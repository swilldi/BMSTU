//
//  ContentView.swift
//  lab_04
//
//  Created by Dmitriy Dudurev on 13.03.2026.
//

import SwiftUI

struct ContentView: View {
    @State var figures = [Figure]()
    @State var directionCellCount = 5
    
    var body: some View {
        NavigationStack {
            HStack {
                PixelCanvas(figures: $figures, directionCellCount: $directionCellCount)
                ControlPanel(directionCellCount: $directionCellCount)
            }
            
            
        }
        
    }
    
    
}




#Preview {
    ContentView()
}
