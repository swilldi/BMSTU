//
//  FillingAlgorithm.swift
//  lab_05
//
//  Created by Dmitriy Dudurev on 04.04.2026.
//

import Foundation

func isExtremum(_ edge1: Edge, _ edge2: Edge) -> Bool {
    let  y1 = edge1.p1.y, y2 = edge1.p2.y, y3 = edge2.p2.y
    return y2 < y1 && y2 < y3 || y2 > y1 && y2 > y3
}

func scanlinePoints(_ p1: Point, _ p2: Point) -> [Point] {
    let y1 = Int(p1.y), y2 = Int(p2.y)
    guard y1 != y2 else { return [] }

    let dy = Double(y2 - y1)
    var pts = [Point]()

    let yFrom = min(y1, y2), yTo = max(y1, y2)
    for y in yFrom...yTo {
        let t  = Double(y - y1) / dy
        let x  = p1.x + t * (p2.x - p1.x)
        pts.append(.init(x: x.rounded(), y: Double(y)))
    }

    // Порядок должен совпадать с направлением ребра (от p1 к p2)
    if y1 > y2 { pts.reverse() }
    return pts
}

func fillingByEdgesWithFlags(points pollygonPoints: [Point], edges pollygonEdges: [Edge]) -> [Edge] {
    var result = [Edge]()

    let (xMin, xMax, yMin, yMax) = boundingBox(points: pollygonPoints)
    let dx = xMax - xMin

    var edgesMap = Dictionary<Int,[Bool]>()
    for i in 0..<pollygonEdges.count {
        let edge1 = pollygonEdges[i]
        let edge2 = pollygonEdges[(i + 1) % pollygonEdges.count]
        
        var points = scanlinePoints(edge1.p2, edge2.p2)

        // если вершина — не экстремум, убираем общую вершину
        if !isExtremum(edge1, edge2) {
            points = Array(points.dropFirst())
        }

        for point in points {
            let idx = Int(point.x) - xMin
            edgesMap[Int(point.y), default: Array(repeating: false, count: dx + 1)][idx].toggle()
        }
    }
    
    for key in edgesMap.keys.sorted() {
        print("\(key): \(edgesMap[key, default: []])")
    }

    // Этап 2: проход с флагом + сборка отрезков
    for y in stride(from: Int(yMin), through: Int(yMax), by: 1) {
        var inside = false
        var xStart: Int = xMin
        
        guard let row = edgesMap[y] else { continue }
        for x in stride(from: Int(xMin), through: Int(xMax), by: 1) where row[x - xMin] {
            inside.toggle()
            
            if inside {
                xStart = x
            } else {
                result.append(.init(p1: .init(x: xStart, y: y), p2: .init(x: x, y: y)))
            }
        }
    }

    for row in result {
        print(row)
    }
    return result
}

func boundingBox(points: [Point]) -> (Int, Int, Int, Int) {
    var xMin = points[0].x, xMax = points[0].x
    var yMin = points[0].y, yMax = points[0].y
    
    for point in points {
        xMin = min(xMin, point.x)
        xMax = max(xMax, point.x)
        
        yMin = min(yMin, point.y)
        yMax = max(yMax, point.y)
    }
    
    return (Int(xMin), Int(xMax), Int(yMin), Int(yMax))
}

func timeFillingByEdgesWithFlags(points pollygonPoints: [Point], edges pollygonEdges: [Edge]) -> (Double, [Edge]) {
    let clock = ContinuousClock()
    
    // замер выполнения
    let start = clock.now
    let edges = fillingByEdgesWithFlags(points: pollygonPoints, edges: pollygonEdges)
    let end = clock.now
    
    
    let elapsed = start.duration(to: end)
    let time = Double(elapsed.components.seconds) * 1e3 + Double(elapsed.components.attoseconds) / 1e15
    
    return (time: time, edges: edges)  // ms
}

