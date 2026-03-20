//
//  CircleParams.swift
//  lab_04
//
//  Created by Dmitriy Dudurev on 18.03.2026.
//

import SwiftUI

struct CircleParams: View {
    
    enum Param: CaseIterable, Identifiable {
        case count, r1
        
        var id: String {
            return self.label
        }
        
        var label: String {
            switch self {
            case .count:
                return "Количество"
            case .r1:
                return "R1"
            }
        }
    }
    
    @Binding var settings: CircleSpecterSettings
    @State private var selectedParam: Param = .count
    
    var body: some View {
        HStack {
            SpinBox(value: $settings.r0, min: 1, max: 100, label: "R0")
            SpinBox(value: $settings.step, min: 1, max: 100, label: "Шаг")
        }
        
        
        Picker("", selection: $selectedParam) {
            ForEach(Param.allCases) { p in
                Text(p.label).tag(p)
            }
        }
        .frame(maxWidth: 200)
        .labelsHidden()
        .pickerStyle(.segmented)
        
        switch selectedParam {
        case .count:
                SpinBox(value: $settings.count, min: 1, max: 100, label: selectedParam.label)
                .onChange(of: settings.count) {
                    settings.r1 = settings.r0 + settings.step * (settings.count - 1)
                }
        case .r1:
            SpinBox(value: $settings.r1, min: 1, max: 100, label: selectedParam.label)
        }
        
    }
}

#Preview {
    @Previewable @State var settings = CircleSpecterSettings()
    CircleParams(settings: $settings)
}

