//
//  ControlPanel.swift
//  lab_04
//
//  Created by Dmitriy Dudurev on 14.03.2026.
//

import SwiftUI

struct ControlPanel: View {
    @State var figureSettings = FigureSettings(type: .ellipse)
    
    @Binding var directionCellCount: Int
    @Binding var figures: [Figure]
    @Binding var currentFigure: Figure?
    
    var radiusStep = 1.0, radiusRange: ClosedRange<Double>
    
    init(directionCellCount: Binding<Int>, figures: Binding<[Figure]>, currentFigure: Binding<Figure?>) {
        _directionCellCount = directionCellCount
        _figures = figures
        _currentFigure = currentFigure
        radiusRange = 1...Double(directionCellCount.wrappedValue)
    }
    
    
    var body: some View {
        VStack {
            // MARK: Настройки количества пикселей
            Stepper(value: $directionCellCount, in: 2...100) {
                HStack {
                    Text("Количество пикселей: ")
                    Text("\(directionCellCount)")
                        .padding(.horizontal)
                        .padding(.vertical, 3)
                        .background()
                }
            }
            
            // MARK: Настройки фигуры
            GroupBox {
                Picker("Тип фигуры", selection: $figureSettings.type) {
                    ForEach(FigureType.allCases) { type in
                        Text(type.rawValue).tag(type)
                    }
                }
                
                switch figureSettings.type {
                case .ellipse:
                    Picker("Алгоритм", selection: $figureSettings.ellipseAlgorithms) {
                        ForEach(EllipseDrawingAlgorithms.allCases) { algo in
                            Text(algo.rawValue).tag(algo)
                        }
                    }
                case .cirlce:
                    Picker("Алгоритм", selection: $figureSettings.circleAlgorithms) {
                        ForEach(CircleDrawingAlgorithms.allCases) { algo in
                            Text(algo.rawValue).tag(algo)
                        }
                    }
                case .line:
                    Text("TODO")
                }
                
                GroupBox {
                    switch figureSettings.type {
                    case .ellipse:
                        PointStepper(x: $figureSettings.center.x, y: $figureSettings.center.y, maxValue: directionCellCount)
                        
                        let rxStr = String(format: "%.0f", figureSettings.ellipseXRadius),
                            ryStr = String(format: "%.0f", figureSettings.ellipseYRadius)
                        HStack {
                            Stepper(value: $figureSettings.ellipseXRadius, in: radiusRange, step: radiusStep) {
                                HStack {
                                    Text("rx: ")
                                    Text(rxStr)
                                        .padding(.horizontal)
                                        .padding(.vertical, 3)
                                        .background()
                                }
                            }
                            .padding(.horizontal)
                            
                            Stepper(value: $figureSettings.ellipseYRadius, in: radiusRange, step: radiusStep) {
                                HStack {
                                    Text("ry: ")
                                    Text(ryStr)
                                        .padding(.horizontal)
                                        .padding(.vertical, 3)
                                        .background()
                                }
                            }
                            .padding(.horizontal)
                        }
                    case .cirlce:
                        PointStepper(x: $figureSettings.center.x, y: $figureSettings.center.y, maxValue: directionCellCount)
                        
                        let rStr = String(format: "%.0f", figureSettings.circleRadius)
                        Stepper(value: $figureSettings.circleRadius, in: radiusRange, step: radiusStep) {
                            HStack {
                                Text("r: ")
                                Text(rStr)
                                    .padding(.horizontal)
                                    .padding(.vertical, 3)
                                    .background()
                            }
                            
                        }
                        .padding(.horizontal)
                    case .line:
                        Text("TODO")
                    }
                }
            }
            
            // MARK: Настройки сохраненных фигур
            Button {
                print("Сохранить фигуру")
            } label: {
                Text("Сохранить фигуру")
                    .frame(maxWidth: .infinity)
            }
            
            Button {
                print("Очистить фигуры")
            } label: {
                Text("Очистить фигуры")
                    .frame(maxWidth: .infinity)
            }
        }
        
        .onChange(of: figureSettings) {
            switch figureSettings.type {
            case .cirlce:
                currentFigure = circleFigure()
            case .ellipse:
                currentFigure = ellipseFigure()
            case .line:
                break
            }
        }
    }
    
    func circleFigure() -> Figure {
        var pixels: [Pixel] {
            switch figureSettings.circleAlgorithms {
            case .canonicalEquation:
                return circlePixelsCanonicalEquation(center: figureSettings.center, r: figureSettings.circleRadius)
            case .parametricEquatiob:
                return cirlePixelParametricEquatiob(center: figureSettings.center, r: figureSettings.circleRadius)
            case .bresenham:
                return circlePixelBresenham(center: figureSettings.center, r: figureSettings.circleRadius)
            case .midPoint:
                return circlePixelMidPoint(center: figureSettings.center, r: figureSettings.circleRadius)
            case .library:
                break
            }
            return [Pixel(x: figureSettings.center.x, y: figureSettings.center.y)]
        }
        
        return Figure(pixels, color: .black)
    }
    
    func ellipseFigure() -> Figure {
        var pixels: [Pixel] {
            switch figureSettings.ellipseAlgorithms {
            case .canonicalEquation:
                return ellipsePixelsCanonicalEquation(
                    center: figureSettings.center,
                    rx: figureSettings.ellipseXRadius,
                    ry: figureSettings.ellipseYRadius
                )
            case .parametricEquatiob:
                return ellipsePixelParametricEquatiob(
                    center: figureSettings.center,
                    rx: figureSettings.ellipseXRadius,
                    ry: figureSettings.ellipseYRadius
                )
            case .bresenham:
                return ellipsePixelBresenham(
                    center: figureSettings.center,
                    rx: figureSettings.ellipseXRadius,
                    ry: figureSettings.ellipseYRadius
                )
            case .midPoint:
                return ellipsePixelMidPoint(
                    center: figureSettings.center,
                    rx: figureSettings.ellipseXRadius,
                    ry: figureSettings.ellipseYRadius
                )
            case .library:
                break
            }
            return [Pixel(x: figureSettings.center.x, y: figureSettings.center.y)]
        }
        
        return Figure(pixels, color: .black)
    }
    
}

struct PointStepper: View {
    @Binding var x: CGFloat
    @Binding var y: CGFloat
    
    var range: ClosedRange<CGFloat>
    
    init(x: Binding<CGFloat>, y: Binding<CGFloat>, maxValue: Int) {
        _x = x
        _y = y
        
        range = -CGFloat(maxValue)...CGFloat(maxValue)
    }
    
    var body: some View {
        HStack {
            HStack {
                Stepper(value: $x, in: range) {
                    HStack {
                        Text("x: ")
                        Text(String(format: "%.0f", x))
                            .padding(.horizontal)
                            .padding(.vertical, 3)
                            .background()
                    }
                }
                .padding(.horizontal)
                
                Stepper(value: $y, in: range) {
                    HStack {
                        Text("y: ")
                        Text(String(format: "%.0f", y))
                            .padding(.horizontal)
                            .padding(.vertical, 3)
                            .background()
                    }
                }
                .padding(.horizontal)
            }
        }
    }
}

#Preview {
    ControlPanel(
        directionCellCount: .constant(30),
        figures: .constant([]),
        currentFigure: .constant(Figure([Pixel(x: 0, y: 0)], color: .black))
    )
}
