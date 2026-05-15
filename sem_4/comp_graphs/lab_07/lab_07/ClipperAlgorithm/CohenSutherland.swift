//
//  CohenSutherland.swift
//  lab_07
//
//  Created by Dmitriy Dudurev on 15.05.2026.
//

import Foundation
import SwiftUI
typealias PositionCode = Int
typealias PointWithCode = (point: CGPoint, code: PositionCode)

let leftCode =   0b0001
let rightCode =  0b0010
let bottomCode = 0b0100
let topCode =    0b1000

private func pointCode(_ point: CGPoint, _ rect: CGRect) -> PositionCode {
    var code: PositionCode = 0
    
    if point.x < rect.minX {
        code |= leftCode
    } else if point.x > rect.maxX {
        code |= rightCode
    }
    
    if point.y < rect.minY {
        code |= bottomCode
    } else if point.y > rect.maxY {
        code |= topCode
    }
    
    return code
}

private func clipSegment(_ point1: PointWithCode, _ point2: PointWithCode, rect: CGRect) -> (CGPoint, CGPoint) {
    var p1 = point1.point, p2 = point2.point
    let code1 = point1.code, code2 = point2.code
    
    let outerCode = code1 != 0 ? code1 : code2
    var x: CGFloat = 0, y: CGFloat = 0
    
    if outerCode & leftCode != 0 {
        x = rect.minX
        y = p1.y + (p2.y - p1.y) * (rect.minX - p1.x) / (p2.x - p1.x)
    } else if outerCode & rightCode != 0 {
        x = rect.maxX
        y = p1.y + (p2.y - p1.y) * (rect.maxX - p1.x) / (p2.x - p1.x)
    } else if outerCode & bottomCode != 0 {
        y = rect.minY
        x = p1.x + (p2.x - p1.x) * (rect.minY - p1.y) / (p2.y - p1.y)
    } else if outerCode & topCode != 0 {
        y = rect.maxY
        x = p1.x + (p2.x - p1.x) * (rect.maxY - p1.y) / (p2.y - p1.y)
    }
    
    if code1 != 0 {
        p1 = CGPoint(x: x, y: y)
    } else {
        p2 = CGPoint(x: x, y: y)
    }
    
    return (p1, p2)
}

func cohenSutherland(_ segments: [Segment], _ rect: CGRect) -> [Segment] {
    var clippedSegments = [Segment]()
    
    // Точки с кодами
    for segment in segments {
        var p1 = segment.p1, p2 = segment.p2
        var code1 = pointCode(p1, rect), code2 = pointCode(p2, rect)
        
        if code1 & code2 != 0 {
            continue
        }
        
        while code1 | code2 != 0 {
            (p1, p2) = clipSegment((p1, code1), (p2, code2), rect: rect)
            
            code1 = pointCode(p1, rect)
            code2 = pointCode(p2, rect)
        }
        
        clippedSegments.append(.init(p1: p1, p2: p2))
        
    }
    
    return clippedSegments
}
