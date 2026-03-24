//
//  ContentView.swift
//  lab_03
//
//  Created by Dmitriy Dudurev on 21.03.2026.
//

import SwiftUI

struct ContentView: View {
    let views: [(view: AnyView, label: String)] = [
        (AnyView(ApproxPlot()), "Задание 1"),
        (AnyView(ApproxPlot3D()), "Задание 2"),
        (AnyView(CompareApproxFunc()), "Задание 3"),
        (AnyView(DiffEquationsPlot()), "Задание 4"),
    ]
    
    @State private var selected: String? = "Задание 1"
    
    var body: some View {
        NavigationSplitView {
            List(views, id: \.label, selection: $selected) { view in
                Text(view.label)
                    .font(.title3)
                    .padding(.vertical, 4)
            }
            .navigationTitle("Лабораторная 3")
        } detail: {
            if let selected, let view = views.first(where: { $0.label == selected }) {
                view.view
                    .navigationTitle(selected)
            } else {
                Text("Выберите задание")
                    .foregroundStyle(.secondary)
            }
        }
    }
}

#Preview {
    ContentView()
}
