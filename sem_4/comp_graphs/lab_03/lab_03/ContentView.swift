//
//  ContentView.swift
//  lab_03
//
//  Created by Dmitriy Dudurev on 27.02.2026.
//

import SwiftUI


func pointRotate(_ p: CGPoint, angle angleGrad: Int, center: CGPoint) -> CGPoint {
    let x0 = p.x - center.x, y0 = p.y - center.y
    let angle = CGFloat(angleGrad) / 180 * CGFloat.pi
    
    let x = x0 * cos(CGFloat(angle)) - y0 * sin(CGFloat(angle)) + center.x,
        y = x0 * sin(CGFloat(angle)) + y0 * cos(CGFloat(angle)) + center.y
    
    return CGPoint(x: round(x), y: round(y))
}

enum DrawAlgo: String, CaseIterable, Identifiable {
    case dda = "ЦДА"
    case bresenham = "Брезенхема"
    case bresenhamInt = "Брезенхема:\nцелые числа"
    case bresenhamNoStep = "Брезенхема:\nустарнение\nступенчатости"
    case vu = "Ву"
    var id: String { rawValue }
}

enum LineMode: String, CaseIterable, Identifiable {
    case twoPoints = "Две точки"
    case centerAngle = "Угол"
    var id: String { rawValue }
}

struct ContentView: View {
    
    @State var cellCount = 11
    @State var pixelColor: Color = .black
    @State var lines = [PixelLine]()
    
    @State var angle = 0
    @State var algo: DrawAlgo = .bresenham
    @State var linePixels: (CGPoint, CGPoint) -> [Pixel] = lineBresenham
    @State var lineMode = LineMode.twoPoints
    
    @State var x0 = 0
    @State var y0 = 0
    @State var x1 = 0
    @State var y1 = 0
    
    
    
    var body: some View {
        HStack {
            GridCanvasView(cellCount: $cellCount, lines: $lines)
                .onAppear {
                    applyCurrentAlgorithm()
                    updateLine()
                }
            
            Divider()
            
            VStack {
                ColorSelecter(selectedColor: $pixelColor)
                
//                Picker("Алгоритм", selection: $algo) {
//                    ForEach(DrawAlgo.allCases) { alg in
//                        Text(alg.rawValue).tag(alg)
//                    }
//                    .pickerStyle(.inline)
//                }
                
                Divider().padding()
                Text("Режим работы")
                Picker("", selection: $lineMode) {
                        ForEach(LineMode.allCases) { m in
                            Text(m.rawValue).tag(m)
                        }
                    }
                    .pickerStyle(.radioGroup)
                
                Divider().padding()
                Text("Алгоритм")
                Picker("", selection: $algo) {
                        ForEach(DrawAlgo.allCases) { m in
                            Text(m.rawValue).tag(m)
                        }
                    }
                    .pickerStyle(.radioGroup)
                
                Divider().padding()
                Spinbox(title: "Количество клеток", value: $cellCount, range: 5...1000)
                Divider().padding()
                
                if lineMode == .twoPoints {
                    let maxLen = cellCount / 2 - 1
                    let range = -maxLen...maxLen
                    HStack {
                        Spinbox(title: "X0", value: $x0, range: range, step: 1)
                        Spinbox(title: "Y0", value: $y0, range: range, step: 1)
                    }
                    HStack {
                        Spinbox(title: "X1", value: $x1, range: range, step: 1)
                        Spinbox(title: "Y1", value: $y1, range: range, step: 1)
                    }
                } else if lineMode == .centerAngle {
                    Spinbox(title: "Угол", value: $angle, range: -1000...1000)
                }
                
                
                Divider().padding()
                Button {
                    if let line = lines.last {
                        lines.append(line)
                    }
                    updateLine()
                } label: {
                    Text("Сохранить линию")
                        .frame(maxWidth: .infinity)
                }
                
                Button {
                    lines.removeAll()
                    updateLine()
                } label: {
                    Text("Очистить линии")
                        .frame(maxWidth: .infinity)
                }
                
                Spacer()
            }
            
            .onChange(of: cellCount) {
                if cellCount == 0 {
                    return
                }
                if cellCount % 2 == 0 {
                    cellCount += 1
                }
                updateLine()
            }
            .onChange(of: angle) {
                updateLine()
            }
            .onChange(of: pixelColor) {
                updateLine()
            }
            .onChange(of: algo) {
                applyCurrentAlgorithm()
                updateLine()
            }
            .onChange(of: lineMode) {
                updateLine()
            }
            .onChange(of: x0) {
                updateLine()
            }
            .onChange(of: y0) {
                updateLine()
            }
            .onChange(of: x1) {
                updateLine()
            }
            .onChange(of: y1) {
                updateLine()
            }
            
        }
    }

    func applyCurrentAlgorithm() {
        switch algo {
        case .dda:
            linePixels = lineDDA
        case .bresenham:
            linePixels = lineBresenham
        case .bresenhamInt:
            linePixels = bresenhamInt
        case .bresenhamNoStep:
            break
        case .vu:
            break
        }
    }
    
    func updateLine() {
        if lines.count != 0 {
            lines.removeLast()
        }
        
        let cx = cellCount / 2, cy = cellCount / 2
        var startPoint: CGPoint, endPoint: CGPoint
        
        switch lineMode {
        case .twoPoints:
            startPoint = CGPoint(x: cx + x0, y: cy + y0)
            endPoint = CGPoint(x: cx + x1, y: cy + y1)
        case .centerAngle:
            startPoint = CGPoint(x: cx, y: cy)
            endPoint = pointRotate(CGPoint(x: cellCount - 1, y: cy), angle: angle, center: startPoint)
        }
        
        lines.append(PixelLine(pixels: linePixels(startPoint, endPoint), color: pixelColor))
    }
}

#Preview {
    ContentView()
}
