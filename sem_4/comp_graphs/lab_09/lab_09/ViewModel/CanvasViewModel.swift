//
//  CanvasViewModel.swift
//  lab_07
//
//  Created by Dmitriy Dudurev on 15.05.2026.
//

import Foundation
import SwiftUI

@Observable
class CanvasViewModel {
    var mode: AppMode = .clipper
    var clipperAlgorithm: Algorithm = .sutherlandHodgman
    var lineConstraint: LineConstraint = .free
    
    var segments = [Segment]()
    var clippedSegments = [Segment]()
    var rectClipper: CGRect? = nil
    
    var polygon: [CGPoint] = []
    var isPolygonClosed = false

    var subjectPolygon: [CGPoint] = []
    var isSubjectPolygonClosed = false
    
    var clipperColor: Color = .blue
    var segmentColor: Color = .black
    var clippedSegmentsColor: Color = .red
    
    var firstPoint: CGPoint? = nil
    
    var hoverPoint: CGPoint? = nil
    
    var canClip: Bool {
        switch clipperAlgorithm {
        case .cohenSutherland:
            return !segments.isEmpty && rectClipper != nil
        case .cyrusBeck:
            return !segments.isEmpty && isPolygonClosed
        case .sutherlandHodgman:
            return isSubjectPolygonClosed && isPolygonClosed
        }
    }
    
    func handleClick(at point: CGPoint) {
        switch (mode, clipperAlgorithm) {
        case (.clipper, .cohenSutherland):
            if let first = firstPoint {
                let minX = min(first.x, point.x)
                let minY = min(first.y, point.y)
                let maxX = max(first.x, point.x)
                let maxY = max(first.y, point.y)
                
                rectClipper = CGRect(x: minX, y: minY, width: maxX - minX, height: maxY - minY)
                firstPoint = nil
            } else {
                firstPoint = point
            }
            
        case (.clipper, .cyrusBeck), (.clipper, .sutherlandHodgman):
            guard !isPolygonClosed else { return }
            polygon.append(constrainedVertex(point, appendingTo: polygon))

        case (.subjectPolygon, _):
            guard !isSubjectPolygonClosed else { return }
            subjectPolygon.append(constrainedVertex(point, appendingTo: subjectPolygon))

        case (.segments, _):
            if let first = firstPoint {
                segments.append(Segment(p1: first, p2: constrainedEnd(from: first, to: point)))
                firstPoint = nil
            } else {
                firstPoint = point
            }
        }
    }

    func constrainedEnd(from start: CGPoint, to end: CGPoint) -> CGPoint {
        guard mode == .segments else { return end }
        return applyConstraint(end, from: start)
    }

    // Привязка вершины многоугольника к предыдущей: горизонтальное / вертикальное ребро
    func constrainedVertex(_ point: CGPoint, appendingTo points: [CGPoint]) -> CGPoint {
        guard let last = points.last else { return point }
        return applyConstraint(point, from: last)
    }

    private func applyConstraint(_ point: CGPoint, from start: CGPoint) -> CGPoint {
        switch lineConstraint {
        case .free: return point
        case .horizontal: return CGPoint(x: point.x, y: start.y)
        case .vertical: return CGPoint(x: start.x, y: point.y)
        }
    }
    
    func clip() {
        switch clipperAlgorithm {
        case .cohenSutherland:
            guard let rect = rectClipper else { return }
            clippedSegments = cohenSutherland(segments, rect)
        case .sutherlandHodgman:
            let resPoints = sutherlandHodgman(subjectPolygon, polygon)

            guard resPoints.count >= 3 else {
                clippedSegments = []
                return
            }

            var result = [Segment]()
            for i in 0..<resPoints.count {
                let p1 = resPoints[i]
                let p2 = resPoints[(i + 1) % resPoints.count]
                result.append(Segment(p1: p1, p2: p2))
            }
            clippedSegments = result
        case .cyrusBeck:
            clippedSegments = cyrusBeck(segments, polygon)
        }
    }
}

