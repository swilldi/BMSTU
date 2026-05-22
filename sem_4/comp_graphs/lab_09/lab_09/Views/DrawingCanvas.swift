//
//  DrawingCanvas.swift
//  lab_07
//
//  Created by Dmitriy Dudurev on 15.05.2026.
//

import SwiftUI

struct DrawingCanvas: View {
    var viewModel: CanvasViewModel
    let dotSize = 4.0
    
    var body: some View {
        Canvas { context, size in
            switch viewModel.clipperAlgorithm {
            case .cohenSutherland:
                if let rect = viewModel.rectClipper {
                    var path = Path()
                    path.addRect(rect)
                    context.stroke(path, with: .color(viewModel.clipperColor), lineWidth: 2)
                }
                
            case .cyrusBeck, .sutherlandHodgman:
                // ребра
                if viewModel.polygon.count > 1 {
                    var path = Path()
                    path.move(to: viewModel.polygon[0])
                    for point in viewModel.polygon.dropFirst() {
                        path.addLine(to: point)
                    }
                    
                    if viewModel.isPolygonClosed {
                        path.closeSubpath()
                    }
                    
                    context.stroke(path, with: .color(viewModel.clipperColor), lineWidth: 2)
                }
                
                for point in viewModel.polygon {
                    let dot = Path(ellipseIn: CGRect(
                        x: point.x - dotSize / 2, y: point.y - dotSize / 2,
                        width: dotSize, height: dotSize
                    ))
                    context.fill(dot, with: .color(viewModel.clipperColor))
                }
            }

            // Отсекаемый многоугольник (Сазерленд-Ходжмен)
            if viewModel.clipperAlgorithm == .sutherlandHodgman {
                let subject = viewModel.subjectPolygon
                if subject.count > 1 {
                    var path = Path()
                    path.move(to: subject[0])
                    for point in subject.dropFirst() {
                        path.addLine(to: point)
                    }
                    if viewModel.isSubjectPolygonClosed {
                        path.closeSubpath()
                    }
                    context.stroke(path, with: .color(viewModel.segmentColor), lineWidth: 2)
                }

                for point in subject {
                    let dot = Path(ellipseIn: CGRect(
                        x: point.x - dotSize / 2, y: point.y - dotSize / 2,
                        width: dotSize, height: dotSize
                    ))
                    context.fill(dot, with: .color(viewModel.segmentColor))
                }
            }

            // Отрезки
            for segment in viewModel.segments {
                var path = Path()
                path.move(to: segment.p1)
                path.addLine(to: segment.p2)
                context.stroke(path, with: .color(viewModel.segmentColor), lineWidth: 2)
            }
            
            for segment in viewModel.clippedSegments {
                var path = Path()
                path.move(to: segment.p1)
                path.addLine(to: segment.p2)
                context.stroke(path, with: .color(viewModel.clippedSegmentsColor), lineWidth: 2)
            }
            
            // Новая линия
            if let first = viewModel.firstPoint, let hover = viewModel.hoverPoint {
                var path = Path()
                
                switch (viewModel.mode, viewModel.clipperAlgorithm) {
                case (.clipper, .cohenSutherland):
                    let minX = min(first.x, hover.x)
                    let minY = min(first.y, hover.y)
                    let maxX = max(first.x, hover.x)
                    let maxY = max(first.y, hover.y)
                    path.addRect(CGRect(
                        x: minX, y: minY,
                        width: maxX - minX, height: maxY - minY
                    )) 
                    
                default:
                    let endPoint = viewModel.constrainedEnd(from: first, to: hover)
                    path.move(to: first)
                    path.addLine(to: endPoint)
                }
                
                context.stroke(path, with: .color(.gray), lineWidth: 2)
            }

            // Предпросмотр ребра многоугольника с учётом привязки
            if let hover = viewModel.hoverPoint {
                let active: (points: [CGPoint], closed: Bool)?
                switch viewModel.mode {
                case .subjectPolygon:
                    active = (viewModel.subjectPolygon, viewModel.isSubjectPolygonClosed)
                case .clipper where viewModel.clipperAlgorithm != .cohenSutherland:
                    active = (viewModel.polygon, viewModel.isPolygonClosed)
                default:
                    active = nil
                }

                if let active, let last = active.points.last, !active.closed {
                    let end = viewModel.constrainedVertex(hover, appendingTo: active.points)
                    var path = Path()
                    path.move(to: last)
                    path.addLine(to: end)
                    context.stroke(path, with: .color(.gray), lineWidth: 2)
                }
            }

            // динамическая отрисовка
            if let first = viewModel.firstPoint {
                let dot = Path(ellipseIn: CGRect(
                    x: first.x - dotSize / 2, y: first.y - dotSize / 2,
                    width: dotSize, height: dotSize
                ))
                context.fill(dot, with: .color(.indigo))
            }
        }
        .contentShape(Rectangle())
        .onTapGesture { location in
            viewModel.handleClick(at: location)
        }
        .onContinuousHover { phase in
            switch phase {
            case .active(let location):
                viewModel.hoverPoint = location
            case .ended:
                viewModel.hoverPoint = nil
            }
        }
    }
}

//#Preview {
//    DrawingCanvas()
//}
