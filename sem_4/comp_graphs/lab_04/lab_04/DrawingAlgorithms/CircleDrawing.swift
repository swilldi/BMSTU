//
//  CircleDrawing.swift
//  lab_04
//
//  Created by Dmitriy Dudurev on 14.03.2026.
//

import Foundation
import SwiftUI

enum CircleDrawingAlgorithms: String, CaseIterable, Identifiable {
    case canonicalEquation = "Канонического уравнения"
    case parametricEquatiob = "Параметрическое уравнение"
    case bresenham = "Алгоритм Брезенхема"
    case midPoint = "Алгоритм средней точки"
    case library = "Библиотечная реализация"
    
    var id: String { rawValue }
}

func circlePixelsCanonicalEquation(center: CGPoint, r: Double) -> [Pixel] {
    var pixels = [Pixel]()
    
    let cx = center.x
    let cy = center.y
    let r2 = r * r
    let limit = r / sqrt(2.0)
    
    for dx in stride(from: 0.0, through: limit, by: 1.0) {
        let dy = sqrt(r2 - dx * dx)
        
        let x = round(dx)
        let y = round(dy)
        
        pixels.append(contentsOf: [
            .init(x: cx + x, y: cy + y),
            .init(x: cx - x, y: cy + y),
            .init(x: cx + x, y: cy - y),
            .init(x: cx - x, y: cy - y),
            .init(x: cx + y, y: cy + x),
            .init(x: cx - y, y: cy + x),
            .init(x: cx + y, y: cy - x),
            .init(x: cx - y, y: cy - x)
        ])
    }
    
    return pixels
}

func cirlePixelParametricEquatiob(center: CGPoint, r: Double) -> [Pixel] {
    if r == 0 {
        return [Pixel(x: center.x, y: center.y)]
    }
    
    var pixels = [Pixel]()
    
    let cx = center.x,
        cy = center.y,
        step = .pi * .pi * r / 720
    
    for t in stride(from: 0, to: .pi / 4, by: step) {
        let x = round(r * cos(t)), y = round(r * sin(t))
        
        pixels.append(contentsOf: [
            .init(x: cx + x, y: cy + y),
            .init(x: cx + x, y: cy - y),
            .init(x: cx - x, y: cy + y),
            .init(x: cx - x, y: cy - y),
            .init(x: cx + y, y: cy + x),
            .init(x: cx + y, y: cy - x),
            .init(x: cx - y, y: cy + x),
            .init(x: cx - y, y: cy - x)
        ])
    }
    
    return pixels
}

func circlePixelBresenham(center: CGPoint, r: Double) -> [Pixel] {
    let cx = center.x, cy = center.y
    var pixels = [Pixel]()
    
    var delta = 2 * (1 - r)
    var x = 0.0, y = r
    while y >= 0 {
        pixels.append(contentsOf: [
            .init(x: cx + x, y: cy + y),
            .init(x: cx + x, y: cy - y),
            .init(x: cx - x, y: cy + y),
            .init(x: cx - x, y: cy - y),
        ])
        
        if delta < 0 {
            // Горизонтальный или диагональных шаг
            let distanceToPixel = 2 * (delta + y) - 1
            x += 1
            delta += 2 * x + 1
            
            if distanceToPixel > 0 {
                y -= 1
                delta += -2 * y + 1
            }
        } else if delta > 0 {
            // Вертикальный или диагональных шаг
            let distanceToPixel = 2 * (delta - x) - 1
            y -= 1
            delta += -2 * y + 1
            
            if distanceToPixel <= 0 {
                x += 1
                delta += 2 * x + 1
            }
        } else {
            // Диагольный шаг
            x += 1
            y -= 1
            delta += 2 * x - 2 * y + 2
        }
    }
    
    return pixels
}

func circlePixelMidPoint(center: CGPoint, r: Double) -> [Pixel] {
    let cx = center.x, cy = center.y
    let xLimit = r / sqrt(2)
    let r2 = pow(r, 2)
    
    var pixels = [Pixel]()
    var x = 0.0, y = r
    while x <= xLimit {
        pixels.append(contentsOf: [
            .init(x: cx + x, y: cy + y),
            .init(x: cx + x, y: cy - y),
            .init(x: cx - x, y: cy + y),
            .init(x: cx - x, y: cy - y),
            .init(x: cx + y, y: cy + x),
            .init(x: cx + y, y: cy - x),
            .init(x: cx - y, y: cy + x),
            .init(x: cx - y, y: cy - x)
        ])
        
        let f = pow(x + 1, 2) + pow(y - 0.5, 2) - r2
        if f < 0 {
            x += 1
        } else {
            x += 1
            y -= 1
        }
    }

    return pixels
}
