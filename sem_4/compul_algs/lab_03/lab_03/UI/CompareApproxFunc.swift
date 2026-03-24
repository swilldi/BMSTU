//
//  CompareApproxFunc.swift
//  lab_03
//
//  Created by Dmitriy Dudurev on 22.03.2026.
//

import SwiftUI
import Charts


let startPoints: [Point] = [
    .init(x: 0.5, y: 10.5),
    .init(x: 1, y: 1.6),
    .init(x: 1.5, y: 0.55),
    .init(x: 2.0, y: 0.26),
    .init(x: 2.5, y: 0.15),
    .init(x: 3.0, y: 0.08),
]


struct CompareApproxFunc: View {
    enum FuncNumber {
        case v1, v2, v3, v4
    }
    
    let additionLineStyle = StrokeStyle(lineWidth: 2, dash: [2, 10])
    let mainLineStyle = StrokeStyle(lineWidth: 2)
    
    
    @State var betterFunc = FuncNumber.v1
    @State var originPoints = startPoints
    
    @State var approxPointsV1 = [Point]()
    @State var approxPointsV2 = [Point]()
    @State var approxPointsV3 = [Point]()
    @State var approxPointsV4 = [Point]()
    
    @State var f1 = variant1(startPoints)
    @State var f2 = variant2(startPoints)
    @State var f3 = variant3(startPoints)
    @State var f4 = variant4(startPoints)
    
    var body: some View {
        HStack {
            // MARK: Графики
            Chart {
                // исходные точки
                ForEach(originPoints) { point in
                    PointMark(
                        x: .value("X", point.x),
                        y: .value("y", point.y)
                    )
                }
                .foregroundStyle(by: .value("Series", "Исходные точки"))
                
                // ax^b
                ForEach(approxPointsV1) { point in
                    LineMark(
                        x: .value("X", point.x),
                        y: .value("y", point.y)
                    )
                }
                .foregroundStyle(by: .value("Series", "F4(x) = \(f1)"))
                .lineStyle(betterFunc == FuncNumber.v1 ? mainLineStyle : additionLineStyle)
                
                // ax^b
                ForEach(approxPointsV2) { point in
                    LineMark(
                        x: .value("X", point.x),
                        y: .value("y", point.y)
                    )
                }
                .foregroundStyle(by: .value("Series", "F4(x) = \(f2)"))
                .lineStyle(betterFunc == FuncNumber.v2 ? mainLineStyle : additionLineStyle)
                
                // a + b / x
                ForEach(approxPointsV3) { point in
                    LineMark(
                        x: .value("X", point.x),
                        y: .value("y", point.y)
                    )
                }
                .foregroundStyle(by: .value("Series", "F4(x) = \(f3)"))
                .lineStyle(betterFunc == FuncNumber.v3 ? mainLineStyle : additionLineStyle)
                
                // a0 / (a1 + a2 * x)
                ForEach(approxPointsV4) { point in
                    LineMark(
                        x: .value("X", point.x),
                        y: .value("y", point.y)
                    )
                }
                .foregroundStyle(by: .value("Series", "F4(x) = \(f4)"))
                .lineStyle(betterFunc == FuncNumber.v4 ? mainLineStyle : additionLineStyle)
                
                
                
            }
            .chartYAxis {
                AxisMarks(position: .leading, values: .stride(by: 1)) { value in
                    AxisGridLine()
                        .foregroundStyle(.black)
                    AxisTick()
                    AxisValueLabel()
                        .font(.system(size: 14))
                }
            }
            .chartXAxis {
                AxisMarks(values: .stride(by: 1)) { value in
                    AxisGridLine()
                        .foregroundStyle(.black)
                    AxisTick()
                    AxisValueLabel()
                        .font(.system(size: 14))
                }
            }
            .padding()
            
            VStack {
                Text("F1(x) = " + f1.description)
                    .bold(betterFunc == FuncNumber.v1)
                    .padding()
                Text("F2(x) = " + f2.description)
                    .bold(betterFunc == FuncNumber.v2)
                    .padding(.horizontal)
                Text("F3(x) = " + f3.description)
                    .bold(betterFunc == FuncNumber.v3)
                    .padding()
                Text("F4(x) = " + f4.description)
                    .bold(betterFunc == FuncNumber.v4)
                    .padding(.horizontal)
                    
            }
        }
        .padding()
        .onAppear {
            updatePoints(originPoints)
        }
    }
    
    func updatePoints(_ points: [Point]) {
        approxPointsV1 = []
        approxPointsV2 = []
        approxPointsV3 = []
        approxPointsV4 = []
        
        let minX = originPoints.first!.x, maxX = originPoints.last!.x
        
        for x in stride(from: minX, through: maxX, by: (maxX - minX) / 100) {
            approxPointsV1.append(Point(x: x, y: f1.f(x)))
            approxPointsV2.append(Point(x: x, y: f2.f(x)))
            approxPointsV3.append(Point(x: x, y: f3.f(x)))
            approxPointsV4.append(Point(x: x, y: f4.f(x)))
        }
        
//        print(approxPointsV1)
        let betterFun = chooseBetterFunc(originPoints, [f1, f2, f3, f4])
        if betterFun == f1 {
            betterFunc = .v1
        } else if betterFun == f2 {
            betterFunc = .v2
        } else if betterFun == f3 {
            betterFunc = .v3
        } else if betterFun == f4 {
            betterFunc = .v4
        }
        
    }
}

#Preview {
    CompareApproxFunc()
}
