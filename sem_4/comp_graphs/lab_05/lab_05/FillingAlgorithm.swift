//
//  FillingAlgorithm.swift
//  lab_05
//
//  Created by Dmitriy Dudurev on 04.04.2026.
//

import Foundation

func fillingByEdgesWithFlags(points pollygonPoints: [Point], edges pollygonEdges: [Edge]) -> [Edge] {
    var edges = [Edge]()
    
    let (xMin, xMax, yMin, yMax) = boundingBox(points: pollygonPoints)
    // Собираем пересечения сканирующих линий
    var scanLines = [Int:Set<Int>]()
    for edge in pollygonEdges {
        let p1 = edge.p1, p2 = edge.p2
        let dx = p2.x - p1.x, dy = abs(p2.y - p1.y) > 1e-5 ? p2.y - p1.y : 1
        for y in stride(from: min(p1.y, p2.y), through: max(p1.y, p2.y) - 1, by: 1) {
            let db = y - p1.y, da = round(Double(dx * db) / Double(dy) + 0.5)
            scanLines[Int(y), default: []].insert(Int(p1.x + da))
        }
    }
    
    //
    var prevPoint: Point?
    for y in stride(from: yMin, through: yMax, by: 1) {
        
        var inside = false
        for x in stride(from: xMin, through: xMax, by: 1) {
            if scanLines[Int(y), default: []].contains(Int(x)) {
                inside = !inside
                if inside {
                    prevPoint = Point(x: x, y: y)
                } else {
                    edges.append(.init(p1: prevPoint!, p2: .init(x: x, y: y)))
                    prevPoint = nil
                }
                
            }
        }
        
        if inside {
            edges.append(.init(p1: prevPoint!, p2: .init(x: xMax, y: y)))
            prevPoint = nil
        }
        
    }
    
    for k in scanLines.keys.sorted() {
        print("\(k): \(scanLines[k, default: []])")
    }
    return edges
}

func boundingBox(points: [Point]) -> (Double, Double, Double, Double) {
    var xMin = points[0].x, xMax = points[0].x
    var yMin = points[0].y, yMax = points[0].y
    
    for point in points {
        xMin = min(xMin, point.x)
        xMax = max(xMax, point.x)
        
        yMin = min(yMin, point.y)
        yMax = max(yMax, point.y)
    }
    
    return (xMin, xMax, yMin, yMax)
}
