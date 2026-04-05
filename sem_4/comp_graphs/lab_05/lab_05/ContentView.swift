//
//  ContentView.swift
//  lab_05
//
//  Created by Dmitriy Dudurev on 04.04.2026.
//

import SwiftUI

struct Point: Identifiable {
    var x: Double
    var y: Double
    
    let id = UUID()
}

struct Edge {
    let p1: Point
    let p2: Point
    let color: Color
    
    init(p1: Point, p2: Point) {
        self.p1 = p1
        self.p2 = p2
        self.color = .black
    }
    
    init(p1: Point, p2: Point, color: Color) {
        self.p1 = p1
        self.p2 = p2
        self.color = color
    }
        
}

let pointRadius = 3.0

struct ContentView: View {
    @State var points = [Point]()
    @State var edges = [Edge]()
    @State var fillingEdges = [Edge]()
    @State var fillingColor = Color.black
    
    @State var cursorPoint = Point(x: 0, y: 0)
    
    @State var inputedPoint = Point(x: 0, y: 0)
    
    @State var fewEdges = false
    
    var body: some View {
        HStack {
            GroupBox("Точка по координатам") {
                VStack {
                    HStack {
                        Text("x: ")
                        TextField("x", value: $inputedPoint.x, format: .number)
                    }
                    
                    HStack {
                        Text("y: ")
                        TextField("y", value: $inputedPoint.y, format: .number)
                    }

                    Button {
                        addPoint(x: inputedPoint.x, y: inputedPoint.y)
                    } label: {
                        Text("Добавить точку")
                            .frame(maxWidth: .infinity, alignment: .center)
                    }
                }
            }
            .frame(maxWidth: 140)
            .padding(.horizontal)
            
            
            GroupBox {
                VStack {
                    Button {
                        // количество точек не достаточно для многоугольника
                        if edges.count < 2 {
                            fewEdges = true
                            return
                        }
                        
                        if let p1 = points.last, let p2 = points.first {
                            edges.append(.init(p1: p1, p2: p2))
                        }
                    } label: {
                        Text("Замкнуть")
                            .frame(maxWidth: .infinity)
                    }
                    
                    Divider()
                    
                    Button {
                        fillingEdges = []
                    } label: {
                        Text("Очистить заполнение")
                            .frame(maxWidth: .infinity)
                    }
                    
                    Button {
                        points = []
                        edges = []
                        fillingEdges = []
                    } label: {
                        Text("Очистить экран")
                            .frame(maxWidth: .infinity)
                    }
                }
            }
            .padding(.trailing)
            
            GroupBox {
                VStack {
                    Button {
                        if edges.count < 2 {
                            fewEdges = true
                            return
                        }
                        
                        fillingEdges = fillingByEdgesWithFlags(points: points, edges: edges)
//                        fillingEdges = Array(fillingEdges[0...10])
                    } label: {
                        Text("Заполнить")
                            .frame(maxWidth: .infinity)
                    }
                    
                    Divider()
                    
                    Button {
                        if edges.count < 2 {
                            fewEdges = true
                            return
                        }
                    } label: {
                        Text("Заполнить с задержкой")
                            .frame(maxWidth: .infinity)
                    }
                    
                    Button {
                        if edges.count < 2 {
                            fewEdges = true
                            return
                        }
                    } label: {
                        Text("Время выполнения")
                            .frame(maxWidth: .infinity)
                    }
                }
            }
            .padding(.trailing)
            
        }
        .alert("Недостаточно ребер", isPresented: $fewEdges) {
            Button("Ok") { }
        }
        
        HStack {
            Canvas { context, size in
                // MARK: Отрисовка ребер контура
                for edge in edges {
                    drawLine(context: context, edge: edge)
                }
                
                // MARK: Отрисовка заполнения
                for edge in fillingEdges {
                    drawLine(context: context, edge: edge, color: fillingColor)
                }
                
                
                // MARK: Отрисовка точек
                for point in points.dropLast() {
                    drawPoint(context: context, point: point, r: pointRadius)
                }
                if let lastPoint = points.last {
                    drawPoint(context: context, point: lastPoint, r: pointRadius + 2, color: .red)
                }
            }
            .onAppear {
                addPoint(x: 100, y: 100)
                addPoint(x: 200, y: 100)
                addPoint(x: 200, y: 200)
                addPoint(x: 100, y: 200)
//                addPoint(x: 100, y: 100)
            }
            .background(Color.white)
            .gesture(
                DragGesture(minimumDistance: 0).onEnded { value in
                    let x = round(value.location.x), y = round(value.location.y)
                    addPoint(x: x, y: y)
                    inputedPoint.x = x
                    inputedPoint.y = y
                    print("(\(x), \(y))")
                }
            )
            .onContinuousHover { phase in
                switch phase {
                case .active(let location):
                    cursorPoint.x = location.x
                    cursorPoint.y = location.y
                case .ended:
                    break
                }
            }
            
            Table(points) {
                TableColumn("x") { point in
                    Text(String(Int(point.x)))
                }
                .width(80)
                
                TableColumn("y") { point in
                    Text(String(Int(point.y)))
                }
                .width(80)
            }
            .frame(maxWidth: 210)
        }
        .padding()
        
        Text("\(Int(cursorPoint.x)) x \(Int(cursorPoint.y))")
            .padding(.leading)
            .padding(.bottom)
            .frame(maxWidth: .infinity, alignment: .leading)
    }
    
    func drawLine(context: GraphicsContext, edge: Edge, color: Color = .black) {
        let line = lineCDA(edge.p1, edge.p2)
        
        for point in line {
            let r = CGRect(x: point.x - 0.5, y: point.y - 0.5, width: 1, height: 1)
            context.fill(Path(r), with: .color(color))
        }
    }
    
    func drawPoint(context: GraphicsContext, point: Point, r: Double, color: Color = .black) {
        let rect = CGRect(x: point.x - r / 2, y: point.y - r / 2, width: r, height: r)
        let circle = Path(ellipseIn: rect)
        context.fill(circle, with: .color(color))
    }
    
    func addPoint(x: Double, y: Double) {
        let point = Point(x: x, y: y)
        
        if let lastPoint = points.last {
            edges.append(.init(p1: lastPoint, p2: point))
            print(edges)
        }
        
        points.append(point)
    }
}

func lineCDA(_ p1: Point, _ p2: Point) -> [Point] {
    var points = [Point]()
    
    let dx = p2.x - p1.x, dy = p2.y - p1.y
    let length = max(abs(dx), abs(dy))
    let xStep = dx / length, yStep = dy / length
    
    var x = p1.x, y = p1.y
    for _ in stride(from: 0.0, through: length, by: 1) {
        points.append(.init(x: round(x), y: round(y)))
        x += xStep
        y += yStep
    }
    
    return points
    
}

#Preview {
    ContentView()
}
