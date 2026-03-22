//
//  AroundedFuncs.swift
//  Approximation
//
//  Created by Dmitriy Dudurev on 22.03.2026.
//

import Foundation

let digitsAfterDot = 3
struct ApproxedFunc: CustomStringConvertible {
    let f: (Double) -> Double
    
    let a: Double
    let b: Double
    var description: String
}

// MARK: y = ax^b
func variant1(_ originPoints: [Point]) -> ApproxedFunc {
    var linerazePoints = [Point]()
    for point in originPoints {
        linerazePoints.append(.init(x: log(point.x), y: log(point.y)))
    }
    
    let coef = getCoef(data: linerazePoints, n: 1)
    let a = exp(coef[0]), b = coef[1]
    let f: (Double) -> Double = { x in
        a * pow(x, b)
    }
    
    let approxFunc = ApproxedFunc(f: f, a: a, b: b, description: String(format: "%.\(digitsAfterDot)f * x^%.\(digitsAfterDot)f", a, b))
    return approxFunc
}

// MARK: y = ae^(bx)
func variant2(_ originPoints: [Point]) -> ApproxedFunc {
    
    
    var linerazePoints = [Point]()
    for point in originPoints {
        linerazePoints.append(.init(x: point.x, y: log(point.y)))
    }
    
    let coef = getCoef(data: linerazePoints, n: 1)
    let a = exp(coef[0]), b = coef[1]
    let f = { x in
        a * pow(x, b)
    }
    
    let approxFunc = ApproxedFunc(f: f, a: a, b: b, description: String(format: "%.\(digitsAfterDot)f * e^(%.\(digitsAfterDot)f * x)", a, b))
    
    return approxFunc
}

// MARK: y = a + b / x
func variant3(_ originPoints: [Point]) -> ApproxedFunc {
    var linerazePoints = [Point]()
    for point in originPoints {
        linerazePoints.append(.init(x: 1 / point.x, y: point.y))
    }
    
    let coef = getCoef(data: linerazePoints, n: 1)
    let a = coef[0], b = coef[1]
    let f = { x in
        a + b / x
    }
    
    let approxFunc = ApproxedFunc(f: f, a: a, b: b, description: String(format: "%.\(digitsAfterDot)f + %.\(digitsAfterDot)f / x", a, b))
    return approxFunc
}

// MARK: y = a / (b + c * x)
func variant4(_ originPoints: [Point]) -> ApproxedFunc {
    var linerazePoints = [Point]()
    for point in originPoints {
        linerazePoints.append(.init(x: 1 / point.x, y: point.y))
    }
    
    let coef = getCoef(data: linerazePoints, n: 1)
    let a = coef[0], b = coef[1] // a + b * x; a = a1 / a0, b = a2/a0
    let f = { x in
        1 / (a + b * x)
    }
    
    let approxFunc = ApproxedFunc(f: f, a: a, b: b, description: String(format: "1 / (%.\(digitsAfterDot)f * %.\(digitsAfterDot)f * x)", a, b))
    return approxFunc
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

func chooseBetterFunc(_ points: [Point], _ approxFuncs: [ApproxedFunc]) -> ApproxedFunc {
    var errorResults = [Double]()
    
    for approxFunc in approxFuncs {
        var approxPoints = [Point]()
        for point in points {
            approxPoints.append(.init(x: point.x, y: approxFunc.f(point.x)))
        }
        
        errorResults.append(funcError(points, approxPoints))
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
