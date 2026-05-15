//
//  СyrusBeck.swift
//  lab_07
//
//  Created by Dmitriy Dudurev on 15.05.2026.
//

import Foundation
func cyrusBeck(_ segments: [Segment], _ polygon: [CGPoint]) -> [Segment] {
    guard polygon.count >= 3 else { return [] }
    
    var clippedSegments = [Segment]()
    
    // Рёбра и внутренние нормали
    let n = polygon.count
    var normals = [CGPoint]()
    var points = [CGPoint]()
    
    for i in 0..<n {
        let a = polygon[i]
        let b = polygon[(i + 1) % n]
        let edge = CGPoint(x: b.x - a.x, y: b.y - a.y)
        // Внутренняя нормаль (поворот на -90°, для многоугольника с вершинами по часовой)
        normals.append(CGPoint(x: edge.y, y: -edge.x))
        points.append(a)
    }
    
    for segment in segments {
        let p1 = segment.p1
        let p2 = segment.p2
        let d = CGPoint(x: p2.x - p1.x, y: p2.y - p1.y)
        
        var tEnter: CGFloat = 0
        var tLeave: CGFloat = 1
        var visible = true
        
        for i in 0..<n {
            let N = normals[i]
            let A = points[i]
            
            let W = CGPoint(x: p1.x - A.x, y: p1.y - A.y)
            
            let nd = N.x * d.x + N.y * d.y   // N · D
            let nw = N.x * W.x + N.y * W.y   // N · W
            
            if nd == 0 {
                // Отрезок параллелен ребру
                if nw < 0 {
                    visible = false
                    break
                }
            } else {
                let t = -nw / nd
                if nd < 0 {
                    tEnter = max(tEnter, t)
                } else {
                    tLeave = min(tLeave, t)
                }
            }
        }
        
        if visible && tEnter <= tLeave {
            let newP1 = CGPoint(x: p1.x + tEnter * d.x, y: p1.y + tEnter * d.y)
            let newP2 = CGPoint(x: p1.x + tLeave * d.x, y: p1.y + tLeave * d.y)
            clippedSegments.append(Segment(p1: newP1, p2: newP2))
        }
    }
    
    return clippedSegments
}
