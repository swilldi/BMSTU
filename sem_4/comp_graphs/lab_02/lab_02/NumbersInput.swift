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
    
    @Binding var x: Double
    @Binding var y: Double
    
    var body: some View {
        GroupBox(title) {
            Spinbox(title: "x:", value: $x)
            Spinbox(title: "y:", value: $y)
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
            Spinbox(title: "Угол:", value: $angle)
            if let action = action {
                Button(action: action) {
                    Text(actionTitle)
                        .frame(maxWidth: .infinity, minHeight: 30)
                }
            }
        }
        
    }
}

