//
//  lab_03App.swift
//  lab_03
//
//  Created by Dmitriy Dudurev on 21.03.2026.
//

import SwiftUI

@main
struct lab_03App: App {
    
    let points: [Point3D] = [
        .init(x: 0, y: 0, z: 0),
        .init(x: 1, y: 0, z: 1),
        .init(x: 2, y: 0, z: 4),
        .init(x: 0, y: 1, z: 1),
        .init(x: 1, y: 1, z: 2),
        .init(x: 2, y: 1, z: 5),
        .init(x: 0, y: 2, z: 4),
        .init(x: 1, y: 2, z: 5),
        .init(x: 2, y: 2, z: 8),
    ]
    
    var body: some Scene {
        WindowGroup {
            ContentView()
                .preferredColorScheme(.light)
        }
    }
}
