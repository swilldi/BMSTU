//
//  ContentView.swift
//  lab_07
//
//  Created by Dmitriy Dudurev on 14.05.2026.
//

import SwiftUI



struct ContentView: View {
    @State private var viewModel = CanvasViewModel()
    
    var body: some View {
        HStack {
            DrawingCanvas(viewModel: viewModel)
                .frame(maxWidth: .infinity, maxHeight: .infinity)
            
            Divider()
            
            ContolPanel(viewModel: $viewModel)
                .frame(width: 300)
                .padding()
        }
        .frame(minWidth: 900, minHeight: 600)
    }
}

#Preview {
    ContentView()
}
