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
    
    let additionLineStyle = StrokeStyle(lineWidth: 2, dash: [5, 10])
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
    
    @State var e1 = 0.0
    @State var e2 = 0.0
    @State var e3 = 0.0
    @State var e4 = 0.0
    
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
                .foregroundStyle(by: .value("Series", "F1(x) = \(f1)"))
                .lineStyle(betterFunc == FuncNumber.v1 ? mainLineStyle : additionLineStyle)
                
                // ax^b
                ForEach(approxPointsV2) { point in
                    LineMark(
                        x: .value("X", point.x),
                        y: .value("y", point.y)
                    )
                }
                .foregroundStyle(by: .value("Series", "F2(x) = \(f2)"))
                .lineStyle(betterFunc == FuncNumber.v2 ? mainLineStyle : additionLineStyle)
                
                // a + b / x
                ForEach(approxPointsV3) { point in
                    LineMark(
                        x: .value("X", point.x),
                        y: .value("y", point.y)
                    )
                }
                .foregroundStyle(by: .value("Series", "F3(x) = \(f3)"))
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
            .chartYScale(domain: -10.0...40.0)
            .padding()
            
            VStack {
                Text("F1(x) = " + f1.description + "\nerror: \(String(format: "%.3f", e1))")
                    .bold(betterFunc == FuncNumber.v1)
                    .padding()
                Text("F2(x) = " + f2.description + "\nerror: \(String(format: "%.3f", e2))")
                    .bold(betterFunc == FuncNumber.v2)
                    .padding(.horizontal)
                Text("F3(x) = " + f3.description + "\nerror: \(String(format: "%.3f", e3))")
                    .bold(betterFunc == FuncNumber.v3)
                    .padding()
                Text("F4(x) = " + f4.description + "\nerror: \(String(format: "%.3f", e4))")
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
        let cmpResults = cmpFunc(originPoints, [f1, f2, f3, f4])
        e1 = cmpResults[0]
        e2 = cmpResults[1]
        e3 = cmpResults[2]
        e4 = cmpResults[3]
        
        var minErrorIndex = 0
        for i in 0..<cmpResults.count {
            if cmpResults[i] < cmpResults[minErrorIndex] {
                minErrorIndex = i
            }
        }
        
        if minErrorIndex == 0 {
            betterFunc = .v1
        } else if minErrorIndex == 1 {
            betterFunc = .v2
        } else if minErrorIndex == 2 {
            betterFunc = .v3
        } else if minErrorIndex == 3 {
            betterFunc = .v4
        }
        
    }
}

#Preview {
    CompareApproxFunc()
}
