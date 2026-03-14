//
//  Figure.swift
//  lab_04
//
//  Created by Dmitriy Dudurev on 13.03.2026.
//

import Foundation
import SwiftUI



class Figure {
    let pixels: [Pixel]
    let color: Color
    init(_ pixels: [Pixel], color: Color) {
        self.pixels = pixels
        self.color = color
    }
}

struct Pixel {
    let x: Int
    let y: Int
    let opacity: Double
    
    init(x: Int, y: Int) {
        self.x = x
        self.y = y
        opacity = 1
    }
    
    init(x: Int, y: Int, opacity: Double) {
        self.x = x
        self.y = y
        self.opacity = opacity
    }
}
