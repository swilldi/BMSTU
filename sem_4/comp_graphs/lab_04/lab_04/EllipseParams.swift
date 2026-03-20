//
//  CircleParams.swift
//  lab_04
//
//  Created by Dmitriy Dudurev on 18.03.2026.
//

import SwiftUI

struct EllipseParams: View {
    
    @Binding var settings: EllipseSpecterSettings
    
    var body: some View {
        HStack {
            SpinBox(value: $settings.rx0, min: 1, max: 100, label: "RX0")
            SpinBox(value: $settings.ry0, min: 1, max: 100, label: "RY0")
        }
        SpinBox(value: $settings.step, min: 1, max: 100, label: "Шаг")
        
        Picker("", selection: $settings.direction) {
            ForEach(EllipseSpecterSettings.EditDirection.allCases) { d in
                Text(d.rawValue).tag(d)
            }
        }
        .frame(maxWidth: 200)
        .labelsHidden()
        .pickerStyle(.segmented)
    
        SpinBox(value: $settings.r1, min: 1, max: 100, label: "R1")
    }
}

#Preview {
    @Previewable @State var settings = EllipseSpecterSettings()
    EllipseParams(settings: $settings)
}

