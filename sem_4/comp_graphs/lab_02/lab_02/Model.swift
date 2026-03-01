//
//  Model.swift
//  lab_02
//
//  Created by Dmitriy Dudurev on 25.02.2026.
//

import Foundation
import SwiftUI


enum TransformAction {
    case move(dx: Double, dy: Double)
    case rotate(angle: Double, center: CGPoint)
    case scale(kx: Double, ky: Double, center: CGPoint)
    case snapshot(points: [[CGPoint]])
}

struct Model {
    var points = [[CGPoint]]()
    var undoTransform: TransformAction?
    
    
    var centerPoint: CGPoint {
        var all: [CGPoint] = []
        for contour in points {
            guard !contour.isEmpty else { continue }
            let pts = (contour.count >= 2 && contour.first == contour.last) ? Array(contour.dropLast()) : contour
            all.append(contentsOf: pts)
        }
        guard let first = all.first else { return .zero }

        var minX = first.x, maxX = first.x
        var minY = first.y, maxY = first.y
        for p in all {
            minX = min(minX, p.x); maxX = max(maxX, p.x)
            minY = min(minY, p.y); maxY = max(maxY, p.y)
        }
        return CGPoint(x: (minX + maxX) / 2, y: (minY + maxY) / 2)
    }
    
    private mutating func applyMove(dx: Double, dy: Double) {
            let dxCG = CGFloat(dx)
            let dyCG = CGFloat(dy)
            for i in points.indices {
                points[i] = points[i].map { p in
                    CGPoint(x: p.x + dxCG, y: p.y + dyCG)
                }
            }
        }

    private mutating func applyScale(kx: Double, ky: Double, center: CGPoint) {
        let kxCG = CGFloat(kx)
        let kyCG = CGFloat(ky)
        let cx = center.x
        let cy = center.y

        for i in points.indices {
            points[i] = points[i].map { p in
                let x = (p.x - cx) * kxCG + cx
                let y = (p.y - cy) * kyCG + cy
                return CGPoint(x: x, y: y)
            }
        }
    }

    private mutating func applyRotate(angleDeg: Double, center: CGPoint) {
        let rad = angleDeg * .pi / 180.0
        let cosCG = CGFloat(cos(rad))
        let sinCG = CGFloat(sin(rad))
        let cx = center.x
        let cy = center.y

        for i in points.indices {
            points[i] = points[i].map { p in
                let x = p.x - cx
                let y = p.y - cy
                return CGPoint(x: x * cosCG - y * sinCG + cx, y: x * sinCG + y * cosCG + cy)
            }
        }
    }


    mutating func move(x: Double, y: Double) {
        undoTransform = .move(dx: -x, dy: -y)
        applyMove(dx: x, dy: y)
    }

    mutating func scale(kx: Double, ky: Double, center: CGPoint) {
        let eps = 1e-6
        if abs(kx) <= eps || abs(ky) <= eps {
            undoTransform = .snapshot(points: points) // необратимо — снапшот
        } else {
            undoTransform = .scale(kx: 1.0 / kx, ky: 1.0 / ky, center: center)
        }
        applyScale(kx: kx, ky: ky, center: center)
    }

    mutating func rotate(angle: Double, center: CGPoint) {
        undoTransform = .rotate(angle: -angle, center: center) // <-- минус!
        applyRotate(angleDeg: angle, center: center)
    }

    mutating func undo() {
        guard let action = undoTransform else { return }
        undoTransform = nil // важно: чтобы undo не перезаписывался

        switch action {
        case .move(let dx, let dy):
            applyMove(dx: dx, dy: dy)
        case .scale(let kx, let ky, let center):
            applyScale(kx: kx, ky: ky, center: center)
        case .rotate(let angle, let center):
            applyRotate(angleDeg: angle, center: center)
        case .snapshot(let pts):
            points = pts
        }
    }
    
    func drawingPath() -> Path {
        var path = Path()
        
        for points in self.points {
            path.move(to: points[0])
            for point in points[1...] {
                path.addLine(to: point)
            }
        }

        return path
    }
}

