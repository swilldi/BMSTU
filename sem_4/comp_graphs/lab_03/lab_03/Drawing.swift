//
//  Drawing.swift
//  lab_03
//
//  Created by Dmitriy Dudurev on 04.03.2026.
//

import Foundation
import SwiftUI
import CoreGraphics

struct Pixel: CustomStringConvertible {
    let x: Int
    let y: Int
    let opacity: Double
    
    init (x: Int, y: Int) {
        self.x = x
        self.y = y
        self.opacity = 1
    }
    
    init (x: Double, y: Double, opacity: Double) {
        self.x = Int(round(x))
        self.y = Int(round(y))
        self.opacity = opacity
    }
    
    init (x: Double, y: Double) {
        self.x = Int(round(x))
        self.y = Int(round(y))
        self.opacity = 1
    }
    
    var description: String {
        "[\(x);\(y)]"
    }
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
    let x0 = p1.x.rounded(), y0 = p1.y.rounded()
    let x1 = p2.x.rounded(), y1 = p2.y.rounded()

    let dxInt = x1 - x0
    let dyInt = y1 - y0
    let len = max(abs(dxInt), abs(dyInt))
    if len == 0 { return [Pixel(x: x0, y: y0)] }

    let dx = Double(dxInt) / Double(len)
    let dy = Double(dyInt) / Double(len)

    var x = Double(x0)
    var y = Double(y0)
    var pixels: [Pixel] = []

    for _ in 0...Int(len) {
        pixels.append(Pixel(x: x.rounded(), y: y.rounded()))
        x += dx
        y += dy
    }
    return pixels
}


func lineBresenham(_ p1: CGPoint, _ p2: CGPoint) -> [Pixel] {
    var x1 = Double(p1.x), x2 = Double(p2.x)
    var y1 = Double(p1.y), y2 = Double(p2.y)
    var dx = abs(x2 - x1), dy = abs(y2 - y1)
    let steep = dy > dx
    
    if steep {
        swap(&x1, &y1)
        swap(&x2, &y2)
        swap(&dx, &dy)
    }
    
    let stepY = y2 > y1 ? 1.0 : -1.0
    let stepX = x2 > x1 ? 1.0 : -1.0
        
    var x: Double = x1, y: Double = y1
    var error = dy / dx - 0.5
    var pixels = [steep ? Pixel(x: y, y: x) : Pixel(x: x, y: y)]
    for _ in 0..<Int(dx) {
        if error >= 0 {
            y += stepY
            error -= 1
        }
        
        x += stepX
        error += dy / dx
        pixels.append(steep ? Pixel(x: y, y: x) : Pixel(x: x, y: y))
    }
    // print(pixels)
    return pixels
}

func bresenhamInt(_ p1: CGPoint, _ p2: CGPoint) -> [Pixel] {
    var x1 = Int(round(p1.x)), x2 = Int(round(p2.x))
    var y1 = Int(round(p1.y)), y2 = Int(round(p2.y))
    var dx = Int(abs(x2 - x1)), dy = Int(abs(y2 - y1))
    let steep = dy > dx
    
    if steep {
        swap(&x1, &y1)
        swap(&x2, &y2)
        swap(&dx, &dy)
    }
    if x1 > x2 {
        swap(&x1, &x2)
        swap(&y1, &y2)
    }
    
    let stepY = y2 > y1 ? 1 : -1
        
    var x: Int = x1, y: Int = y1
    var error = 2 * dy - dx
    var pixels = [steep ? Pixel(x: y, y: x) : Pixel(x: x, y: y)]
    for _ in 0..<Int(dx) {
        if error >= 0 {
            y += stepY
            error -= 2 * dx
        }
        
        x += 1
        error += 2 * dy
        pixels.append(steep ? Pixel(x: y, y: x) : Pixel(x: x, y: y))
    }
    // print(pixels)
    return pixels
}

func bresenhamNoStep(_ p1: CGPoint, _ p2: CGPoint) -> [Pixel] {
    var x1 = Double(p1.x), x2 = Double(p2.x)
    var y1 = Double(p1.y), y2 = Double(p2.y)
    var dx = abs(x2 - x1), dy = abs(y2 - y1)
    let steep = dy > dx
    
    if steep {
        swap(&x1, &y1)
        swap(&x2, &y2)
        swap(&dx, &dy)
    }
    if x1 > x2 {
        swap(&x1, &x2)
        swap(&y1, &y2)
    }
    
    let stepY = y2 > y1 ? 1.0 : -1.0
    
    var x: Double = x1, y: Double = y1
    var error = dy / dx - 0.5
    
    var e = error + 0.5
    var pixels = [Pixel]()
    pixels.append(steep ? Pixel(x: y, y: x, opacity: 1 - e) : Pixel(x: x, y: y, opacity: 1 - e))
    pixels.append(steep ? Pixel(x: y + stepY, y: x, opacity: e) : Pixel(x: x, y: y + stepY, opacity: e))
    for _ in 0..<Int(dx) {
        if error >= 0 {
            y += stepY
            error -= 1
        }
        
        x += 1
        error += dy / dx
        e = error + 0.5
        // print(e)
        pixels.append(steep ? Pixel(x: y, y: x, opacity: 1 - e) : Pixel(x: x, y: y, opacity: 1 - e))
        pixels.append(steep ? Pixel(x: y + stepY, y: x, opacity: e) : Pixel(x: x, y: y + stepY, opacity: e))
    }
    // print(pixels)
    return pixels
}


func lineVu(_ p1: CGPoint, _ p2: CGPoint) -> [Pixel] {
    var x1 = Double(p1.x), x2 = Double(p2.x),
        y1 = Double(p1.y), y2 = Double(p2.y)
    var dx = abs(x1 - x2), dy = abs(y1 - y2)
    let steep = dy > dx
    
    if steep {
        swap(&x1, &y1)
        swap(&x2, &y2)
        swap(&dx, &dy)
    }
    
    if x1 > x2 {
        swap(&x1, &x2)
        swap(&y1, &y2)
    }
    
    let gradient = (y2 - y1) / dx
    var x = x1, y = y1
    
    var pixels = [Pixel]()
    for _ in 0...Int(dx) {
        let opacity = y - floor(y)
        
        pixels.append(steep ? Pixel(x: floor(y), y: x, opacity: 1 - opacity) : Pixel(x: x, y: floor(y), opacity: 1 - opacity))
        pixels.append(steep ? Pixel(x: floor(y) + 1 , y: x, opacity: opacity) : Pixel(x: x, y: floor(y) + 1, opacity: opacity))
        
        x += 1
        y += gradient
    }
    
    return pixels
}

func lineLibrary(_ p1: CGPoint, _ p2: CGPoint) -> [Pixel] {
    let startGrid = CGPoint(x: p1.x.rounded(), y: p1.y.rounded())
    let endGrid = CGPoint(x: p2.x.rounded(), y: p2.y.rounded())
    if startGrid == endGrid {
        return [Pixel(x: Int(startGrid.x), y: Int(startGrid.y))]
    }
    
    // Shift to pixel centers, otherwise axis-aligned lines lie on cell borders
    // and may be selected as 2-pixel thick.
    let start = CGPoint(x: startGrid.x + 0.5, y: startGrid.y + 0.5)
    let end = CGPoint(x: endGrid.x + 0.5, y: endGrid.y + 0.5)

    let path = CGMutablePath()
    path.move(to: start)
    path.addLine(to: end)

    let stroked = path.copy(
        strokingWithWidth: 1,
        lineCap: .butt,
        lineJoin: .miter,
        miterLimit: 10
    )

    let bbox = stroked.boundingBoxOfPath.insetBy(dx: -1, dy: -1)
    let minX = Int(floor(bbox.minX))
    let maxX = Int(ceil(bbox.maxX))
    let minY = Int(floor(bbox.minY))
    let maxY = Int(ceil(bbox.maxY))

    var pixels = [Pixel]()
    pixels.reserveCapacity(max(0, (maxX - minX + 1) * (maxY - minY + 1)))

    for y in minY...maxY {
        for x in minX...maxX {
            let center = CGPoint(x: Double(x) + 0.5, y: Double(y) + 0.5)
            if stroked.contains(center) {
                pixels.append(Pixel(x: x, y: y))
            }
        }
    }

    if pixels.isEmpty {
        return [Pixel(x: Int(startGrid.x), y: Int(startGrid.y))]
    }

    // Keep pixel order along the segment to preserve stepping metrics.
    let vx = end.x - start.x
    let vy = end.y - start.y
    let denom = max(1e-9, vx * vx + vy * vy)

    pixels.sort { lhs, rhs in
        let tl = ((Double(lhs.x) - start.x) * vx + (Double(lhs.y) - start.y) * vy) / denom
        let tr = ((Double(rhs.x) - start.x) * vx + (Double(rhs.y) - start.y) * vy) / denom
        return tl < tr
    }

    return pixels
}
