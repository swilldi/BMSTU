//
//  ColorSelecter.swift
//  lab_03
//
//  Created by Dmitriy Dudurev on 05.03.2026.
//

import SwiftUI
import Foundation

struct ColorSelecter: View {
    let colors: [Color] = [.black, .gray, .blue, .green, .red, .orange]
    @Binding var selectedColor: Color
    
    var body: some View {
        let cols = Array(repeating: GridItem(.fixed(40), spacing: 8), count: 3)

        LazyVGrid(columns: cols, spacing: 8) {
            ForEach(colors, id: \.self) { c in
                c.frame(width: 40, height: 40)
                    .border(borderColor(c), width: 5)
                    .onTapGesture {
                        selectedColor = c
                    }
            }
        }
    }
    
    func borderColor(_ color: Color) -> Color {
        if color == selectedColor {
            return .white
//            return color == .black ? .gray : .black
        } else {
            return .clear
        }
    }
}

#Preview {
    ColorSelecter(selectedColor: .constant(.black))
}
