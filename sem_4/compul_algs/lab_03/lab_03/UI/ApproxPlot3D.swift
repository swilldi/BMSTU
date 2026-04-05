//
//  ApproxPlot3D.swift
//  lab_03
//
//  Created by Dmitriy Dudurev on 22.03.2026.
//

import SwiftUI
import SceneKit


let startPoints3D: [Point3D] = [
    .init(x: -3.2, y: 2.220446049250313e-16, z: 5.120000000000001),
    .init(x: -2.4, y: 0.8000000000000003, z: 3.2),
//    .init(x: -1.5999999999999999, y: 1.6000000000000003, z: 2.5600000000000005),
//    .init(x: 2.220446049250313e-16, y: -1.5999999999999999, z: 1.2799999999999998),
    .init(x: 2.220446049250313e-16, y: 2.220446049250313e-16, z: 4.930380657631324e-32),
//    .init(x: 0.8000000000000003, y: -2.4, z: 3.2),
    .init(x: 1.6000000000000003, y: -0.7999999999999998, z: 1.6000000000000003),
    .init(x: 4.0, y: 1.6000000000000003, z: 9.280000000000001),
    .init(x: 4.0, y: 4.0, z: 16.0),
]


//var startPoints3D: [Point3D] {
//    let percent = 10
//    
//    var points = [Point3D]()
//    
//    let xMin = -4.0, xMax = 4.0
//    let yMin = -4.0, yMax = 4.0
//    let step = 0.8
//    
//    let a2: Double = 1, b2: Double = 1, p: Double = 1
//    let f: (Double, Double) -> Double = {x, y in
//        (x*x / a2 + y*y / b2) / 2 / p
//    }
//    
//    for x in stride(from: xMin, through: xMax, by: step) {
//        for y in stride(from: yMin, through: yMax, by: step) {
//            if Int.random(in: 0...100) <= percent {
//                points.append(.init(x: x, y: y, z: f(x, y)))
//            }
//        }
//    }
//    
//    for point in points {
//        print(".init(x: \(point.x), y: \(point.y), z: \(point.z),")
//    }
//    
//    return points
//}

struct ApproxPlot3D: View {
    @State var originPoints: [Point3D] = startPoints3D

    @State var approxDegree = 1
    @State var approxFunc: ((Double, Double) -> Double)? = nil

    var body: some View {
        HStack {
            // MARK: 3D сцена
            Group {
                if let f = approxFunc {
                    SceneKitView(points: originPoints, f: f)
                } else {
                    Text("Нет данных")
                        .frame(maxWidth: .infinity, maxHeight: .infinity)
                }
            }
            .frame(minWidth: 400, minHeight: 400)
            .padding()

            // MARK: Панель управления
            VStack(alignment: .leading, spacing: 12) {
                SpinBox(value: $approxDegree, min: 1, max: originPoints.count - 1, label: "N")

                Table($originPoints) {
                    TableColumn("X") { $point in
                        Text(String(format: "%.2f", point.x))
                    }
                    TableColumn("Y") { $point in
                        Text(String(format: "%.2f", point.y))
                    }
                    TableColumn("Z") { $point in
                        Text(String(format: "%.2f", point.z))
                    }
                    TableColumn("P") { $point in
                        TextField("p", value: $point.p, format: .number)
                            .textFieldStyle(.roundedBorder)
                            .onSubmit { updateApprox() }
                    }
                }

                Spacer()
            }
            .padding()
            .onChange(of: approxDegree) { updateApprox() }
        }
        .onAppear { updateApprox() }
    }

    func updateApprox() {
        approxFunc = aprox3D(data: originPoints, n: approxDegree)
    }
}

// MARK: - SceneKit View

struct SceneKitView: NSViewRepresentable {
    let points: [Point3D]
    let f: (Double, Double) -> Double

    func makeNSView(context: Context) -> SCNView {
        let scnView = SCNView()
        scnView.scene = SCNScene()
        scnView.allowsCameraControl = true
        scnView.autoenablesDefaultLighting = true
        scnView.backgroundColor = .white
        return scnView
    }

    func updateNSView(_ scnView: SCNView, context: Context) {
        let testVal = f(1.0, 1.0)
        guard !testVal.isNaN && !testVal.isInfinite else {
            print("Функция возвращает nan/inf, поверхность не строится")
            return
        }
        
        guard let scene = scnView.scene else { return }
        scene.rootNode.childNodes.forEach { $0.removeFromParentNode() }

        // исходные точки — синие сферы
        for point in points {
            let sphere = SCNSphere(radius: 0.05)
            sphere.firstMaterial?.diffuse.contents = NSColor.blue
            let node = SCNNode(geometry: sphere)
            node.position = SCNVector3(point.x, point.z, point.y)
            scene.rootNode.addChildNode(node)
        }

        // поверхность аппроксимации
        addSurface(to: scene)

        // оси координат
        addAxes(to: scene)
    }

    func addSurface(to scene: SCNScene) {
        let steps = 30
        let xMin = points.map(\.x).min()!
        let xMax = points.map(\.x).max()!
        let yMin = points.map(\.y).min()!
        let yMax = points.map(\.y).max()!

        let xStep = (xMax - xMin) / Double(steps)
        let yStep = (yMax - yMin) / Double(steps)

        var vertices = [SCNVector3]()
        var indices = [Int32]()

        for i in 0...steps {
            for j in 0...steps {
                let x = xMin + Double(i) * xStep
                let y = yMin + Double(j) * yStep
                let z = f(x, y)
                vertices.append(SCNVector3(x, z, y))
            }
        }

        for i in 0..<steps {
            for j in 0..<steps {
                let topLeft     = Int32(i * (steps + 1) + j)
                let topRight    = topLeft + 1
                let bottomLeft  = topLeft + Int32(steps + 1)
                let bottomRight = bottomLeft + 1

                indices.append(contentsOf: [topLeft, bottomLeft, topRight])
                indices.append(contentsOf: [topRight, bottomLeft, bottomRight])
            }
        }

        let vertexSource = SCNGeometrySource(vertices: vertices)
        let element = SCNGeometryElement(indices: indices, primitiveType: .triangles)

        let geometry = SCNGeometry(sources: [vertexSource], elements: [element])
        geometry.firstMaterial?.diffuse.contents = NSColor.green.withAlphaComponent(0.6)
        geometry.firstMaterial?.isDoubleSided = true

        scene.rootNode.addChildNode(SCNNode(geometry: geometry))
    }

    func addAxes(to scene: SCNScene) {
        var xMax = CGFloat(points.map(\.x).max()! * 1.3)
        if xMax < 1 {
            xMax = 1
        }
        var yMax = CGFloat(points.map(\.y).max()! * 1.3)
        if yMax < 1 {
            yMax = 1
        }
        var zMax = CGFloat(points.map(\.z).max()! * 1.3)
        if zMax < 1 {
            zMax = 1
        }
        let axisRadius: CGFloat = 0.015
        let fontSize: CGFloat = 0.18
        let labelOffset: CGFloat = 0.15
        let gridColor = NSColor.gray.withAlphaComponent(0.25)
        let gridRadius: CGFloat = 0.005

        func makeCylinder(radius: CGFloat, height: CGFloat, color: NSColor,
                          rotation: SCNVector3, position: SCNVector3) {
            let cyl = SCNCylinder(radius: radius, height: height)
            cyl.firstMaterial?.diffuse.contents = color
            let node = SCNNode(geometry: cyl)
            node.eulerAngles = rotation
            node.position = position
            scene.rootNode.addChildNode(node)
        }

        func makeLabel(_ str: String, color: NSColor, position: SCNVector3) {
            let text = SCNText(string: str, extrusionDepth: 0.01)
            text.font = .systemFont(ofSize: fontSize)
            text.firstMaterial?.diffuse.contents = color
            let node = SCNNode(geometry: text)
            node.position = position
            
            // всегда смотрит на камеру
            let billboard = SCNBillboardConstraint()
            billboard.freeAxes = .all
            node.constraints = [billboard]
            
            scene.rootNode.addChildNode(node)
        }

        // X ось — красная
        makeCylinder(radius: axisRadius, height: xMax, color: .red,
                     rotation: SCNVector3(0, 0, -Double.pi / 2),
                     position: SCNVector3(xMax / 2, 0, 0))
        makeLabel("X", color: .red, position: SCNVector3(xMax + 0.1, -0.15 - 1, 0))
        for k in 1...Int(xMax) {
            let v = CGFloat(k)
            makeCylinder(radius: axisRadius, height: 0.12, color: .red,
                         rotation: SCNVector3(0, 0, 0),
                         position: SCNVector3(v, 0, 0))
            makeLabel("\(k)", color: .red, position: SCNVector3(v - 0.06, labelOffset - 1, 0))
        }

        // Z ось — зелёная (вертикаль)
        makeCylinder(radius: axisRadius, height: zMax, color: .green,
                     rotation: SCNVector3(0, 0, 0),
                     position: SCNVector3(0, zMax / 2, 0))
        makeLabel("Z", color: .green, position: SCNVector3(-0.3, zMax + 0.1 - 1, 0))
        for k in 1...Int(zMax) {
            let v = CGFloat(k)
            makeCylinder(radius: axisRadius, height: 0.12, color: .green,
                         rotation: SCNVector3(0, 0, -Double.pi / 2),
                         position: SCNVector3(0, v, 0))
            makeLabel("\(k)", color: .green, position: SCNVector3(labelOffset, v - 0.06 - 1, 0))
        }

        // Y ось — синяя
        makeCylinder(radius: axisRadius, height: yMax, color: .blue,
                     rotation: SCNVector3(Double.pi / 2, 0, 0),
                     position: SCNVector3(0, 0, yMax / 2))
        makeLabel("Y", color: .blue, position: SCNVector3(0, -0.15 - 1, yMax + 0.1))
        for k in 1...Int(yMax) {
            let v = CGFloat(k)
            makeCylinder(radius: axisRadius, height: 0.12, color: .blue,
                         rotation: SCNVector3(Double.pi / 2, 0, 0),
                         position: SCNVector3(0, 0, v))
            makeLabel("\(k)", color: .blue, position: SCNVector3(0, labelOffset - 1, v - 0.06))
        }

        // сетка на плоскости Z=0 (XY)
        for k in 0...Int(xMax) {
            makeCylinder(radius: gridRadius, height: yMax, color: gridColor,
                         rotation: SCNVector3(Double.pi / 2, 0, 0),
                         position: SCNVector3(CGFloat(k), 0, yMax / 2))
        }
        for k in 0...Int(yMax) {
            makeCylinder(radius: gridRadius, height: xMax, color: gridColor,
                         rotation: SCNVector3(0, 0, -Double.pi / 2),
                         position: SCNVector3(xMax / 2, 0, CGFloat(k)))
        }
    }
}

#Preview {
    ApproxPlot3D()
}
