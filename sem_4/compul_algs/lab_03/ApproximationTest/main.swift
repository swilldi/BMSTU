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



let f1 = variant1(originPoints)
let f2 = variant2(originPoints)
let f3 = variant3(originPoints)
let f4 = variant4(originPoints)
print(chooseBetter(originPoints, [f1, f2, f3, f4]))

print()
print(f1)
print(f2)
print(f3)
print(f4)
