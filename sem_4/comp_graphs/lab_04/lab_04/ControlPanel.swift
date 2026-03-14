//
//  ControlPanel.swift
//  lab_04
//
//  Created by Dmitriy Dudurev on 14.03.2026.
//

import SwiftUI

enum FigureType: String, CaseIterable, Identifiable {
    case ellipse = "Эллипс"
    case cirlce = "Круг"
    case line = "Линия"
    
    var id: String { rawValue }
}





struct FigureSettings {
    var type: FigureType
    
    // Центр фигуры
    var center: CGPoint = CGPoint(x: 0, y: 0)
    
    // Радиус круга
    var circleRadius: Double = 0
    
    // Радиусы эллипса
    var ellipseXRadius: Double = 0
    var ellipseYRadius: Double = 0
    
    init(type: FigureType) {
        self.type = type
    }
}

struct ControlPanel: View {
    @State var figureSettings = FigureSettings(type: .ellipse)
    
    @Binding var directionCellCount: Int
    
    let radiusRange = 0.0...100.0, radiusStep = 1.0
    
    
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
                
                GroupBox {
                    switch figureSettings.type {
                    case .ellipse:
                        let rxStr = String(format: "%.0f", figureSettings.ellipseXRadius),
                            ryStr = String(format: "%.0f", figureSettings.ellipseYRadius)
                        
                        Stepper(value: $figureSettings.ellipseXRadius, in: radiusRange, step: radiusStep) {
                            HStack {
                                Text("rx: ")
                                Text(rxStr)
                                    .padding(.horizontal)
                                    .padding(.vertical, 3)
                                    .background()
                            }
                        }
                        Stepper(value: $figureSettings.ellipseYRadius, in: radiusRange, step: radiusStep) {
                            HStack {
                                Text("ry: ")
                                Text(ryStr)
                                    .padding(.horizontal)
                                    .padding(.vertical, 3)
                                    .background()
                            }
                        }
                    case .cirlce:
                        let rStr = String(format: "%.0f", figureSettings.circleRadius)
                        Stepper(value: $figureSettings.circleRadius, in: radiusRange, step: radiusStep) {
                            HStack {
                                Text("ry: ")
                                Text(rStr)
                                    .padding(.horizontal)
                                    .padding(.vertical, 3)
                                    .background()
                            }
                        }
                    case .line:
                        Text("TODO")
                    }
                }
            }
            
            // MARK: Настройки
            
        }
    }
}

#Preview {
    ControlPanel(directionCellCount: .constant(30))
}
