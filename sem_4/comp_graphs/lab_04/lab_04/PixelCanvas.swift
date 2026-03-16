//
//  PixelCanvas.swift
//  lab_04
//
//  Created by Dmitriy Dudurev on 13.03.2026.
//

import SwiftUI

struct PixelCanvas: View {
    @Binding var figures: [Figure]
    @Binding var currentFigure: Figure?
    @Binding var directionCellCount: Int
    
    struct Metrics {
        let center: CGPoint
        let pixelSize: CGFloat
        
        init(_ size: CGSize, directionCellCount: Int) {
            center = CGPoint(x: size.width / 2, y: size.height / 2)
            pixelSize = size.width / (2 * Double(directionCellCount) + 2)
        }
    }
    
    var body: some View {
        Canvas { context, size in
            let metrics = Metrics(size, directionCellCount: directionCellCount)
            
            let grid = pixelGridPath(metrics)
            for line in grid {
                for pixel in line {
                    context.stroke(pixel, with: .color(.black))
                }
            }
            
            // Сохраненные фигуры
            for figure in figures {
                for pixel in figure.pixels {
                    let x = directionCellCount + pixel.x,
                        y = directionCellCount - pixel.y
                    let color = figure.color.opacity(pixel.opacity)
                    context.fill(grid[y][x], with: .color(color))
                }
            }
            
            // Текущая фигура
            if let figure = currentFigure {
                for pixel in figure.pixels {
                    let x = directionCellCount + pixel.x,
                        y = directionCellCount - pixel.y
                    let color = figure.color.opacity(pixel.opacity)
                    if abs(pixel.y) <= directionCellCount && abs(pixel.x) <= directionCellCount {
                        context.fill(grid[y][x], with: .color(color))
                    }
                        
                }
            }
            
        }
        .aspectRatio(1, contentMode: .fit)
        .border(.black)
        .padding()
        
    }
    
    // Отрисорка сетки
    func pixelGridPath(_ metrics: Metrics) -> [[Path]] {
        let pixelSize = metrics.pixelSize, halfPixelSize = pixelSize / 2
        let pixelCount = 2 * directionCellCount + 1
        
        var grid = [[Path]]()
        for y in 0..<pixelCount {
            grid.append([])
            for x in 0..<pixelCount {
                let pixel = CGRect(
                    x: Double(x + 1) * pixelSize - halfPixelSize,
                    y: Double(y + 1) * pixelSize - halfPixelSize,
                    width: pixelSize,
                    height: pixelSize
                )
                grid[y].append(Path(pixel))
            }
        }
        
        return grid
    }
}

#Preview {
    let pixels = [Pixel(x: 0, y: 0, opacity: 0.4), Pixel(x: 1, y: 0), Pixel(x: 2, y: 1) ]
    let figure = Figure(pixels, color: .red)
    PixelCanvas(
        figures: .constant([figure]),
        currentFigure: .constant(nil),
        directionCellCount: .constant(2)
    )
}
