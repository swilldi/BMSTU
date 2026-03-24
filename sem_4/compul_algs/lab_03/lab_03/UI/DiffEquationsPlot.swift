//
//  DiffEquationsPlot.swift
//  lab_03
//
//  Created by Dmitriy Dudurev on 22.03.2026.
//

import SwiftUI
import Charts

struct DiffEquationsPlot: View {
    @State var originPoints = [Point]()
    @State var approxPoints = [Point]()
    @State var approxPointsNoWeights = [Point]()
    
    @State var approxPointsM2 = [Point]()
    @State var approxPointsM3 = [Point]()
    @State var coefM2 = [Double]()
    @State var coefM3 = [Double]()
    
    @State var N = 10
    @State var xMin = -0.5
    @State var xMax = 2.0
    
    var body: some View {
        HStack {
            // MARK: Графики
            Chart {
                // исходные точки
                ForEach(approxPointsM2) { point in
                    LineMark(
                        x: .value("X", point.x),
                        y: .value("Y", point.y)
                    )
                    .foregroundStyle(by: .value("Series", "f(x), m=2"))
                }
                
                ForEach(approxPointsM3) { point in
                    LineMark(
                        x: .value("X", point.x),
                        y: .value("Y", point.y)
                    )
                    .foregroundStyle(by: .value("Series", "f(x), m=3"))
                }
            }
            .chartYAxis {
                AxisMarks(position: .leading, values: .stride(by: 0.1)) { value in
                    AxisGridLine()
                        .foregroundStyle(.black)
                    AxisTick()
                    AxisValueLabel()
                        .font(.system(size: 14))
                }
            }
            .chartXAxis {
                AxisMarks(values: .stride(by: 0.1)) { value in
                    AxisGridLine()
                        .foregroundStyle(.black)
                    AxisTick()
                    AxisValueLabel()
                        .font(.system(size: 14))
                }
            }
            .padding()
            .onAppear {
                (approxPointsM2, coefM2) = odeM2(min: xMin, max: xMax, n: N)
                (approxPointsM3, coefM3) = odeM3(min: xMin, max: xMax, n: N)
                print(approxPointsM2)
            }
            
            VStack {
                SpinBox(value: $N, min: 1, max: 10_000, label: "N")
                    .onChange(of: N, updatePoints)
                SpinboxDouble(value: $xMin, min: -20, max: 20, label: "min")
                    .onChange(of: xMin, updatePoints)
                SpinboxDouble(value: $xMax, min: -20, max: 20, label: "max")
                    .onChange(of: xMax, updatePoints)
                
                if !coefM2.isEmpty && !coefM3.isEmpty {
                    let coefM2Formated: [String] = coefM2.map { String(format: "%.3f", $0) }
                    let coefM3Formated: [String] = coefM3.map { String(format: "%.3f", $0) }
                    
                    
                    let equalM2 = Text("m=2:").font(.system(size: 14)).bold()
                    let equalM3 = Text("m=3:").font(.system(size: 14)).bold()
                    Text("\(equalM2)\ty(x) = (1 - x) + \(coefM2Formated[0]) * x(1 - x) + \(coefM2Formated[1]) * x^2(1 - x)")
                        .font(.system(size: 14))
                        .padding(.top)
                        .padding(.horizontal)
                    Text("\(equalM3)\ty(x) = (1 - x) + \(coefM3Formated[0]) * x(1 - x) + \(coefM3Formated[1]) * x^2(1 - x) + \(coefM3Formated[2]) * x^3(1 - x)")
                        .font(.system(size: 14))
                        .padding()
                }
            }
        }
        .padding()
    }
    
    func updatePoints() {
        (approxPointsM2, coefM2) = odeM2(min: xMin, max: xMax, n: N)
        (approxPointsM3, coefM3) = odeM3(min: xMin, max: xMax, n: N)
    }
}
#Preview {
    DiffEquationsPlot()
}
