//
//  Figure.swift
//  lab_04
//
//  Created by Dmitriy Dudurev on 13.03.2026.
//

import Foundation
import SwiftUI

enum FigureType: String, CaseIterable, Identifiable {
    case ellipse = "Эллипс"
    case cirlce = "Круг"
    case line = "Линия"
    
    var id: String { rawValue }
}

struct FigureSettings: Equatable {
    var type: FigureType
    
    // Центр фигуры
    var center: CGPoint = CGPoint(x: 0, y: 0)
    
    // Радиус круга
    var circleRadius: Double = 1
    var circleAlgorithms: CircleDrawingAlgorithms = .canonicalEquation
    
    // Радиусы эллипса
    var ellipseXRadius: Double = 2
    var ellipseYRadius: Double = 2
    var ellipseAlgorithms: EllipseDrawingAlgorithms = .canonicalEquation
    
    init(type: FigureType) {
        self.type = type
    }
}


struct Figure: Equatable {
    static func == (lhs: Figure, rhs: Figure) -> Bool {
        lhs.pixels == rhs.pixels && lhs.color == rhs.color
    }
    
    let pixels: [Pixel]
    let color: Color
    init(_ pixels: [Pixel], color: Color) {
        self.pixels = pixels
        self.color = color
    }
}

struct Pixel: Equatable & Hashable {
    let x: Int
    let y: Int
    let opacity: Double
    
    init(x: Double, y: Double) {
        self.x = Int(x)
        self.y = Int(y)
        opacity = 1
    }
    
    init(x: Double, y: Double, opacity: Double) {
        self.x = Int(x)
        self.y = Int(y)
        self.opacity = opacity
    }
}
