//
//  Drawing.swift
//  lab_03
//
//  Created by Dmitriy Dudurev on 04.03.2026.
//

import Foundation
import SwiftUI

struct Pixel {
    let x: Int
    let y: Int
    let color: Color? = nil
}

func sign<T: Comparable & Numeric>(_ num: T) -> T {
    switch num {
    case ..<0:
        return -1
    case 0:
        return 0
    default:
        return 1
    }
}

func lineDDA(_ p1: CGPoint, _ p2: CGPoint) -> [Pixel] {
    let x0 = Int(p1.x.rounded()), y0 = Int(p1.y.rounded())
    let x1 = Int(p2.x.rounded()), y1 = Int(p2.y.rounded())

    let dxInt = x1 - x0
    let dyInt = y1 - y0
    let len = max(abs(dxInt), abs(dyInt))
    if len == 0 { return [Pixel(x: x0, y: y0)] }

    let dx = Double(dxInt) / Double(len)
    let dy = Double(dyInt) / Double(len)

    var x = Double(x0)
    var y = Double(y0)
    var pixels: [Pixel] = []
    pixels.reserveCapacity(len + 1)

    for _ in 0...len {
        pixels.append(Pixel(x: Int(x.rounded()), y: Int(y.rounded())))
        x += dx
        y += dy
    }
    return pixels
}

func lineBresenham(_ p1: CGPoint, _ p2: CGPoint) -> [Pixel] {
    var x0 = p1.x, y0 = p1.y
    let x1 = p2.x, y1 = p2.y

    let dx = abs(x1 - x0)
    let sx = x0 < x1 ? 1.0 : -1.0
    let dy = -abs(y1 - y0)
    let sy = y0 < y1 ? 1.0 : -1.0
    var error = dy / dx - 0.5

    var pixels = [Pixel]()
    
    var x = Double(x0), y = Double(y0)
    for _ in 0..<Int(dx) {
        if error >= 0 {
            y += sy
            error -= 1
        }
        
        x += sx
        error += Double(dy) / Double (dx)
        
        pixels.append(Pixel(x: Int(round(x)), y: Int(round(y))))
    }

    return pixels
}

func bresenhamInt(_ p1: CGPoint, _ p2: CGPoint) -> [Pixel] {
    var x0 = Int(p1.x.rounded()), y0 = Int(p1.y.rounded())
    let x1 = Int(p2.x.rounded()), y1 = Int(p2.y.rounded())

    let dx = abs(x1 - x0)
    let sx = x0 < x1 ? 1 : -1
    let dy = -abs(y1 - y0)
    let sy = y0 < y1 ? 1 : -1
    var error = 2 * dy - dx

    var x = x0, y = y0
    var pixels = [Pixel(x: x, y: y)]
    for _ in 0..<dx {
        if error >= 0 {
            y += sy
            error -= 2 * dx
        }
        
        x += sx
        error += 2 * dy
        
        pixels.append(Pixel(x: x, y: y))
    }

    return pixels
}

func bresenhamNoStep(_ p1: CGPoint, _ p2: CGPoint) -> [Pixel] {
    var x0 = Int(p1.x.rounded()), y0 = Int(p1.y.rounded())
    let x1 = Int(p2.x.rounded()), y1 = Int(p2.y.rounded())

    let dx = abs(x1 - x0)
    let sx = x0 < x1 ? 1 : -1
    let dy = -abs(y1 - y0)
    let sy = y0 < y1 ? 1 : -1
    var error = 2 * dy - dx

    var x = x0, y = y0
    var pixels = [Pixel(x: x, y: y)]
    for _ in 0..<dx {
        if error >= 0 {
            y += sy
            error -= 2 * dx
        }
        
        x += sx
        error += 2 * dy
        
        pixels.append(Pixel(x: x0, y: y0))
    }

    return pixels
}
//func lineVu(_ p1: CGPoint, _ p2: CGPoint) -> [Pixel] {
//    
//}
