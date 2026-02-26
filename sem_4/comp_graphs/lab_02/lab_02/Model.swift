//
//  Model.swift
//  lab_02
//
//  Created by Dmitriy Dudurev on 25.02.2026.
//

import Foundation
import SwiftUI


enum TransformAction {
    
    case scale(kx: Double, ky: Double, center: CGPoint)
    case scale_zero(points: [[CGPoint]])
}

struct Model {
    var points = [[CGPoint]]()
    
    
    
    var centerPoint: CGPoint {
        guard let first = points.first else { return .zero }
        var minX = first.x, maxX = first.x
        var minY = first.y, maxY = first.y
        
        
        for point in points.dropLast() {
            minX = min(minX, point.x)
            maxX = max(maxX, point.x)
            
            minY = min(minY, point.y)
            maxY = max(maxY, point.y)
        }
        
        let cx = minX + (maxX - minX) / 2, cy = minY + (maxY - minY) / 2
        print(cx, cy)
        
        return CGPoint(x: cx, y: cy)
    }
    
    mutating func move(x: Double, y: Double) {
        print("Перемещение")
        print(points)
        points = points.map { p in
            CGPoint(x: p.x + x, y: p.y + y)
        }
        print(points)
    }
    
    mutating func scale(kx: Double = 1.0, ky: Double = 1.0, center: CGPoint) {
        let cx = Double(center.x), cy = Double(center.y)
        
        print("Scale")
        print(points)
        self.move(x: -cx, y: -cy)
        points = points.map { p in
            CGPoint(x: p.x * kx, y: p.y * ky)
        }
        self.move(x: cx, y: cy)
        print(points)
    }
    
    mutating func rotate(angle: Double = 0.0, center: CGPoint) {
        print(center)
        let cx = Double(center.x), cy = Double(center.y)
        let angleRad = angle * .pi / 180.0
        let cosCG = CGFloat(cos(angleRad)), sinCG = CGFloat(sin(angleRad))
        
        print("rotate")
        print(points)
        self.move(x: -cx, y: -cy)
        points = points.map { p in
            let x = p.x, y = p.y
            return CGPoint(x: x * cosCG - y * sinCG, y: x * sinCG + y * cosCG)
        }
        self.move(x: cx, y: cy)
        print(points)
    }
    
    func drawingPath() -> Path {
        var path = Path()
        
        path.move(to: points[0])
        for point in points[1...] {
            path.addLine(to: point)
        }

        
        return path
    }
}

