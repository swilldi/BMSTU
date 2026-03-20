//
//  TimeTestCircle.swift
//  lab_04
//
//  Created by Dmitriy Dudurev on 19.03.2026.
//

import Foundation
import SwiftUI
import Charts

let startR = 30
struct CircleTimeTestView: View {
    
    @State var r: Int = startR

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
            title: CircleDrawingAlgorithms.canonicalEquation.rawValue,
            time: timeToCompleteCircle(algo: .canonicalEquation, r: startR)
        ),
        TimeTestResult(
            title: CircleDrawingAlgorithms.parametricEquatiob.rawValue,
            time: timeToCompleteCircle(algo: .parametricEquatiob, r: startR)
        ),
        TimeTestResult(
            title: CircleDrawingAlgorithms.bresenham.rawValue,
            time: timeToCompleteCircle(algo: .bresenham, r: startR)
        ),
        TimeTestResult(
            title: CircleDrawingAlgorithms.midPoint.rawValue,
            time: timeToCompleteCircle(algo: .midPoint, r: startR)
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
                    SpinBox(value: $r, min: 0, max: 1000, label: "R")
                        .padding()
                }
            }
        }
        .onChange(of: r, dataUpdate)
    }


    func dataUpdate() {
        data = [
            TimeTestResult(
                title: CircleDrawingAlgorithms.canonicalEquation.rawValue,
                time: timeToCompleteCircle(algo: .canonicalEquation, r: r)
            ),
            TimeTestResult(
                title: CircleDrawingAlgorithms.parametricEquatiob.rawValue,
                time: timeToCompleteCircle(algo: .parametricEquatiob, r: r)
            ),
            TimeTestResult(
                title: CircleDrawingAlgorithms.bresenham.rawValue,
                time: timeToCompleteCircle(algo: .bresenham, r: r)
            ),
            TimeTestResult(
                title: CircleDrawingAlgorithms.midPoint.rawValue,
                time: timeToCompleteCircle(algo: .midPoint, r: r)
            ),
        ]
//        print(data, "len: \(lineLen), angle: \(angle)")
    }
}

let endR = 100, stepR = 5
struct CircleTimeByRTestView: View {
    @State private var r0 = startR
    @State private var r1 = endR
    @State private var step = stepR
    
    struct DataPoint: Identifiable {
        let id = UUID()
        let algorithm: String
        let r: Int
        let time: Double
    }
    
    private let algorithms: [(name: String, algo: CircleDrawingAlgorithms)] = [
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
                let time = timeToCompleteCircle(algo: algorithm.algo, r: r)
                result.append(DataPoint(algorithm: algorithm.name, r: r, time: time))
            }
        }
        
        return result
    }
    

}


func timeToCompleteCircle(algo: CircleDrawingAlgorithms, r: Int) -> Double {
    
    let clock = ContinuousClock()
    var time: Double = 0
    
    // Прогревочные замеры
    for _ in 0..<preTestCount {
        circleFigureTestTime(algo: algo, r: r)
    }
    
    // Основные замеры
    for _ in 0..<testCount {
        let start = clock.now
        circleFigureTestTime(algo: algo, r: r)
        let end = clock.now
        let elapsed = start.duration(to: end)
        
        time += Double(elapsed.components.seconds) * 1e6 +
                Double(elapsed.components.attoseconds) / 1e12
    }
    
    time /= Double(testCount)
    
    return time  // ms
}


func circleFigureTestTime(algo: CircleDrawingAlgorithms, r: Int) -> Void {
    let center = CGPoint(x: 0, y: 0)
    
    var pixels: [Pixel] {
        switch algo {
        case .canonicalEquation:
            return circlePixelsCanonicalEquation(center: center, r: Double(r))
        case .parametricEquatiob:
            return cirlePixelParametricEquatiob(center: center, r: Double(r))
        case .bresenham:
            return circlePixelBresenham(center: center, r: Double(r))
        case .midPoint:
            return circlePixelMidPoint(center: center, r: Double(r))
        case .library:
            break
        }
        return [Pixel(x: 0, y: 0)]
    }
    
    _ = Figure(pixels, color: .black)
}

