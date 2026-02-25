//
//  Spinbox.swift
//  lab_02
//
//  Created by Dmitriy Dudurev on 24.02.2026.
//

import SwiftUI

struct Spinbox: View {
    var title: String = "Sample text: "
    @Binding var value: Double
    
    var body: some View {
        HStack {
            Text(title)
            TextField("", value: $value, format: .number)
                .frame(width: 80)
                .textFieldStyle(.roundedBorder)
                .padding(.trailing, -10)
            Stepper("", value: $value, in: -100...100, step: 0.1)
        }
    }
}


