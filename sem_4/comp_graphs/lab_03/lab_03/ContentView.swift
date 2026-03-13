//
//  ContentView.swift
//  lab_03
//
//  Created by Dmitriy Dudurev on 27.02.2026.
//

import SwiftUI


func pointRotate(_ p: CGPoint, angle angleGrad: Int, center: CGPoint) -> CGPoint {
    let x0 = p.x - center.x, y0 = p.y - center.y
    let angle = CGFloat(angleGrad) / 180 * CGFloat.pi
    
    let x = x0 * cos(CGFloat(angle)) - y0 * sin(CGFloat(angle)) + center.x,
        y = x0 * sin(CGFloat(angle)) + y0 * cos(CGFloat(angle)) + center.y
    
    return CGPoint(x: round(x), y: round(y))
}

enum DrawAlgo: String, CaseIterable, Identifiable {
    case dda = "ЦДА"
    case bresenham = "Брезенхема"
    case bresenhamInt = "Брезенхема:\nцелые числа"
    case bresenhamNoStep = "Брезенхема:\nустарнение\nступенчатости"
    case vu = "Ву"
    var id: String { rawValue }
}

enum LineMode: String, CaseIterable, Identifiable {
    case twoPoints = "Две точки"
    case centerAngle = "Угол"
    var id: String { rawValue }
}

struct ContentView: View {
    
    @State var cellCount = 101
    @State var pixelColor: Color = .black
    @State var lines = [PixelLine]()
    
    @State var angle = 0
    @State var angleSpecter = 5
    @State var algo: DrawAlgo = .dda
    @State var linePixels: (CGPoint, CGPoint) -> [Pixel] = lineVu
    @State var lineMode = LineMode.twoPoints
    
    @State var x0 = 0
    @State var y0 = 0
    @State var x1 = 0
    @State var y1 = 0
    
    
    
    var body: some View {
        NavigationStack {
            HStack {
                GridCanvasView(cellCount: $cellCount, lines: $lines)
                    .onAppear {
                        applyCurrentAlgorithm()
                        updateLine()
                    }
                
                Divider()
                
                VStack {
                    Spinbox(title: "Количество клеток", value: $cellCount, range: 5...1000, step: 2)
                        .padding(.top)
                    Divider().padding()
                    
                    ColorSelecter(selectedColor: $pixelColor)
                    
                    Divider().padding()
                    Text("Алгоритм").font(.headline)
                    Picker("", selection: $algo) {
                        ForEach(DrawAlgo.allCases) { m in
                            Text(m.rawValue).tag(m)
                        }
                    }
                    .pickerStyle(.radioGroup)
                    
                    Divider().padding()
                    
                    Text("Режим работы").font(.headline)
                    Picker("", selection: $lineMode) {
                        ForEach(LineMode.allCases) { m in
                            Text(m.rawValue).tag(m)
                        }
                    }
                    .pickerStyle(.radioGroup)
                    
                    
                    GroupBox {
                        if lineMode == .twoPoints {
                            let maxLen = cellCount / 2 - 1
                            let range = -maxLen...maxLen
                            HStack {
                                Spinbox(title: "X0", value: $x0, range: range, step: 1)
                                Spinbox(title: "Y0", value: $y0, range: range, step: 1)
                            }
                            HStack {
                                Spinbox(title: "X1", value: $x1, range: range, step: 1)
                                Spinbox(title: "Y1", value: $y1, range: range, step: 1)
                            }
                        } else if lineMode == .centerAngle {
                            Spinbox(title: "Угол", value: $angle, range: -1000...1000)
                        }
                    }
                    .padding(.top)
                    
                    Divider().padding(.vertical, 5)
                    
                    GroupBox {
                        Spinbox(title: "Шаг спектра", value: $angleSpecter, range: 1...360, step: 1)
                        Button {
                            addSpecterAngleLines()
                        } label: {
                            Text("Построить спектр")
                                .frame(maxWidth: .infinity)
                        }
                    }
                        
                    Divider().padding(.vertical, 5)
                    
                    Button {
                        if let line = lines.last {
                            lines.append(line)
                        }
                        updateLine()
                    } label: {
                        Text("Сохранить линию")
                            .frame(maxWidth: .infinity)
                    }
                    
                    Button {
                        lines.removeAll()
                        updateLine()
                    } label: {
                        Text("Очистить линии")
                            .frame(maxWidth: .infinity)
                    }
                    
                    
                    Spacer()
                }
                
            }
            .navigationTitle("Lab_03")
            .toolbar {
                NavigationLink("Временные характеристики") {
                    TimeTestView()
                }
                NavigationLink("Ступенчатость отрезков") {
                    SteppingLinesView()
                }
            }
        }
                    
            .onChange(of: cellCount) {
                if cellCount == 0 {
                    return
                }
                if cellCount % 2 == 0 {
                    cellCount += 1
                }
                updateLine()
            }
            .onChange(of: angle) {
                updateLine()
            }
            .onChange(of: pixelColor) {
                updateLine()
            }
            .onChange(of: algo) {
                applyCurrentAlgorithm()
                updateLine()
            }
            .onChange(of: lineMode) {
                updateLine()
            }
            .onChange(of: x0) {
                updateLine()
            }
            .onChange(of: y0) {
                updateLine()
            }
            .onChange(of: x1) {
                updateLine()
            }
            .onChange(of: y1) {
                updateLine()
            }
            
        }

    func applyCurrentAlgorithm() {
        switch algo {
        case .dda:
            linePixels = lineDDA
        case .bresenham:
            linePixels = lineBresenham
        case .bresenhamInt:
            linePixels = bresenhamInt
            break
        case .bresenhamNoStep:
            linePixels = bresenhamNoStep
        case .vu:
            linePixels = lineVu
        }
    }
    
    func addSpecterAngleLines() {
        
        let cx = cellCount / 2, cy = cellCount / 2
        var startPoint: CGPoint, endPoint: CGPoint
        
        for angle in stride(from: 0, to: 360, by: angleSpecter) {
            startPoint = CGPoint(x: cx, y: cy)
            endPoint = pointRotate(CGPoint(x: cellCount - 1, y: cy), angle: angle, center: startPoint)
            lines.append(PixelLine(pixels: linePixels(startPoint, endPoint), color: pixelColor))
            if angle + angleSpecter >= 360 {
                lines.append(PixelLine(pixels: linePixels(startPoint, endPoint), color: pixelColor))
            }
        }
    }
    
    func updateLine() {
        if lines.count != 0 {
            lines.removeLast()
        }
        
        let cx = cellCount / 2, cy = cellCount / 2
        var startPoint: CGPoint, endPoint: CGPoint
        
        switch lineMode {
        case .twoPoints:
            startPoint = CGPoint(x: cx + x0, y: cy + y0)
            endPoint = CGPoint(x: cx + x1, y: cy + y1)
        case .centerAngle:
            startPoint = CGPoint(x: cx, y: cy)
            endPoint = pointRotate(CGPoint(x: cellCount - 1, y: cy), angle: angle, center: startPoint)
        }
        
        lines.append(PixelLine(pixels: linePixels(startPoint, endPoint), color: pixelColor))
    }
}

import Charts
let startLineLen = 100, startAngle = 0
struct TimeTestView: View {
        
    @State var lineLen: Int = startLineLen
    @State var angle: Int = startAngle
    
    struct TimeTestResult: Identifiable, CustomStringConvertible {
        let id = UUID()
        let title: String
        let time: Double
        
        var description: String {
            "\(title.replacingOccurrences(of: "\n", with: " ")) – \(time)"
        }
    }
    
    @State var data = [
        TimeTestResult(title: DrawAlgo.dda.rawValue, time: timeToComplete(lineDDA, len: startLineLen, angle: startAngle)),
        TimeTestResult(title: DrawAlgo.bresenham.rawValue, time: timeToComplete(lineBresenham, len: startLineLen, angle: startAngle)),
        TimeTestResult(title: DrawAlgo.bresenhamInt.rawValue, time: timeToComplete(bresenhamInt, len: startLineLen, angle: startAngle)),
        TimeTestResult(title: DrawAlgo.bresenhamNoStep.rawValue, time: timeToComplete(bresenhamNoStep, len: startLineLen, angle: startAngle)),
        TimeTestResult(title: DrawAlgo.vu.rawValue, time: timeToComplete(lineVu, len: startLineLen, angle: startAngle))
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
                    Spinbox(title: "Длина отрезка", value: $lineLen, range: 0...10_000, step: 5)
                        .padding()
                    Spinbox(title: "Угол", value: $angle, range: -360...360, step: 5)
                        .padding(.horizontal)
                        .padding(.bottom)
                }
            }
        }
        .onChange(of: lineLen, dataUpdate)
        .onChange(of: angle, dataUpdate)
    }
    
    
    func dataUpdate() {
        data = [
            TimeTestResult(title: DrawAlgo.dda.rawValue, time: timeToComplete(lineDDA, len: lineLen, angle: angle)),
            TimeTestResult(title: DrawAlgo.bresenham.rawValue, time: timeToComplete(lineBresenham, len: lineLen, angle: angle)),
            TimeTestResult(title: DrawAlgo.bresenhamInt.rawValue, time: timeToComplete(bresenhamInt, len: lineLen, angle: angle)),
            TimeTestResult(title: DrawAlgo.bresenhamNoStep.rawValue, time: timeToComplete(bresenhamNoStep, len: lineLen, angle: angle)),
            TimeTestResult(title: DrawAlgo.vu.rawValue, time: timeToComplete(lineVu, len: lineLen, angle: angle))
        ]
        print(data, "len: \(lineLen), angle: \(angle)")
    }
}

struct SteppingLinesView: View {
    @State private var lineLen = startLineLen
    @State private var typeY: AxisYType = .lenStep
    
    enum AxisYType: String, CaseIterable, Identifiable {
        case countStep = "Количество ступенек"
        case lenStep = "Макс. длина ступеньки"
        var id: String { rawValue }
    }
    
    struct DataPoint: Identifiable {
        let id = UUID()
        let algorithm: String
        let angle: Int
        let value: Int
    }
    
    private let algorithms: [(name: String, line: (CGPoint, CGPoint) -> [Pixel])] = [
        ("ЦДА", lineDDA),
        ("Брезенхем", lineBresenham),
        ("Брезенхем int", bresenhamInt),
        ("Брезенхем сглаж.", bresenhamNoStep),
        ("Ву", lineVu)
    ]
    
    var body: some View {
        HStack {
            Chart(data) { item in
                LineMark(
                    x: .value("Угол", item.angle),
                    y: .value(typeY.rawValue, item.value)
                )
                .foregroundStyle(by: .value("Алгоритм", item.algorithm))
            }
            .chartForegroundStyleScale([
                "ЦДА": .red,
                "Брезенхем": .blue,
                "Брезенхем int": .green,
                "Брезенхем сглаж.": .orange,
                "Ву": .purple
            ])
            .chartXAxis {
                AxisMarks(values: Array(stride(from: 0, through: 90, by: 5))) {
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
            .chartXAxisLabel("Угол (°)")
            .chartYAxisLabel(typeY.rawValue, position: .leading)
            .chartLegend()
            .padding()
            
            Divider()
            
            VStack {
                Picker("Ось OY", selection: $typeY) {
                    ForEach(AxisYType.allCases) { metric in
                        Text(metric.rawValue).tag(metric)
                    }
                }
                .pickerStyle(.segmented)
                .padding()
                
                Spinbox(title: "Длина отрезка", value: $lineLen, range: 5...10_000, step: 5)
                    .padding(.horizontal)
                
                Spacer()
            }
            .frame(width: 320)
        }
    }
    
    private var data: [DataPoint] {
        var result = [DataPoint]()
        result.reserveCapacity(algorithms.count * 91)
        
        for angle in 0...90 {
            let p1 = CGPoint.zero
            let p2 = pointRotate(CGPoint(x: lineLen, y: 0), angle: angle, center: .zero)
            
            for algorithm in algorithms {
                let value = metricValue(algorithm.line(p1, p2))
                result.append(DataPoint(algorithm: algorithm.name, angle: angle, value: value))
            }
        }
        
        return result
    }
    
    private func metricValue(_ rawPixels: [Pixel]) -> Int {
        let pixels = rawPixels.filter { $0.opacity >= 0.5 }
        guard pixels.count > 1 else { return 0 }
        
        let xMajor = abs((pixels.last?.x ?? 0) - pixels[0].x) >= abs((pixels.last?.y ?? 0) - pixels[0].y)
        var stepsCount = 0
        var run = 1
        var maxRun = 1
        
        for i in 1..<pixels.count {
            let prev = pixels[i - 1], cur = pixels[i]
            let sameMinor = xMajor ? (prev.y == cur.y) : (prev.x == cur.x)
            
            if sameMinor {
                run += 1
                maxRun = max(maxRun, run)
            } else {
                stepsCount += 1
                run = 1
            }
        }
        
        return typeY == .countStep ? stepsCount : maxRun
    }
}

#Preview {
    ContentView()
}



func timeToComplete(_ line: (CGPoint, CGPoint) -> [Pixel], len: Int, angle: Int) -> Double {
    let preTestCount = 10, testCount = 3000
    
    let clock = ContinuousClock()
    var time: Double = 0
    
    let p1 = CGPoint(x: 0, y: 0), p2 = pointRotate(CGPoint(x: len, y: 0), angle: angle, center: .zero)
    
    // Прогревочные замеры
    for _ in 0..<preTestCount {
        line(p1, p2)
    }
    
    // Основные замеры
    for _ in 0..<testCount {
        let start = clock.now
        line(p1, p2)
        let end = clock.now
        let elapsed = start.duration(to: end)
        
        time += Double(elapsed.components.seconds) * 1e6 +
                Double(elapsed.components.attoseconds) / 1e12
    }
    
    time /= Double(testCount)
    
    return time  // ms
}
