//
//  main.swift
//  ApproximationTest
//
//  Created by Dmitriy Dudurev on 21.03.2026.
//

import Foundation


let originPoints: [Point] = [
    .init(x: 0.5, y: 10.5),
    .init(x: 1.0, y: 1.6),
    .init(x: 1.5, y: 0.55),
    .init(x: 2.0, y: 0.26),
    .init(x: 2.5, y: 0.15),
    .init(x: 3.0, y: 0.08),
]

struct ApproxedFunc: CustomStringConvertible {
    let f: (Double) -> Double
    
    let a: Double
    let b: Double
    var description: String
}

// y = ax^b
func variant1(_ originPoints: [Point]) -> [Point] {
    var linerazePoints = [Point]()
    for point in originPoints {
        linerazePoints.append(.init(x: log(point.x), y: log(point.y)))
    }
    
    let coef = getCoef(data: linerazePoints, n: 1)
    let a = exp(coef[0]), b = coef[1]
    let f = { x in
        a * pow(x, b)
    }
    
    var points = [Point]()
    for point in originPoints {
        points.append(.init(x: point.x, y: f(point.x)))
    }
    
    return points
}

// y = ae^(bx)
func variant2(_ originPoints: [Point]) -> [Point] {
    
    
    var linerazePoints = [Point]()
    for point in originPoints {
        linerazePoints.append(.init(x: point.x, y: log(point.y)))
    }
    
    let coef = getCoef(data: linerazePoints, n: 1)
    let a = exp(coef[0]), b = coef[1]
    let f = { x in
        a * pow(x, b)
    }
    
    var points = [Point]()
    for point in originPoints {
        points.append(.init(x: point.x, y: f(point.x)))
    }
    
    return points
}

// y = a + b / x
func variant3(_ originPoints: [Point]) -> [Point] {
    var linerazePoints = [Point]()
    for point in originPoints {
        linerazePoints.append(.init(x: 1 / point.x, y: point.y))
    }
    
    let coef = getCoef(data: linerazePoints, n: 1)
    let a = coef[0], b = coef[1]
    let f = { x in
        a + b / x
    }
    
    var points = [Point]()
    for point in originPoints {
        points.append(.init(x: point.x, y: f(point.x)))
    }
    
    return points
}

// y = a / (b + c * x)
func variant4(_ originPoints: [Point]) -> [Point] {
    var linerazePoints = [Point]()
    for point in originPoints {
        linerazePoints.append(.init(x: 1 / point.x, y: point.y))
    }
    
    let coef = getCoef(data: linerazePoints, n: 1)
    let a = coef[0], b = coef[1] // a + b * x; a = a1 / a0, b = a2/a0
    let f = { x in
        1 / (a + b * x)
    }
    
    var points = [Point]()
    for point in originPoints {
        points.append(.init(x: point.x, y: f(point.x)))
    }
    
    return points
}





func funcError(_ originPoints: [Point], _ approxPoints: [Point]) -> Double {
    var res = 0.0
    for (originPoint, approxPoint) in zip(originPoints, approxPoints) {
        res += pow(originPoint.y - approxPoint.y, 2)
    }
    
    let N = Double(originPoints.count)
    res = sqrt(res / (N + 1))
    
    return res
}

func chooseBetter(_ points: [Point]) -> ([Point]) -> [Point] {
    let approxFuncs: [([Point]) -> [Point]] = [variant1, variant2, variant3, variant4]
    var errorResults = [Double]()
    
    for approxFunc in approxFuncs {
        errorResults.append(funcError(points, approxFunc(points)))
    }
    
    var minIndex = 0,
        minValue = errorResults[0]
    for i in 0..<errorResults.count {
        if errorResults[i] < minValue {
            minIndex = i
            minValue = errorResults[i]
        }
    }
    
    return approxFuncs[minIndex]
}

variant1(originPoints)
print()
variant2(originPoints)
print()
variant3(originPoints)
print()
variant4(originPoints)
