//
//  ContolPanel.swift
//  lab_02
//
//  Created by Dmitriy Dudurev on 24.02.2026.
//

import SwiftUI

struct ContolPanel: View {
    @Binding var model: Model
    
    @Binding var  actionCenterX: Double
    @Binding var  actionCenterY: Double
    

    @State var move_x = 0.0
    @State var move_y = 0.0
    @State var scale_x = 1.0
    @State var scale_y = 1.0
    @State var angle = 0.0
    
    var body: some View {
        VStack {
            
            HStack {
                Button {
                    model.undo()
                    print("Undo")
                } label: {
                    Image(systemName: "arrowshape.backward.circle")
                        .frame(maxWidth: .infinity)
                        .font(.system(size: 20))       
                }
                .disabled(model.undoTransform == nil)
                Spacer()
            }
            
            Divider()
            
            NumbersInput(
                title: "Центр операций",
                action: {
                    actionCenterX = model.centerPoint.x
                    actionCenterY = model.centerPoint.y
                },
                actionTitle: "центр фигуры",
                range: -1000...1000,
                step: 10,
                x: $actionCenterX,
                y: $actionCenterY
                
            )
            NumbersInput(
                title: "Перемещение",
                action: { model.move(x: move_x, y: move_y) },
                actionTitle: "Переместить",
                range: -1000...1000,
                step: 10,
                x: $move_x,
                y: $move_y
            )
            NumberInput(
                title: "Поворот",
                action: { model.rotate(angle: -angle, center: CGPoint(x :actionCenterX, y: actionCenterY)) },
                actionTitle: "Повернуть",
                angle: $angle
            )
            NumbersInput(
                title: "Масштабирование",
                action: { model.scale(kx: scale_x, ky: scale_y, center: CGPoint(x: actionCenterX, y: actionCenterY)) },
                actionTitle: "Масштабировать",
                range: -100...100,
                step: 0.1,
                x: $scale_x,
                y: $scale_y
            )
        }
        .frame(minWidth: 170)
    }
}

