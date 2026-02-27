//
//  ContentView.swift
//  lab_02
//
//  Created by Dmitriy Dudurev on 24.02.2026.
//

import SwiftUI

let cursorLength = 15.0
let cursorColor = Color.blue

struct ContentView: View {
    
    @State var model: Model
    @State var actionCenterX: Double
    @State var actionCenterY: Double
    
    init() {
        let m = Model(
            points: gitara
        )
        _model = State(initialValue: m)
        _actionCenterX = State(initialValue: m.centerPoint.x)
        _actionCenterY = State(initialValue: m.centerPoint.y)
    }
    

    var body: some View {
        HStack {
            GeometryReader { geom in
                Canvas { context, size in
                    let figure = model.drawingPath()
                    context.stroke(figure, with: .color(.black), lineWidth: 1)
                    
                    let cursor = cursorPath()
                    context.stroke(cursor, with: .color(cursorColor), lineWidth: 1.5)
                }
                .onAppear {
                    let targetX = geom.size.width / 2
                    let targetY = geom.size.height / 2

                    let c = model.centerPoint
                    let dx = targetX - c.x
                    let dy = targetY - c.y

                    model.move(x: dx, y: dy)
                    model.undoTransform = nil

                    actionCenterX = Double(targetX)
                    actionCenterY = Double(targetY)
                    
                }
                .frame(maxWidth: .infinity)
                .border(.black, width: 2)
            }
            
            Divider()
            
            VStack {
                ContolPanel(
                    model: $model,
                    actionCenterX: $actionCenterX,
                    actionCenterY: $actionCenterY
                )
                Spacer()
            }
            .frame(width: 150)
        }
        .padding()
    }
    
    func cursorPath() -> Path {
        var path = Path()
        let x = actionCenterX, y = actionCenterY
        
        
        path.move(to: CGPoint(x: x - cursorLength / 2, y: y))
        path.addLine(to: CGPoint(x: x + cursorLength / 2, y: y))
        
        path.move(to: CGPoint(x: x, y: y - cursorLength / 2))
        path.addLine(to: CGPoint(x: x, y: y + cursorLength / 2))
        
        return path
    }
}

#Preview {
    ContentView()
}
