//
//  ContolPanel.swift
//  lab_07
//
//  Created by Dmitriy Dudurev on 15.05.2026.
//

import SwiftUI

struct ContolPanel: View {
    @Binding var viewModel: CanvasViewModel
    
    var body: some View {
        VStack(alignment: .leading, spacing: 16) {
            Text("Режим работы")
                .font(.headline)
            
            // Выбор режима работы
            Picker("", selection: $viewModel.mode) {
                Text("Отрезки").tag(AppMode.segments)
                Text("Отсеактели").tag(AppMode.clipper)
            }
            .pickerStyle(.segmented)
            
            // Выбор алгоритма для отсекателя
            if viewModel.mode == .clipper {
                Picker("", selection: $viewModel.clipperAlgorithm) {
                    Text("Коэн-Сазерленд").tag(Algorithm.cohenSutherland)
                    Text("Кирус-Бек").tag(Algorithm.cyrusBeck)
                }
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
            
            // Таблица вершин для Кируса-Бека
            if viewModel.clipperAlgorithm == .cyrusBeck {
                Text("Вершины отсекателя")
                    .font(.headline)
                
                Table(viewModel.polygon.indices.map { i in
                    PolygonVertex(index: i, point: viewModel.polygon[i])
                }) {
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
                .frame(height: 200)
                
                HStack {
                    Button("Закрыть многоугольник") {
                        viewModel.isPolygonClosed = true
                    }
                    .disabled(viewModel.polygon.count < 3 || viewModel.isPolygonClosed)
                    
                    Spacer()
                    
                    Button("Сбросить") {
                        viewModel.polygon = []
                        viewModel.isPolygonClosed = false
                    }
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
                Button("Сбросить отрезки") {
                    viewModel.segments = []
                }
                .disabled(viewModel.segments.isEmpty)
                
                Button("Отсечь") {
                    viewModel.clip()
                }
                .disabled(!viewModel.canClip)
            }
        }
    }
}


//#Preview {
//    ContolPanel()
//}
