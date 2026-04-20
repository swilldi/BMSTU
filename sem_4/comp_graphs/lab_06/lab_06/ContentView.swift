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
    
    init(x: Double, y: Double) {
        self.x = x
        self.y = y
    }
    
    init(x: Int, y: Int) {
        self.x = Double(x)
        self.y = Double(y)
    }
}

struct Edge: CustomStringConvertible {
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
        
    var description: String {
        "{ from: (\(p1.x), \(p1.y); to: (\(p2.x), \(p2.y) }"
    }
}

let pointRadius = 3.0

struct ContentView: View {
    @State var points = [Point]()
    @State var edges = [Edge]()
    @State var fillingEdges = [Edge]()
    @State var fillingColor = Color.black
    @State var figureIsClosed = false
    @State var timeToComplite: Double? = nil
    
    
    @State var cursorPoint = Point(x: 0, y: 0)

    @State var inputedPoint = Point(x: 0, y: 0)

    @State var fewEdges = false

    // Затравочный алгоритм
    @State var seedFillMode = false
    @State var seedPoint: Point? = nil
    
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
                ColorSelecter(selectedColor: $fillingColor)
                    .padding(3)
            }
            .padding(.trailing)
            
            
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
                            figureIsClosed = true
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
                        figureIsClosed = false
                        seedFillMode = false
                        seedPoint = nil
                    } label: {
                        Text("Очистить экран")
                            .frame(maxWidth: .infinity)
                    }
                }
            }
            .padding(.trailing)
            
            GroupBox("Заполнение") {
                VStack {
                    Button {
                        if edges.count < 2 { fewEdges = true; return }
                        seedFillMode.toggle()
                        fillingEdges = []
                        seedPoint = nil
                    } label: {
                        Text(seedFillMode ? "Отмена" : "Выбрать затравку")
                            .frame(maxWidth: .infinity)
                            .foregroundStyle(seedFillMode ? .red : .blue)
                    }

                    if let seed = seedPoint {
                        Text("Затравка: (\(Int(seed.x)), \(Int(seed.y)))")
                            .font(.caption)
                            .foregroundStyle(.secondary)
                    }

                    Divider()

                    Button {
                        if edges.count < 2 { fewEdges = true; return }
                        guard let seed = seedPoint else { return }
                        fillingEdges = []
                        let bounds = boundingBox(points: points)
                        let fEdges = scanlineSeedFill(seed: seed, polygonEdges: edges, bounds: bounds)

                        // Показываем отрезки в порядке работы алгоритма (стековый порядок).
                        // Батч ~1% от общего числа отрезков за кадр (~16 мс), не менее 1.
                        let batchSize = max(1, fEdges.count / 100)
                        Task { @MainActor in
                            var i = 0
                            while i < fEdges.count {
                                let end = min(i + batchSize, fEdges.count)
                                fillingEdges.append(contentsOf: fEdges[i..<end])
                                i = end
                                try? await Task.sleep(nanoseconds: 16_000_000) // ~1 кадр 60fps
                            }
                        }
                    } label: {
                        Text("Заполнить с задержкой")
                            .frame(maxWidth: .infinity)
                    }
                    .disabled(seedPoint == nil)

                    Button {
                        if edges.count < 2 { fewEdges = true; return }
                        guard let seed = seedPoint else { return }
                        let bounds = boundingBox(points: points)
                        (timeToComplite, fillingEdges) = timeScanlineSeedFill(
                            seed: seed, polygonEdges: edges, bounds: bounds)
                    } label: {
                        Text("Время выполнения")
                            .frame(maxWidth: .infinity)
                    }
                    .disabled(seedPoint == nil)
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

                // MARK: Затравка
                if let seed = seedPoint {
                    drawPoint(context: context, point: seed, r: 8, color: .green)
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

                    if seedFillMode {
                        // Режим затравки: клик задаёт точку и запускает заполнение
                        let seed = Point(x: x, y: y)
                        seedPoint = seed
                        seedFillMode = false
                        let bounds = boundingBox(points: points)
                        fillingEdges = scanlineSeedFill(
                            seed: seed, polygonEdges: edges, bounds: bounds)
                        return
                    }

                    if figureIsClosed { return }

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
        
        HStack {
            
            Text("\(Int(cursorPoint.x)) x \(Int(cursorPoint.y))")
                .padding(.leading)
                .padding(.bottom)
                .frame(maxWidth: .infinity, alignment: .leading)
            
        
            if let time = timeToComplite {
                Text("Время выполнения: " + String(time) + " миллисекунд")
                    .padding(.trailing)
            } else {
                Text("---")
                    .padding(.trailing)
            }
                
        }
    }
    
    func drawLine(context: GraphicsContext, edge: Edge, color: Color = .black) {
        let line = lineDDA(edge.p1, edge.p2)
        
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

func lineDDA(_ p1: Point, _ p2: Point) -> [Point] {
    let x0 = p1.x.rounded(), y0 = p1.y.rounded()
    let x1 = p2.x.rounded(), y1 = p2.y.rounded()

    let dxInt = x1 - x0
    let dyInt = y1 - y0
    let len = max(abs(dxInt), abs(dyInt))
    if len == 0 { return [Point(x: x0, y: y0)] }

    let dx = Double(dxInt) / Double(len)
    let dy = Double(dyInt) / Double(len)

    var x = Double(x0)
    var y = Double(y0)
    var pixels: [Point] = []

    for _ in 0...Int(len) {
        pixels.append(Point(x: x.rounded(), y: y.rounded()))
        x += dx
        y += dy
    }
    return pixels
}

#Preview {
    ContentView()
}
