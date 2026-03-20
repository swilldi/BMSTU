//
//  TimeTestEllipse.swift
//  lab_04
//
//  Created by Dmitriy Dudurev on 19.03.2026.
//

import Foundation
import SwiftUI

import Charts
let startRX = 30, startRY = 20
struct EllipseTimeTestView: View {

    @State var rx: Int = startRX
    @State var ry: Int = startRY

    struct TimeTestResult: Identifiable, CustomStringConvertible {
        let id = UUID()
        let title: String
        let time: Double

        var description: String {
            "\(title.replacingOccurrences(of: "\n", with: " ")) – \(time)"
        }
    }

    @State var data = [
        TimeTestResult(
            title: EllipseDrawingAlgorithms.canonicalEquation.rawValue,
            time: timeToCompleteEllipse(algo: .canonicalEquation, rx: startRX, ry: startRY)
        ),
        TimeTestResult(
            title: EllipseDrawingAlgorithms.parametricEquatiob.rawValue,
            time: timeToCompleteEllipse(algo: .parametricEquatiob, rx: startRX, ry: startRY)
        ),
        TimeTestResult(
            title: EllipseDrawingAlgorithms.bresenham.rawValue,
            time: timeToCompleteEllipse(algo: .bresenham, rx: startRX, ry: startRY)
        ),
        TimeTestResult(
            title: EllipseDrawingAlgorithms.midPoint.rawValue,
            time: timeToCompleteEllipse(algo: .midPoint, rx: startRX, ry: startRY)
        ),
    ]

    var body: some View {
        ZStack {
            Color.clear
//            Text("Будет гистограмма")
//                .font(.largeTitle)
            HStack {
                // Гистограммы
                Chart(data) { item in
                    BarMark(
                        x: .value("Алгоритм", item.title),
                        y: .value("Время", item.time)
                    )
                }
                .chartYAxisLabel("t, мкс", position: .leading)
                .chartXAxisLabel("Алгоритм")
                .chartYAxis {
                    AxisMarks(position: .leading, values: .automatic(desiredCount: 12)) {
                        AxisGridLine()
                        AxisTick()
                        AxisValueLabel()
                    }
                }
                .padding()

                Divider()

                VStack {
                    SpinBox(value: $rx, min: 0, max: 1000, label: "RX")
                        .padding()
                    SpinBox(value: $ry, min: 0, max: 1000, label: "RY")
                        .padding(.horizontal)
                        .padding(.bottom)
                }
            }
        }
        .onChange(of: rx, dataUpdate)
        .onChange(of: ry, dataUpdate)
    }


    func dataUpdate() {
        data = [
            TimeTestResult(
                title: EllipseDrawingAlgorithms.canonicalEquation.rawValue,
                time: timeToCompleteEllipse(algo: .canonicalEquation, rx: startRX, ry: startRY)
            ),
            TimeTestResult(
                title: EllipseDrawingAlgorithms.parametricEquatiob.rawValue,
                time: timeToCompleteEllipse(algo: .parametricEquatiob, rx: startRX, ry: startRY)
            ),
            TimeTestResult(
                title: EllipseDrawingAlgorithms.bresenham.rawValue,
                time: timeToCompleteEllipse(algo: .bresenham, rx: startRX, ry: startRY)
            ),
            TimeTestResult(
                title: EllipseDrawingAlgorithms.midPoint.rawValue,
                time: timeToCompleteEllipse(algo: .midPoint, rx: startRX, ry: startRY)
            ),
        ]
//        print(data, "len: \(lineLen), angle: \(angle)")
    }
}



enum EllipseEditDirection: String, CaseIterable, Identifiable {
    case x = "x", y = "y"
    
    var id: String {
        rawValue
    }
}


let startDirection: EllipseEditDirection = .x
struct EllipseTimeByRTestView: View {
    @State private var r0 = startR
    @State private var r1 = endR
    @State private var step = stepR
    @State private var directcion = startDirection
    
    struct DataPoint: Identifiable {
        let id = UUID()
        let algorithm: String
        let r: Int
        let time: Double
    }
    
    private let algorithms: [(name: String, algo: EllipseDrawingAlgorithms)] = [
        ("Каноническое", .canonicalEquation),
        ("Параметрическое", .parametricEquatiob),
        ("Брезенхем", .bresenham),
        ("Средней точки", .midPoint),
    ]
    
    var body: some View {
        HStack {
            Chart(data) { item in
                LineMark(
                    x: .value("Радиус", item.r),
                    y: .value("t, мкс", item.time)
                )
                .foregroundStyle(by: .value("Алгоритм", item.algorithm))
            }
            .chartXScale(domain: r0...(r1 + step))
            .chartXAxis {
                AxisMarks(values: Array(stride(from: r0, through: r1 + step, by: step))) {
                    AxisGridLine()
                    AxisTick()
                    AxisValueLabel()
                }
            }
            .chartYAxis {
                AxisMarks(position: .leading, values: .automatic(desiredCount: 12)) {
                    AxisGridLine()
                    AxisTick()
                    AxisValueLabel()
                }
            }
            .chartXAxisLabel("R")
            .chartYAxisLabel("t, мкс", position: .leading)
            .chartLegend()
            .padding()
            
            Divider()
            
            VStack {
                SpinBox(value: $r0, min: 1, max: 1000, label: "R0")
                SpinBox(value: $r1, min: 1, max: 1000, label: "R1")
                SpinBox(value: $step, min: 1, max: 1000, label: "step")
                
                Picker("", selection: $directcion) {
                    ForEach(EllipseEditDirection.allCases) { d in
                        Text(d.rawValue).tag(d)
                    }
                }
                .pickerStyle(.segmented)
                .labelsHidden()
                
                Spacer()
            }
            .frame(width: 320)
        }
    }
    
    private var data: [DataPoint] {
        var result = [DataPoint]()
        result.reserveCapacity(algorithms.count * (abs(r1 - r0) + 2) )
        
        for r in stride(from: r0, to: r1 + step, by: step) {
            for algorithm in algorithms {
                
                var time: Double {
                    switch directcion {
                    case .x:
                        timeToCompleteEllipse(algo: algorithm.algo, rx: r, ry: r0)
                    case .y:
                        timeToCompleteEllipse(algo: algorithm.algo, rx: r0, ry: r)
                    }
                }
            
                result.append(DataPoint(algorithm: algorithm.name, r: r, time: time))
            }
        }
        
        return result
    }
    

}



func timeToCompleteEllipse(algo: EllipseDrawingAlgorithms, rx: Int, ry: Int) -> Double {
    
    let clock = ContinuousClock()
    var time: Double = 0
    
    // Прогревочные замеры
    for _ in 0..<preTestCount {
        ellipseFigureTestTime(algo: algo, rx: rx, ry: ry)
    }
    
    // Основные замеры
    for _ in 0..<testCount {
        let start = clock.now
        ellipseFigureTestTime(algo: algo, rx: rx, ry: ry)
        let end = clock.now
        let elapsed = start.duration(to: end)
        
        time += Double(elapsed.components.seconds) * 1e6 +
                Double(elapsed.components.attoseconds) / 1e12
    }
    
    time /= Double(testCount)
    
    return time  // ms
}


func ellipseFigureTestTime(algo: EllipseDrawingAlgorithms, rx: Int, ry: Int) -> Void {
    let center = CGPoint(x: 0, y: 0)
    
    var pixels: [Pixel] {
        switch algo {
        case .canonicalEquation:
            return ellipsePixelsCanonicalEquation(
                center: center,
                rx: Double(rx),
                ry: Double(ry)
            )
        case .parametricEquatiob:
            return ellipsePixelParametricEquatiob(
                center: center,
                rx: Double(rx),
                ry: Double(ry)
            )
        case .bresenham:
            return ellipsePixelBresenham(
                center: center,
                rx: Double(rx),
                ry: Double(ry)
            )
        case .midPoint:
            return ellipsePixelMidPoint(
                center: center,
                rx: Double(rx),
                ry: Double(ry)
            )
        case .library:
            break
        }
        return [Pixel(x: 0, y: 0)]
    }
    
    _ = Figure(pixels, color: .black)
}

#Preview {
    EllipseTimeTestView()
}
