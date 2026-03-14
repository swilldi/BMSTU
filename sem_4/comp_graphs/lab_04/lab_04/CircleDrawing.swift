//
//  CircleDrawing.swift
//  lab_04
//
//  Created by Dmitriy Dudurev on 14.03.2026.
//

import Foundation

enum CirleDrawingAlgorithms: String, CaseIterable, Identifiable {
    case canonicalEquation = "Канонического уравнения"
    case parametricEquatiob = "Параметрическое уравнение"
    case bresenham = "Алгоритм Брезенхема"
    case midPoint = "Алгоритм средней точки"
    case library = "Библиотечная реализация"
    
    var id: String { rawValue }
}
