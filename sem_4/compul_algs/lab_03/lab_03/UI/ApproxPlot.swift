//
//  ApproxPlot.swift
//  lab_03
//
//  Created by Dmitriy Dudurev on 22.03.2026.
//

import SwiftUI
import Charts
internal import UniformTypeIdentifiers


let startP: Double = 1
struct ApproxPlot: View {
    enum PlotModes: String, CaseIterable, Identifiable {
        case showDifferentN = "Различные степени полинома"
        case showDifferentP = "Значение веса точки"
        
        var id: String { rawValue }
    }
    
    @State var plotMode = PlotModes.showDifferentN
    
    
    @State var originPoints: [Point] = [
        .init(x: 1, y: 1),
        .init(x: 2.3, y: 3.26, p: startP),
        .init(x: 3.19, y: 0.78, p: startP),
        .init(x: 4.51, y: 3.96),
        .init(x: 4.51, y: 4.2),
        .init(x: 5.28, y: 2.34),
        .init(x: 6.73, y: 3.23),
    ]
    
    @State var approxPoints = [Point]()
    @State var approxPointsNoWeights = [Point]()
    @State var approxDegree = 2
    
    @State var approxPointsN1 = [Point]()
    @State var approxPointsN2 = [Point]()
    
    @State private var showFilePicker = false
    
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
                
                if !approxPointsN1.isEmpty && !approxPointsN2.isEmpty {
                    // Аппроксимация 1-й степени
                    ForEach(approxPointsN1) { point in
                        LineMark(
                            x: .value("X", point.x),
                            y: .value("y", point.y)
                        )
                    }
                    .foregroundStyle(by: .value("Series", "F(x), N = 1"))
                    
                    // Аппроксимация 2-й степени
                    ForEach(approxPointsN2) { point in
                        LineMark(
                            x: .value("X", point.x),
                            y: .value("y", point.y)
                        )
                    }
                    .foregroundStyle(by: .value("Series", "F(x), N = 2"))
                }
                
                // Аппроксимация N-й степени
                if !approxPoints.isEmpty {
                    ForEach(approxPoints) { point in
                        LineMark(
                            x: .value("X", point.x),
                            y: .value("y", point.y)
                        )
                    }
                    .foregroundStyle(by: .value("Series", "F(x), N = \(approxDegree)"))
                }
                
                if !approxPointsNoWeights.isEmpty {
                    ForEach(approxPointsNoWeights) { point in
                        LineMark(
                            x: .value("X", point.x),
                            y: .value("y", point.y)
                        )
                    }
                    .foregroundStyle(by: .value("Series", "F(x), N = \(approxDegree), без весов"))
                }
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
            .onAppear {
                updatePoints(originPoints)
            }
            
            // MARK: Таблица + Степпер
            VStack {
                
                Picker("", selection: $plotMode) {
                    ForEach(PlotModes.allCases) { mode in
                        Text(mode.rawValue).tag(mode)
                    }
                }
                
                SpinBox(value: $approxDegree, min: 0, max: originPoints.count - 1, label: "N")
                
                Button("Открыть файл") {
                    showFilePicker = true
                }
                .fileImporter(
                    isPresented: $showFilePicker,
                    allowedContentTypes: [.plainText]
                ) { result in
                    switch result {
                    case .success(let url):
                        let points = readPoints2D(from: url)
                        if !points.isEmpty {
                            originPoints = points
                            updatePoints(points)
                        }
                    case .failure(let error):
                        print("Ошибка: \(error)")
                    }
                }
                
                // Таблицу вот сюда
                Table($originPoints) {
                    TableColumn("X") { $point in
                        Text(String(format: "%.4f", point.x))
                    }
                    TableColumn("Y") { $point in
                        Text(String(format: "%.4f", point.y))
                    }
                    TableColumn("P") { $point in
                        TextField("p", value: $point.p, format: .number)
                            .textFieldStyle(.roundedBorder)
                            .onSubmit {
                                updatePoints(originPoints)
                            }
                    }
                }
            }
            
            .onChange(of: approxDegree) {
                updatePoints(originPoints)
            }
            .onChange(of: plotMode) {
                updatePoints(originPoints)
            }
        }
        .padding()
    }
    
    func updatePoints(_ points: [Point]) {
        switch plotMode {
        case .showDifferentN:
            approxPointsN1 = aprox(data: points, n: 1)
            approxPointsN2 = aprox(data: points, n: 2)
            
            if approxDegree > 2 || approxDegree == 0 {
                approxPoints = aprox(data: points, n: approxDegree)
            } else {
                approxPoints = []
            }
        case .showDifferentP:
            approxPointsN1 = []
            approxPointsN2 = []
            
            approxPointsNoWeights = aprox(data: points.map { Point(x: $0.x, y: $0.y) }, n: approxDegree)
            approxPoints = aprox(data: points, n: approxDegree)
        }
        
    }
}

#Preview {
    ApproxPlot()
}
