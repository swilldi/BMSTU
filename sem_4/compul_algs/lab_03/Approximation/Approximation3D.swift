//
//  Approximation3D.swift
//  Approximation
//
//  Created by Dmitriy Dudurev on 22.03.2026.
//

import Foundation

struct Point3D: Identifiable {
    let x: Double
    let y: Double
    let z: Double
    var p: Double
    
    init(x: Double, y: Double, z: Double) {
        self.x = x
        self.y = y
        self.z = z
        self.p = 1
    }
    
    init(x: Double, y: Double, z: Double, p: Double) {
        self.x = x
        self.y = y
        self.z = z
        self.p = p
    }
    
    let id = UUID()
}


private func multFunc<T>(x xValues: [T], y yValues: [T], weight p: [Double], _ f1: (T, T) -> Double, _ f2: (T, T) -> Double) -> Double {
    var result = 0.0
    for i in 0..<xValues.count {
        let x = xValues[i], y = yValues[i]
        result += p[i] * f1(x, y) * f2(x, y)
    }
    return result
}

private func multFunc<T>(x xValues: [T], y yValues: [T], weight p: [Double], _ zValues: [Double], _ f2: (T, T) -> Double) -> Double {
    var result = 0.0
    for i in 0..<xValues.count {
        let x = xValues[i], y = yValues[i], z = zValues[i]
        result += p[i] * z * f2(x, y)
    }
    return result
}

private func getCoef3D(data: [Point3D], degrees degreePars: [(x: Double, y: Double)], n: Int) -> [Double] {
    let coefCount = (n + 1) * (n + 2) / 2
    var xValues = [Double](), yValues = [Double](), zValues = [Double](), pValues = [Double]()
    for point in data {
        xValues.append(point.x)
        yValues.append(point.y)
        zValues.append(point.z)
        pValues.append(point.p)
    }

    
    
    
    var matrOfMultFunc = [[Double]](), vectorOfMultFuncByY = [Double]()
    for i in 0..<coefCount {
        let f1: (Double, Double) -> Double = { x, y in
            pow(x, degreePars[i].x) * pow(y, degreePars[i].y)
        }
        
        // матрица умножения функций
        var row = [Double]()
        for j in 0..<coefCount {
            let f2: (Double, Double) -> Double = { x, y in
                pow(x, degreePars[j].x) * pow(y, degreePars[j].y)
            }
            
            row.append(multFunc(x: xValues, y: yValues, weight: pValues, f1, f2))
        }
        matrOfMultFunc.append(row)
        
        vectorOfMultFuncByY.append(multFunc(x: xValues, y: yValues, weight: pValues, zValues, f1))
    }
    
    

    print("\nМатрица A:")
    for row in matrOfMultFunc {
        print(row.map { String(format: "%.2f", $0) }.joined(separator: "\t"))
    }
    print("Вектор b: \(vectorOfMultFuncByY)")
    
    
    
    
    return solveMatrix(A: matrOfMultFunc, b: vectorOfMultFuncByY)

}

func aprox3D(data: [Point3D], n: Int) -> ((Double, Double) -> Double) {
    var points = [Point3D]()
    
    var degreePars = [(x: Double, y: Double)]()
    for a in 0...n {
        for b in 0...(n - a) {
            degreePars.append((Double(a), Double(b)))
        }
    }

    // получить коэфиенты
    let coef = getCoef3D(data: data, degrees: degreePars, n: n)
    
    
//    // пары (x, F(x)) приближенной функции F(x)
//    for point in data {
//        var z = 0.0
//        
//        // F(x) = a0 * x^0 + a1 * x^1 + ... + an * x^n
//        for i in 0..<coef.count {
//            z += coef[i] * pow(point.x, degreePars[i].x) * pow(point.y, degreePars[i].y)
//        }
//        points.append(Point3D(x: point.x, y: point.y, z: z))
//    }
    
    let f: (Double, Double) -> Double = { x, y in
        var z = 0.0

        // F(x) = a0 * x^0 + a1 * x^1 + ... + an * x^n
        for i in 0..<coef.count {
            z += coef[i] * pow(x, degreePars[i].x) * pow(y, degreePars[i].y)
        }
        
        return z
    }
    
    // вывод коэфициентов
    print()
    for (c, p) in zip(coef, degreePars) {
        print("\(p): \(c)")
    }
    //
    
    return f
}
