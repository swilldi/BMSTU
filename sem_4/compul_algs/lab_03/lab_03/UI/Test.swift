//
//  Test.swift
//  lab_03
//
//  Created by Dmitriy Dudurev on 21.03.2026.
//

import SwiftUI
import Charts

struct Test: View {
    @State var originPoints = [Point]()
    
    
    var body: some View {
        
        
        Chart {
            // MARK: График по исходным точкам
            ForEach(originPoints) { point in
//                LineMark(
//                    x: .value("X", point.x),
//                    y: .value("Y", point.y)
//                )
                
                PointMark(
                    x: .value("X", point.x),
                    y: .value("Y", point.y)
                )
            }
            .foregroundStyle(by: .value("Series", "Исходный график"))
            
            // MARK: График по аппроксимации
            let approxPoints = aprox(data: originPoints, n: 3)
            ForEach(approxPoints) { point in
                LineMark(
                    x: .value("X", point.x),
                    y: .value("Y", point.y)
                )
                
                
                PointMark(
                    x: .value("X", point.x),
                    y: .value("Y", point.y)
                )
                .symbol(.plus)
                .foregroundStyle(.black)
            }
            .foregroundStyle(by: .value("Series", "Аппроксимация, n=\(3)"))
            
        }
        .chartYAxis {
            AxisMarks(position: .leading)
        }
        .padding()
        .onAppear {
            pointsUpdate()
        }
        
    }
//        .chartOverlay { proxy in
//            GeometryReader { geometry in
//                Rectangle()
//                    .fill(.clear)
//                    .contentShape(Rectangle())
//                    .onTapGesture { location in
//                        let origin = geometry[proxy.plotFrame!].origin
//                        
//                        let x = proxy.value(atX: location.x - origin.x, as: Double.self)
//                        let y = proxy.value(atY: location.y - origin.y, as: Double.self)
//                        print("x: \(x); y: \(y)")
//                    }
//            }
//        }
    
    func pointsUpdate() {
        var newPoints = [Point]()
        let f: (Double) -> Double = { x in
            2 * x * x - 3 * x + 10
        }
            
        for x in stride(from: 0.0, through: 10, by: 1) {
            newPoints.append(.init(x: x, y: f(x)))
        }
        
//        newPoints = [
//            .init(x: 0, y: 0),
//            .init(x: 0.5, y: 0.479),
//            .init(x: 1, y: 0.841),
//            .init(x: 1.5, y: 0.997),
//            .init(x: 2, y: 0.909),
//            .init(x: 2.5, y: 0.599),
//            .init(x: 3, y: 0.141),
//        ]
        
        let p: Double = 2
        newPoints = [
            .init(x: 1, y: 1),
            .init(x: 2.3, y: 3.26, p: p),
            .init(x: 3.19, y: 0.78, p: p),
            .init(x: 4.51, y: 3.96),
            .init(x: 4.51, y: 4.2),
            .init(x: 5.28, y: 2.34),
            .init(x: 6.73, y: 3.23),
        ]
        
        originPoints = newPoints
        
        let ap = aprox(data: newPoints, n: 3)
        for i in 0..<ap.count {
//            print("\(originPoints[i].y - ap[i].y)")
//            print("\(originPoints[i].id); \(ap[i].id)")
        }
    }
}

#Preview {
    Test()
}

