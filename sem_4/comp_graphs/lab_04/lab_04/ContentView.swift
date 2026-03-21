//
//  ContentView.swift
//  lab_04
//
//  Created by Dmitriy Dudurev on 13.03.2026.
//

import SwiftUI

struct ContentView: View {
    @State var figures = [Figure]()
    @State var currentFigure: Figure = Figure(
        ellipsePixelsCanonicalEquation(center: CGPoint(x: 0, y: 0), rx: 2, ry: 2),
        color: .black
    )
    @State var directionCellCount = 20
    
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
//                guard let figure = currentFigure else { return }
                
                print(currentFigure)
            }
            .navigationTitle("Lab 04")
            .toolbar {
                VStack {
                    HStack {
                        Text("Время построения: ")
                        NavigationLink("Окружность") {
                            CircleTimeTestView()
                        }
                        NavigationLink("Эллипс") {
                            EllipseTimeTestView()
                        }
                    }
                    .padding(.vertical, -5)
                    
                    HStack {
                        Text("График зависимости времени от радиуса: ")
                        NavigationLink("Окружность") {
                            CircleTimeByRTestView()
                        }
                        NavigationLink("Эллипс") {
                            EllipseTimeByRTestView()
                        }
                    }
                }
            }
            
        }
    }
    
    
}




#Preview {
    ContentView()
}
