//
//  ContolPanel.swift
//  lab_07
//
//  Created by Dmitriy Dudurev on 15.05.2026.
//

import SwiftUI

struct ContolPanel: View {
    @Binding var viewModel: CanvasViewModel

    // Привязка рёбер актуальна везде, кроме прямоугольного отсекателя
    private var showsLineConstraint: Bool {
        switch viewModel.mode {
        case .segments, .subjectPolygon:
            return true
        case .clipper:
            return viewModel.clipperAlgorithm != .cohenSutherland
        }
    }

    var body: some View {
        VStack(alignment: .leading, spacing: 16) {
            Text("Режим работы")
                .font(.headline)
            
            // Выбор режима работы
            Picker("", selection: $viewModel.mode) {
                if viewModel.clipperAlgorithm == .sutherlandHodgman {
                    Text("Многоугольник").tag(AppMode.subjectPolygon)
                } else {
                    Text("Отрезки").tag(AppMode.segments)
                }
                Text("Отсекатель").tag(AppMode.clipper)
            }
            .pickerStyle(.segmented)
            .onChange(of: viewModel.clipperAlgorithm) { _, newValue in
                switch (newValue, viewModel.mode) {
                case (.sutherlandHodgman, .segments):
                    viewModel.mode = .subjectPolygon
                case (.cohenSutherland, .subjectPolygon), (.cyrusBeck, .subjectPolygon):
                    viewModel.mode = .segments
                default:
                    break
                }
            }
            
            // Выбор алгоритма для отсекателя
            if viewModel.mode == .clipper {
                Picker("", selection: $viewModel.clipperAlgorithm) {
//                    Text("Коэн-Сазерленд").tag(Algorithm.cohenSutherland)
//                    Text("Кирус-Бек").tag(Algorithm.cyrusBeck)
                    Text("Сазерленда-Ходжмена").tag(Algorithm.sutherlandHodgman)
                }
            }

            // Тип отрезка (свободный / горизонтальный / вертикальный)
            if showsLineConstraint {
                Text("Тип отрезка")
                    .font(.headline)
                Picker("", selection: $viewModel.lineConstraint) {
                    ForEach(LineConstraint.allCases, id: \.self) { c in
                        Text(c.label).tag(c)
                    }
                }
                .pickerStyle(.segmented)
            }

            Divider()
            
            // Выбор цыетов
            Text("Цвета")
                .font(.headline)
            
            HStack {
                Text("Отрезки")
                Spacer()
                ColorPicker("", selection: $viewModel.segmentColor)
            }
            
            HStack {
                Text("Отсекатели")
                Spacer()
                ColorPicker("", selection: $viewModel.clipperColor)
            }
            
            HStack {
                Text("Результат")
                Spacer()
                ColorPicker("", selection: $viewModel.clippedSegmentsColor)
            }
            
            Divider()
            
            // Таблица вершин многоугольников
            if viewModel.clipperAlgorithm == .cyrusBeck {
                PolygonEditor(
                    title: "Вершины отсекателя",
                    points: $viewModel.polygon,
                    isClosed: $viewModel.isPolygonClosed
                )
            }

            if viewModel.clipperAlgorithm == .sutherlandHodgman {
                if viewModel.mode == .clipper {
                    PolygonEditor(
                        title: "Вершины отсекателя",
                        points: $viewModel.polygon,
                        isClosed: $viewModel.isPolygonClosed
                    )
                } else {
                    PolygonEditor(
                        title: "Вершины многоугольника",
                        points: $viewModel.subjectPolygon,
                        isClosed: $viewModel.isSubjectPolygonClosed
                    )
                }
            }

            
            if viewModel.clipperAlgorithm == .cohenSutherland {
                Text("Отсекатель")
                    .font(.headline)
                
                if let rect = viewModel.rectClipper {
                    Text("(\(Int(rect.minX)), \(Int(rect.minY))) — (\(Int(rect.maxX)), \(Int(rect.maxY)))")
                        .font(.caption)
                        .foregroundStyle(.secondary)
                } else {
                    Text("Не задан")
                        .font(.caption)
                        .foregroundStyle(.secondary)
                }
                
                Button("Сбросить отсекатель") {
                    viewModel.rectClipper = nil
                    viewModel.firstPoint = nil
                }
                .disabled(viewModel.rectClipper == nil)
            }
            
            Divider()
            
            VStack {
                if viewModel.clipperAlgorithm != .sutherlandHodgman {
                    Button("Сбросить отрезки") {
                        viewModel.segments = []
                        viewModel.clippedSegments = []
                    }
                    .disabled(viewModel.segments.isEmpty)
                }

                Button("Сбросить результат") {
                    viewModel.clippedSegments = []
                }
                .disabled(viewModel.clippedSegments.isEmpty)

                Button("Отсечь") {
                    viewModel.clip()
                }
                .disabled(!viewModel.canClip)
            }
        }
    }
}

private struct PolygonEditor: View {
    let title: String
    @Binding var points: [CGPoint]
    @Binding var isClosed: Bool

    var body: some View {
        VStack(alignment: .leading, spacing: 8) {
            Text(title)
                .font(.headline)

            Table(points.indices.map { PolygonVertex(index: $0, point: points[$0]) }) {
                TableColumn("N") { v in
                    Text("\(v.index + 1)")
                }
                .width(30)

                TableColumn("x") { v in
                    Text(String(format: "%.1f", v.point.x))
                }

                TableColumn("y") { v in
                    Text(String(format: "%.1f", v.point.y))
                }
            }
            .frame(height: 160)

            HStack {
                Button("Замкнуть многоугольник") {
                    isClosed = true
                }
                .disabled(points.count < 3 || isClosed)

                Spacer()

                Button("Сбросить") {
                    points = []
                    isClosed = false
                }
            }
        }
    }
}


//#Preview {
//    ContolPanel()
//}
