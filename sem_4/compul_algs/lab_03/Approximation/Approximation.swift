//
//  AproxFunc.swift
//  Approximation
//
//  Created by Dmitriy Dudurev on 21.03.2026.
//

import Foundation

struct Point: Identifiable, CustomStringConvertible {
    let x: Double
    let y: Double
    var p: Double
    
    init(x: Double, y: Double) {
        self.x = x
        self.y = y
        self.p = 1
    }
    
    init(x: Double, y: Double, p: Double) {
        self.x = x
        self.y = y
        self.p = p
    }
    
    let id = UUID()
    
    var description: String {
        "(x: \(x), y: \(y))"
    }
}

private func multFunc<T>(x values: [T], weight p: [Double], _ f1: (T) -> Double, _ f2: (T) -> Double) -> Double {
    var result = 0.0
    for i in 0..<values.count {
        result += p[i] * f1(values[i]) * f2(values[i])
    }
    return result
}

private func multFunc<T>(x values: [T], weight p: [Double], _ yValue: [Double], _ f2: (T) -> Double) -> Double {
    var result = 0.0
    for i in 0..<values.count {
        result += p[i] * yValue[i] * f2(values[i])
    }
    return result
}

func getCoef(data: [Point], n: Int) -> [Double] {
    let n = n + 1
    var xValues = [Double](), yValues = [Double](), pValues = [Double]()
    for point in data {
        xValues.append(point.x)
        yValues.append(point.y)
        pValues.append(point.p)
    }

    var matrOfMultFunc = [[Double]](), vectorOfMultFuncByY = [Double]()
    for i in 0..<n {
        let f1: (Double) -> Double = { x in
            pow(x, Double(i))
        }
        
        // матрица умножения функций
        var row = [Double]()
        for j in 0..<n {
            let f2: (Double) -> Double = { x in
                pow(x, Double(j))
            }
            
            row.append(multFunc(x: xValues, weight: pValues, f1, f2))
        }
        matrOfMultFunc.append(row)
        
        vectorOfMultFuncByY.append(multFunc(x: xValues, weight: pValues, yValues, f1))
    }
    
    return solveMatrix(A: matrOfMultFunc, b: vectorOfMultFuncByY)

}

func aprox(data: [Point], n: Int) -> [Point] {
    let minX = data.first!.x, maxX = data.last!.x
    
    var points = [Point]()

    // получить коэфиенты
    let coef = getCoef(data: data, n: n)
    print("coef (\(n)): \(coef)")
    
//    // пары (x, F(x)) приближенной функции F(x)
//    for point in data {
//        var y = 0.0
//        var x = 1.0
//        
//        // F(x) = a0 * x^0 + a1 * x^1 + ... + an * x^n
//        for i in 0..<coef.count {
//            y += x * coef[i]
//            x *= point.x
//        }
//        
//        points.append(Point(x: point.x, y: y))
//    }
    
    for curX in stride(from: minX, through: maxX, by: (maxX - minX) / 100) {
        var y = 0.0
        var x = 1.0
        
        // F(x) = a0 * x^0 + a1 * x^1 + ... + an * x^n
        for i in 0..<coef.count {
            y += x * coef[i]
            x *= curX
        }
        
        points.append(Point(x: curX, y: y))
    }
    
    return points
}
