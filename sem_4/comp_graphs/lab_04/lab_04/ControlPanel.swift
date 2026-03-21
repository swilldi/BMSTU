//
//  ControlPanel.swift
//  lab_04
//
//  Created by Dmitriy Dudurev on 14.03.2026.
//

import SwiftUI

struct CircleSpecterSettings {
    var r0: Int = 1,
        r1: Int = 1,
        step: Int = 1,
        count: Int = 1
}

struct EllipseSpecterSettings {
    enum EditDirection: String, CaseIterable, Identifiable {
        case x = "X", y = "Y"
        
        var id: String {
            rawValue
        }
    }
    
    var rx0: Int = 1,
        ry0: Int = 1,
        r1: Int = 1,
        step: Int = 1,
        count: Int = 1,
        direction: EditDirection = .x
        
}

struct ControlPanel: View {
    @State var figureSettings = FigureSettings(type: .cirlce)
    @State var circleSpecterSettings = CircleSpecterSettings()
    @State var ellipseSpecterSettings = EllipseSpecterSettings()
    
    @Binding var directionCellCount: Int
    @Binding var figures: [Figure]
    @Binding var currentFigure: Figure

    var radiusStep = 1.0, radiusRange: ClosedRange<Double>
    
    init(directionCellCount: Binding<Int>, figures: Binding<[Figure]>, currentFigure: Binding<Figure>) {
        _directionCellCount = directionCellCount
        _figures = figures
        _currentFigure = currentFigure
        radiusRange = 1...Double(directionCellCount.wrappedValue)
    }
    
    
    var body: some View {
        VStack {
            // MARK: Настройки количества пикселей
            ColorSelecter(selectedColor: $figureSettings.color)
            
            // MARK: Настройки количества пикселей
//            Stepper(value: $directionCellCount, in: 2...100) {
//                HStack {
//                    Text("Количество пикселей: ")
//                    Text("\(directionCellCount)")
//                        .padding(.horizontal)
//                        .padding(.vertical, 3)
//                        .background()
//                }
//            }
            SpinBox(value: $directionCellCount, min: 2, max: 100, label: "Количество пикселей ")
            
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
                            .padding(.bottom)
                        
                        HStack {
                            SpinBox(value: $figureSettings.ellipseXRadius, min: Int(radiusRange.lowerBound), max: Int(radiusRange.upperBound), label: "rx ")
                            .padding(.horizontal)
                            SpinBox(value: $figureSettings.ellipseYRadius, min: Int(radiusRange.lowerBound), max: Int(radiusRange.upperBound), label: "ry ")
                            .padding(.horizontal)
                        }
                    case .cirlce:
                        PointStepper(x: $figureSettings.center.x, y: $figureSettings.center.y, maxValue: directionCellCount)
                            .padding(.bottom)
                        
                        SpinBox(value: $figureSettings.circleRadius, min: Int(radiusRange.lowerBound), max: Int(radiusRange.upperBound), label: "rx ")
                        .padding(.horizontal)
                    case .line:
                        Text("TODO")
                    }
                }
                
                GroupBox {
                    switch figureSettings.type {
                    case .ellipse:
                        EllipseParams(settings: $ellipseSpecterSettings)
                    case .cirlce:
                        CircleParams(settings: $circleSpecterSettings)
                    case .line:
                        Text("TODO")
                    }
                    
                    
                    Button {
                        print("Будет построен спектр")
//                        currentFigure = Figure([], color: .black)
                        
                        switch figureSettings.type {
                        case .cirlce:
                            circleSpecter()
                        case .ellipse:
                            ellipseSpecter()
                        case .line:
                            break
                        }
                        
                    } label: {
                        Text("Построить спектр")
                            .frame(maxWidth: .infinity)
                    }
                }
            }
            
            // MARK: Настройки сохраненных фигур
            Button {
                print("Сохранить фигуру")
                figures.append(currentFigure)
            } label: {
                Text("Сохранить фигуру")
                    .frame(maxWidth: .infinity)
            }
            
            Button {
                print("Очистить фигуры")
                figures.removeAll()
                figureUpdate()
            } label: {
                Text("Очистить фигуры")
                    .frame(maxWidth: .infinity)
            }
        }
        
        .onChange(of: figureSettings) {
            figureUpdate()
        }
        .frame(maxWidth: 360)
    }
    
    func figureUpdate() {
        switch figureSettings.type {
        case .cirlce:
            currentFigure = circleFigure()
        case .ellipse:
            currentFigure = ellipseFigure()
        case .line:
            break
        }
    }
    
    func circleSpecter() {
        let r0 = circleSpecterSettings.r0, r1 = circleSpecterSettings.r1, step = circleSpecterSettings.step
        
        print("\(r0) -> \(r1)")
        for r in stride(from: r0, through: r1, by: step) {
            print("Построенна окружность: \(r)")
            figures.append(circleFigure(r: r))
        }
    }
    
    func ellipseSpecter() {
        let rx0 = ellipseSpecterSettings.rx0, ry0 = ellipseSpecterSettings.ry0, step = ellipseSpecterSettings.step,
            r1 = ellipseSpecterSettings.r1
        
//        print("\(r0) -> \(r1)")
        switch ellipseSpecterSettings.direction {
        case .x:
            for r in stride(from: rx0, through: r1, by: step) {
                figures.append(ellipseFigure(rx: r, ry: ry0))
            }
        case .y:
            for r in stride(from: ry0, through: r1, by: step) {
                figures.append(ellipseFigure(rx: rx0, ry: r))
            }
        }
        
    }
    
    func circleFigure(r circleR: Int? = nil) -> Figure {
        var center: CGPoint
        var r: Int
        
        if let circleR = circleR {
            r = circleR
            center = figureSettings.center
        } else {
            r = figureSettings.circleRadius
            center = figureSettings.center
        }
        
        var pixels: [Pixel] {
            switch figureSettings.circleAlgorithms {
            case .canonicalEquation:
                return circlePixelsCanonicalEquation(center: center, r: Double(r))
            case .parametricEquatiob:
                return cirlePixelParametricEquatiob(center: center, r: Double(r))
            case .bresenham:
                return circlePixelBresenham(center: center, r: Double(r))
            case .midPoint:
                return circlePixelMidPoint(center: center, r: Double(r))
            case .library:
                break
            }
            return [Pixel(x: figureSettings.center.x, y: figureSettings.center.y)]
        }
        
        return Figure(pixels, color: figureSettings.color)
    }
    
    func ellipseFigure(rx ellipseRX: Int? = nil, ry ellipseRY: Int? = nil) -> Figure {
        var center: CGPoint
        var rx: Int, ry: Int
        
        if let ellipseRX = ellipseRX, let ellipseRY = ellipseRY {
            rx = ellipseRX
            ry = ellipseRY
            center = CGPoint(x: 0, y: 0)
        } else {
            rx = figureSettings.ellipseXRadius
            ry = figureSettings.ellipseYRadius
            center = figureSettings.center
        }
        
        var pixels: [Pixel] {
            switch figureSettings.ellipseAlgorithms {
            case .canonicalEquation:
                return ellipsePixelsCanonicalEquation(
                    center: center,
                    rx: Double(rx),
                    ry: Double(ry)
                )
            case .parametricEquatiob:
                return ellipsePixelParametricEquatiob(
                    center: center,
                    rx: Double(rx),
                    ry: Double(ry)
                )
            case .bresenham:
                return ellipsePixelBresenham(
                    center: center,
                    rx: Double(rx),
                    ry: Double(ry)
                )
            case .midPoint:
                return ellipsePixelMidPoint(
                    center: center,
                    rx: Double(rx),
                    ry: Double(ry)
                )
            case .library:
                break
            }
            return [Pixel(x: figureSettings.center.x, y: figureSettings.center.y)]
        }
        
        return Figure(pixels, color: figureSettings.color)
    }
    
}

struct PointStepper: View {
    @Binding var x: CGFloat
    @Binding var y: CGFloat
    
    let minValue: Int, maxValue: Int
    
    init(x: Binding<CGFloat>, y: Binding<CGFloat>, maxValue: Int) {
        _x = x
        _y = y
        
        self.minValue = -maxValue
        self.maxValue = maxValue
    }
    
    var body: some View {
        HStack {
            HStack {
                SpinBox(
                    value: Binding(
                        get: { Int(x) },
                        set: { x = CGFloat($0) }
                    ),
                    min: minValue,
                    max: maxValue,
                    label: "x"
                )
                .padding(.horizontal)
                
                SpinBox(
                    value: Binding(
                        get: { Int(y) },
                        set: { y = CGFloat($0) }
                    ),
                    min: minValue,
                    max: maxValue,
                    label: "y"
                )
                .padding(.horizontal)
            }
        }
    }
}


struct VisualComparingSettingsView: View {
    let type: FigureType
    
    var body: some View {
        if type == .cirlce {
            
        } else if type == .ellipse {
            
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
