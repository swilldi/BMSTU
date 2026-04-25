//
//  FillingAlgorithm.swift
//  lab_06
//
//  Created by Dmitriy Dudurev on 04.04.2026.
//

import Foundation
import CoreGraphics

// MARK: - Затравочный алгоритм заполнения со строчным сканированием

private func pixelKey(_ x: Int, _ y: Int) -> Int64 {
    Int64(x) << 32 | Int64(UInt32(bitPattern: Int32(y)))
}

private func rasterizeBorder(_ polygonEdges: [Edge]) -> Set<Int64> {
    var borderSet = Set<Int64>()
    for edge in polygonEdges {
        let pts = lineDDA(edge.p1, edge.p2)
        for pt in pts {
            borderSet.insert(pixelKey(Int(pt.x), Int(pt.y)))
        }

        for i in 1..<pts.count {
            let px = Int(pts[i-1].x), py = Int(pts[i-1].y)
            let cx = Int(pts[i].x),   cy = Int(pts[i].y)
            if abs(cx - px) == 1 && abs(cy - py) == 1 {
                borderSet.insert(pixelKey(cx, py))
            }
        }
    }
    return borderSet
}

func scanlineSeedFill(seed: Point, polygonEdges: [Edge], canvasSize: CGSize) -> [Edge] {
    let xMax = Int(canvasSize.width), yMax = Int(canvasSize.height)
    let (xMin, yMin) = (0, 0)
    let borderSet = rasterizeBorder(polygonEdges)

    var filledSet = Set<Int64>()
    var result = [Edge]()
    var stack = [(Int, Int)]()

    stack.append((Int(seed.x.rounded()), Int(seed.y.rounded())))

    while !stack.isEmpty {
        let (x, y) = stack.removeLast()

        if borderSet.contains(pixelKey(x, y)) || filledSet.contains(pixelKey(x, y)) { continue }
        if x < xMin || x > xMax || y < yMin || y > yMax { continue }

        // Идём влево от затравки
        var xLeft = x
        while xLeft - 1 >= xMin && !borderSet.contains(pixelKey(xLeft - 1, y)) {
            xLeft -= 1
        }

        // Идём вправо от затравки
        var xRight = x
        while xRight + 1 <= xMax && !borderSet.contains(pixelKey(xRight + 1, y)) {
            xRight += 1
        }

        // Заполняем отрезок [xLeft, xRight]
        for xi in xLeft...xRight {
            filledSet.insert(pixelKey(xi, y))
        }
        result.append(.init(p1: .init(x: xLeft, y: y), p2: .init(x: xRight, y: y)))

        // Ищем новые затравки выше и ниже
        for dy in [-1, 1] {
            let ny = y + dy
            guard ny >= yMin && ny <= yMax else { continue }
            scanForNewSeeds(xLeft: xLeft, xRight: xRight, y: ny,
                            borderSet: borderSet, filledSet: filledSet,
                            stack: &stack)
        }
    }

    return result
}

private func scanForNewSeeds(xLeft: Int, xRight: Int, y: Int,
                             borderSet: Set<Int64>, filledSet: Set<Int64>,
                             stack: inout [(Int, Int)]) {
    var inSegment = false
    for x in xLeft...xRight {
        let isFree = !borderSet.contains(pixelKey(x, y)) && !filledSet.contains(pixelKey(x, y))
        if isFree {
            if !inSegment {
                stack.append((x, y))
                inSegment = true
            }
        } else {
            inSegment = false
        }
    }
}

func timeScanlineSeedFill(seed: Point, polygonEdges: [Edge], canvasSize: CGSize) -> (Double, [Edge]) {
    let clock = ContinuousClock()
    let start = clock.now
    let edges = scanlineSeedFill(seed: seed, polygonEdges: polygonEdges, canvasSize: canvasSize)
    let end = clock.now

    let elapsed = start.duration(to: end)
    let time = Double(elapsed.components.seconds) * 1e3 + Double(elapsed.components.attoseconds) / 1e15
    return (time: time, edges: edges)
}
