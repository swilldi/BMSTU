//
//  DifferentialEquations.swift
//  Approximation
//
//  Created by Dmitriy Dudurev on 22.03.2026.
//

import Foundation


private func alphaM2(x: Double) -> Double {
    -3 * pow(x, 2) + 2 * x - 2
}

private func betaM2(x: Double) -> Double {
    -4 * pow(x, 3) + 3 * pow(x, 2) - 6 * x + 2
}

func odeM2(min: Double = 0, max: Double = 1, n: Int = 10) -> (points: [Point], coef: [Double]) {
    let xValues = Array(stride(from: min, through: max, by: (max - min) / Double(n)))
    
    var sumAlpha = 0.0, sumBeta = 0.0, sumAlphaBeta = 0.0,
        sumFreePartsAlpha = 0.0, sumFreePartsBeta = 0.0
    for x in xValues {
        sumAlpha += alphaM2(x: x) * alphaM2(x: x)
        sumBeta += betaM2(x: x) * betaM2(x: x)
        sumAlphaBeta += alphaM2(x: x) * betaM2(x: x)
        sumFreePartsAlpha += (4 * x - 1) * alphaM2(x: x)  // sum: (4x - 1)
        sumFreePartsBeta += (4 * x - 1) * betaM2(x: x)  // sum: (4x - 1)
    }
    
    // Решение уравнение матриц A * c = B, C = (C1, C2)
    let A = [
        [sumAlpha, sumAlphaBeta],
        [sumAlphaBeta, sumBeta]
    ]
    let B = [sumFreePartsAlpha, sumFreePartsBeta]
    
    let coef = solveMatrix(A: A, b: B)
    
    var points = [Point]()
    for x in xValues {
        let u0 = 1 - x
//        let u0 = 2.0
        
        var y = u0
        for (k, c) in coef.enumerated() {
            y += c * pow(x, Double(k + 1)) * (1 - x)
//            y += c * pow(x, Double(k + 1)) * (2 - x)
        }
        points.append(Point(x: x, y: y))
    }
    
    return (points, coef)
}

func gammaM3(x: Double) -> Double {
    -5 * pow(x, 4) + 4 * pow(x, 3) - 12 * pow(x, 2) + 6 * x
}

func odeM3(min: Double = 0, max: Double = 1, n: Int = 10) -> (points: [Point], coef: [Double]) {
    let xValues = Array(stride(from: min, through: max, by: (max - min) / Double(n)))
    
    var sumAlpha = 0.0, sumBeta = 0.0, sumGamma = 0.0,
        sumAlphaBeta = 0.0, sumAlphaGamma = 0.0, sumBetaGamma = 0.0,
        sumFreePartsAlpha = 0.0, sumFreePartsBeta = 0.0, sumFreePartsGamma = 0.0
    for x in xValues {
        sumAlpha += alphaM2(x: x) * alphaM2(x: x)
        sumBeta += betaM2(x: x) * betaM2(x: x)
        sumGamma += gammaM3(x: x) * gammaM3(x: x)
        sumAlphaBeta += alphaM2(x: x) * betaM2(x: x)
        sumAlphaGamma += alphaM2(x: x) * gammaM3(x: x)
        sumBetaGamma += gammaM3(x: x) * betaM2(x: x)
        sumFreePartsAlpha += (4 * x - 1) * alphaM2(x: x)  // sum: (4x - 1)
        sumFreePartsBeta += (4 * x - 1) * betaM2(x: x)  // sum: (4x - 1)
        sumFreePartsGamma += (4 * x - 1) * gammaM3(x: x)  // sum: (4x - 1)
    }
    
    // Решение уравнение матриц A * c = B, C = (C1, C2)
    let A = [
        [sumAlpha, sumAlphaBeta, sumAlphaGamma],
        [sumAlphaBeta, sumBeta, sumBetaGamma],
        [sumAlphaGamma, sumBetaGamma, sumGamma]
    ]
    let B = [sumFreePartsAlpha, sumFreePartsBeta, sumFreePartsGamma]
    
    let coef = solveMatrix(A: A, b: B)
    
    var points = [Point]()
    for x in xValues {
        let u0 = 1 - x
//        let u0 = 2.0
        
        var y = u0
        for (k, c) in coef.enumerated() {
            y += c * pow(x, Double(k + 1)) * (1 - x)
//            y += c * pow(x, Double(k + 1)) * (2 - x)
        }
        points.append(Point(x: x, y: y))
    }
    
    return (points, coef)
}
