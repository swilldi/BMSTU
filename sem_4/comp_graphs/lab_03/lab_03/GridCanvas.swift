//
//  Grid.swift
//  lab_03
//
//  Created by Dmitriy Dudurev on 04.03.2026.
//

import Foundation
import SwiftUI

struct PixelLine {
    let pixels: [Pixel]
    let color: Color
}

struct GridCanvasView: View {
    let gridPadding: Int = 10
    
    @Binding var cellCount: Int
    @Binding var lines: [PixelLine]
    
    
    
    struct Metrics {
        let origin: CGPoint
        let cellSize: CGFloat
        let gridSize: CGSize
    }
    
    func metrics(_ size: CGSize) -> Metrics {
//        print(size)
        let w = size.width - 2 * CGFloat(gridPadding), h = size.height - 2 * CGFloat(gridPadding)
        let gridSize = CGSize(width: w, height: h)
        let origin = CGPoint(x: gridPadding, y: gridPadding + Int(h))
        let cellSize = min(h, w) / CGFloat(cellCount)
        
        let m = Metrics(origin: origin, cellSize: cellSize, gridSize: gridSize)
        return m
    }
    
    var body: some View {
        Canvas { context, size in
            let m = metrics(size)
            
            let grid = gridPath(m)
            context.stroke(grid, with: .color(.black), lineWidth: 0.3)
            
//            print(pixels)
            for line in lines {
                var linePath = Path()
                for pixel in line.pixels {
                    linePath.addPath(pixelPath(pixel, m))
                }
                
                context.fill(linePath, with: .color(line.color))
            }
            
            

        }.frame(width: 600, height: 600)
    }
    
    func gridPath(_ m: Metrics) -> Path {
        var grid = Path()
        for k in 0...cellCount {
            grid.move(to: CGPoint(x: m.origin.x + m.cellSize * CGFloat(k), y: m.origin.y))
            grid.addLine(to: CGPoint(x: m.origin.x + m.cellSize * CGFloat(k), y: m.origin.y - m.gridSize.height))
            
            grid.move(to: CGPoint(x: m.origin.x, y: m.origin.y - m.cellSize * CGFloat(k)))
            grid.addLine(to: CGPoint(x: m.origin.x + m.gridSize.width, y: m.origin.y - m.cellSize * CGFloat(k)))
        }
        return grid
    }
    
    func axisPath(_ m: Metrics) -> Path {
        var axis = Path()
        axis.move(to: CGPoint(x: gridPadding, y: gridPadding))
        axis.addLine(to: CGPoint(x: gridPadding, y: gridPadding))
        
        return axis
        
    }
    
    func pixelPath(_ pixel: Pixel, _ m: Metrics) -> Path {
        Path(CGRect(
            x: m.origin.x + CGFloat(pixel.x) * m.cellSize,
            y: m.origin.y - CGFloat(pixel.y + 1) * m.cellSize,
            width: m.cellSize,
            height: m.cellSize,
        ))
//        Path(CGRect(
//                    x: 0,
//                    y: 0,
//                    width: 100,
//                    height: 100
//                ))
        
    }
}


//#Preview {
//    GridCanvasView(cellCount: .constant(20), pixels: .constant([.init(x: 1, y: 1, color: .black)]))
//}
