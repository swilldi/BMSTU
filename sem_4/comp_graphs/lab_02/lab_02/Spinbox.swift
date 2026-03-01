//
//  Spinbox.swift
//  lab_02
//
//  Created by Dmitriy Dudurev on 24.02.2026.
//

import SwiftUI

struct Spinbox: View {
    var title: String = "Sample text:"
    @Binding var value: Double
    var range: ClosedRange<Double>
    var step: Double = 1

    private var formatter: NumberFormatter {
        let f = NumberFormatter()
        f.numberStyle = .decimal
        f.decimalSeparator = ","      // или "." если хочешь точку
        f.groupingSeparator = ""      // чтобы не было “тысяч”
        f.minimum = NSNumber(value: range.lowerBound)
        f.maximum = NSNumber(value: range.upperBound)
        f.maximumFractionDigits = 4
        return f
    }

    var body: some View {
        HStack {
            Text(title)

            TextField("", value: $value, formatter: formatter)
                .frame(width: 80)
                .textFieldStyle(.roundedBorder)
                .padding(.trailing, -10)

            Stepper("", value: $value, in: range, step: step)
        }
    }
}


