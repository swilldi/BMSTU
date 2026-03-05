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
    let x0 = p1.x, y0 = p1.y
    let x1 = p2.x, y1 = p2.y
    let len = max(abs(x1 - x0), abs(y1 - y0))
    if len == 0 {
        return [Pixel(x: Int(x1), y: Int(y1))]
    }
    
    let dx = (x1 - x0) / len, dy = (y1 - y0) / len
    
    var x = x0 + 0.5 * sin(dx), y = y0 + 0.5 * sign(dy)
    var pixels = [Pixel(x: Int(round(x)), y: Int(round(y)))]
    for _ in 0..<Int(len) {
        x += dx
        y += dy
        pixels.append(Pixel(x: Int(round(x)), y: Int(round(y))))
    }
    
    return pixels
}
