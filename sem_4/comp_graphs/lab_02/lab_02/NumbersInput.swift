//
//  CoordsInput.swift
//  lab_02
//
//  Created by Dmitriy Dudurev on 24.02.2026.
//

import SwiftUI

struct NumbersInput: View {
    var title: String = "Название"
    var action: (() -> Void)? = nil
    var actionTitle: String = "Кнопка"
    var range: ClosedRange<Double>
    var step: Double
    
    @Binding var x: Double
    @Binding var y: Double
    
    var body: some View {
        GroupBox(title) {
            Spinbox(title: "x:", value: $x, range: range, step: step)
            Spinbox(title: "y:", value: $y, range: range, step: step)
            if let action = action {
                Button(action: action) {
                    Text(actionTitle)
                        .frame(maxWidth: .infinity, minHeight: 30)
                }
            }
        }
        
    }
}

struct NumberInput: View {
    var title: String = "Название"
    var action: (() -> Void)? = nil
    var actionTitle: String = "Кнопка"
    
    @Binding var angle: Double
    
    var body: some View {
        GroupBox(title) {
            Spinbox(title: "Угол:", value: $angle, range: -360...360, step: 5)
            if let action = action {
                Button(action: action) {
                    Text(actionTitle)
                        .frame(maxWidth: .infinity, minHeight: 30)
                }
            }
        }
        
    }
}

