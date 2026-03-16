//
//  EllipseDrawing.swift
//  lab_04
//
//  Created by Dmitriy Dudurev on 14.03.2026.
//

import Foundation

enum EllipseDrawingAlgorithms: String, CaseIterable, Identifiable {
    case canonicalEquation = "Канонического уравнения"
    case parametricEquatiob = "Параметрическое уравнение"
    case bresenham = "Алгоритм Брезенхема"
    case midPoint = "Алгоритм средней точки"
    case library = "Библиотечная реализация"
    
    var id: String { rawValue }
}

func ellipsePixelsCanonicalEquation(center: CGPoint, rx a: Double, ry b: Double) -> [Pixel] {
    var pixels = Set<Pixel>()
    
    let cx = center.x
    let cy = center.y
    let a2 = a * a, b2 = b * b
    let xLimit: Double = a2 / sqrt(a2 + b2), yLimit = b2 / sqrt(a2 + b2)
    
    for x in stride(from: 0, to: xLimit, by: 1) {
        let y = round(b * sqrt(1 - x * x / a2))

        pixels.insert(Pixel(x: cx + x, y: cy + y))
        pixels.insert(Pixel(x: cx + x, y: cy - y))
        pixels.insert(Pixel(x: cx - x, y: cy + y))
        pixels.insert(Pixel(x: cx - x, y: cy - y))
    }
    
    for y in stride(from: 0, to: yLimit, by: 1) {
        let x = round(a * sqrt(1 - y * y / b2))
        
        pixels.insert(Pixel(x: cx + x, y: cy + y))
        pixels.insert(Pixel(x: cx + x, y: cy - y))
        pixels.insert(Pixel(x: cx - x, y: cy + y))
        pixels.insert(Pixel(x: cx - x, y: cy - y))
    }
    
    return Array(pixels)
}

func ellipsePixelParametricEquatiob(center: CGPoint, rx a: Double, ry b: Double) -> [Pixel] {
    if a == 0 && b == 0 {
        return [Pixel(x: center.x, y: center.y)]
    }
    
    var pixels = Set<Pixel>()
    
    let cx = center.x,
        cy = center.y,
        step = 1 / max(a, b)
    
    for t in stride(from: 0, through: .pi / 2, by: step) {
        let x = round(a * cos(t)), y = round(b * sin(t))
        
        pixels.insert(Pixel(x: cx + x, y: cy + y))
        pixels.insert(Pixel(x: cx + x, y: cy - y))
        pixels.insert(Pixel(x: cx - x, y: cy + y))
        pixels.insert(Pixel(x: cx - x, y: cy - y))
    }
    
    pixels.insert(Pixel(x: cx, y: cy + b))
    pixels.insert(Pixel(x: cx, y: cy - b))
    pixels.insert(Pixel(x: cx + a, y: cy))
    pixels.insert(Pixel(x: cx - a, y: cy))
    
    return Array(pixels)
}

func ellipsePixelBresenham(center: CGPoint, rx a: Double, ry b: Double) -> [Pixel] {
    let cx = center.x, cy = center.y,
        a2 = a * a, b2 = b * b, ab2 = a2 * b2
    var pixels = [Pixel]()
    
    var delta = a2 * (1 - 2 * b)
    var x = 0.0, y = b
    while y >= 0 {
        pixels.append(contentsOf: [
            .init(x: cx + x, y: cy + y),
            .init(x: cx + x, y: cy - y),
            .init(x: cx - x, y: cy + y),
            .init(x: cx - x, y: cy - y),
        ])
        
        if delta < 0 {
            // Горизонтальный или диагональных шаг
            let distanceToPixel = 2 * delta +  a2 * (2 * y - 1)
            x += 1
            delta += b2 * (2 * x + 1)
            
            if distanceToPixel > 0 {
                y -= 1
                delta += -a2 * (2 * y - 1)
            }
        } else if delta > 0 {
            // Вертикальный или диагональных шаг
            let distanceToPixel = 2 * delta - b2 * (2 * x + 1)
            y -= 1
            delta += -a2 * (2 * y - 1)
            
            if distanceToPixel <= 0 {
                x += 1
                delta += b2 * (2 * x + 1)
            }
        } else {
            // Диагольный шаг
            x += 1
            y -= 1
            delta += b2 * (2 * x + 1) - a2 * (2 * y - 1)
        }
    }
    
    return pixels
}

func ellipsePixelMidPoint(center: CGPoint, rx a: Double, ry b: Double) -> [Pixel] {
    
    let cx = center.x, cy = center.y
    let a2 = pow(a, 2), b2 = pow(b, 2), ab2 = a2 * b2
    
    var pixels = [Pixel]()
    var x = 0.0, y = b
    
    if a == 0 {
        for y in -Int(b)...Int(b) {
            pixels.append(Pixel(x: cx, y: cy + Double(y)))
        }
        return pixels
    }
    if b == 0 {
        for x in -Int(a)...Int(a) {
            pixels.append(Pixel(x: cx + Double(x), y: cy))
        }
        return pixels
    }
    
    // Проход по x
    while b2 * x <= a2 * y {
        pixels.append(contentsOf: [
            .init(x: cx + x, y: cy + y),
            .init(x: cx + x, y: cy - y),
            .init(x: cx - x, y: cy + y),
            .init(x: cx - x, y: cy - y)
        ])
        
        let f = b2 * (x + 1) * (x + 1) + a2 * (y - 0.5) * (y - 0.5) - ab2
        if f < 0 {
            x += 1
        } else {
            x += 1
            y -= 1
        }
    }
    
    // Проход по y
    while y >= 0 {
        pixels.append(contentsOf: [
            .init(x: cx + x, y: cy + y),
            .init(x: cx + x, y: cy - y),
            .init(x: cx - x, y: cy + y),
            .init(x: cx - x, y: cy - y)
        ])
        
        let f = b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - ab2
        if f < 0 {
            x += 1
            y -= 1
        } else {
            y -= 1
        }
    }

    return pixels
}


