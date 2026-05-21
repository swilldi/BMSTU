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
    var mode: AppMode = .segments
    var clipperAlgorithm: Algorithm = .cohenSutherland
    var lineConstraint: LineConstraint = .free
    
    var segments = [Segment]()
    var clippedSegments = [Segment]()
    var rectClipper: CGRect? = nil
    
    var polygon: [CGPoint] = []
    var isPolygonClosed = false
    
    var clipperColor: Color = .blue
    var segmentColor: Color = .black
    var clippedSegmentsColor: Color = .red
    
    var firstPoint: CGPoint? = nil
    
    var hoverPoint: CGPoint? = nil
    
    var canClip: Bool {
        guard !segments.isEmpty else { return false }
        
        switch clipperAlgorithm {
        case .cohenSutherland:
            return rectClipper != nil
        case .cyrusBeck:
            return isPolygonClosed
        }

        return false
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
            
        case (.clipper, .cyrusBeck):
            guard !isPolygonClosed else { return }
            polygon.append(point)
            
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
        switch lineConstraint {
        case .free: return end
        case .horizontal: return CGPoint(x: end.x, y: start.y)
        case .vertical: return CGPoint(x: start.x, y: end.y)
        }
    }
    
    func clip() {
        switch clipperAlgorithm {
        case .cohenSutherland:
            guard let rect = rectClipper else { return }
            clippedSegments = cohenSutherland(segments, rect)
        case .cyrusBeck:
            clippedSegments = cyrusBeck(segments, polygon)
        }
    }
}

