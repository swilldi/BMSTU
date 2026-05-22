//
//  PolygonVertex.swift
//  lab_07
//
//  Created by Dmitriy Dudurev on 15.05.2026.
//

import SwiftUI

struct PolygonVertex: Identifiable {
    let id: Int
    let index: Int
    let point: CGPoint
    
    init(index: Int, point: CGPoint) {
        self.id = index
        self.index = index
        self.point = point
    }
}
