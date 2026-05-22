//
//  AppMode.swift
//  lab_07
//
//  Created by Dmitriy Dudurev on 15.05.2026.
//

import Foundation

enum Algorithm: Hashable {
    case cohenSutherland
    case cyrusBeck
    case sutherlandHodgman
}

enum AppMode: Hashable {
    case clipper
    case segments
    case subjectPolygon
}

enum LineConstraint: Hashable, CaseIterable {
    case free
    case horizontal
    case vertical

    var label: String {
        switch self {
        case .free: return "Свободно"
        case .horizontal: return "Горизонталь"
        case .vertical: return "Вертикаль"
        }
    }
}
