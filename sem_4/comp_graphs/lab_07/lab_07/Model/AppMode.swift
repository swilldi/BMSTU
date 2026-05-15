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
}

enum AppMode: Hashable {
    case clipper
    case segments
}
