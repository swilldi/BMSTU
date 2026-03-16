//
//  ContentView.swift
//  lab_04
//
//  Created by Dmitriy Dudurev on 13.03.2026.
//

import SwiftUI

struct ContentView: View {
    @State var figures = [Figure]()
    @State var currentFigure: Figure? = Figure([.init(x: 0, y: 0)], color: .black)
    @State var directionCellCount = 5
    
    var body: some View {
        NavigationStack {
            HStack {
                PixelCanvas(figures: $figures, currentFigure: $currentFigure, directionCellCount: $directionCellCount)
                ControlPanel(
                    directionCellCount: $directionCellCount,
                    figures: $figures,
                    currentFigure: $currentFigure
                )
            }
            
            .onChange(of: currentFigure) {
                guard let figure = currentFigure else { return }
                
                print(figure)
            }
            
        }
        
    }
    
    
}




#Preview {
    ContentView()
}
