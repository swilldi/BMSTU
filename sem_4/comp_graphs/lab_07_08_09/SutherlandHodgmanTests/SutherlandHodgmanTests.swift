//
//  SutherlandHodgmanTests.swift
//  SutherlandHodgmanTests
//
//  Created by Dmitriy Dudurev on 22.05.2026.
//

import Testing
import Foundation
@testable import lab_07_08_09

struct SutherlandHodgmanTests {

    // Выпуклое окно-отсекатель: квадрат [0,10] x [0,10]
    private let window: [CGPoint] = [
        CGPoint(x: 0, y: 0),
        CGPoint(x: 0, y: 10),
        CGPoint(x: 10, y: 10),
        CGPoint(x: 10, y: 0),
    ]

    @Test func subjectFullyInside() {
        // Многоугольник целиком внутри окна — остаётся без отсечения
        let subject = [
            CGPoint(x: 2, y: 2),
            CGPoint(x: 2, y: 8),
            CGPoint(x: 8, y: 8),
            CGPoint(x: 8, y: 2),
        ]

        let result = sutherlandHodgman(subject, window)

        #expect(result.count == 4)
        for p in result {
            #expect(p.x >= 2 - 1e-6 && p.x <= 8 + 1e-6)
            #expect(p.y >= 2 - 1e-6 && p.y <= 8 + 1e-6)
        }
    }

    @Test func subjectFullyOutside() {
        // Многоугольник целиком вне окна — результат пустой
        let subject = [
            CGPoint(x: 20, y: 20),
            CGPoint(x: 20, y: 30),
            CGPoint(x: 30, y: 30),
            CGPoint(x: 30, y: 20),
        ]

        let result = sutherlandHodgman(subject, window)

        #expect(result.count < 3)
    }

    @Test func subjectPartiallyClipped() {
        // Многоугольник пересекает окно — остаётся пересечение [5,10] x [5,10]
        let subject = [
            CGPoint(x: 5, y: 5),
            CGPoint(x: 5, y: 15),
            CGPoint(x: 15, y: 15),
            CGPoint(x: 15, y: 5),
        ]

        let result = sutherlandHodgman(subject, window)

        #expect(result.count == 4)
        for p in result {
            #expect(p.x >= 5 - 1e-6 && p.x <= 10 + 1e-6)
            #expect(p.y >= 5 - 1e-6 && p.y <= 10 + 1e-6)
        }
    }
}
