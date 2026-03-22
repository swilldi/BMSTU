//
//  MatrixFunc.swift
//  Approximation
//
//  Created by Dmitriy Dudurev on 21.03.2026.
//

import Foundation

func swapMaxDiagElem(A: inout [[Double]], b: inout [Double], k: Int) {
    var maxIndex: Int = k, maxValue = A[k][k]
    for i in k..<A.count {
        if abs(A[i][k]) > abs(maxValue) {
            maxValue = A[i][k]
            maxIndex = i
        }
    }
    
    (A[k], A[maxIndex]) = (A[maxIndex], A[k])
    (b[k], b[maxIndex]) = (b[maxIndex], b[k])
}


func solveMatrix(A: [[Double]], b: [Double]) -> [Double] {
    let rowCount = A.count, colCount = A[0].count
    var A = A, b = b
    
    // установка на диагональ максимальных элементов
    for i in 0..<rowCount {
        swapMaxDiagElem(A: &A, b: &b, k: i)
    }
    
    // получение верхнетреугольной матрицы
    for i in 0..<rowCount {
        for j in (i + 1)..<rowCount {
            let k = A[j][i] / A[i][i]
            for colInd in 0..<colCount {
                A[j][colInd] -= A[i][colInd] * k
            }
            b[j] -= b[i] * k
        }
    }
    
    // получение итоговых коэфициентов
    var coef = Array(repeating: 0.0, count: rowCount)
    for i in stride(from: rowCount - 1, through: 0, by: -1) {
        var sum = 0.0
        for j in (i + 1)..<colCount {
            sum += A[i][j] * coef[j]
        }
        coef[i] = (b[i] - sum) / A[i][i]
    }
    
    return coef
}

