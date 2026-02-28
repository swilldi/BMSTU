//
//  ContentView.swift
//  lab_03
//
//  Created by Dmitriy Dudurev on 27.02.2026.
//

import SwiftUI

func lineDDA(_ p1: CGPoint, _ p2: CGPoint) -> Path {
    var dx = p2.x - p1.x, dy = p2.y - p1.y, yStep = dy / dx
    var x = p1.x, y = p1.y
    if (abs(dy) > abs(dx)) {
        (dx, dy) = (dy, dx)
        (x, y) = (y, x)
    }
    
    var line = Path()
    line.move(to: CGPoint(x: x, y: y))
    for _ in 0..<Int(dx) {
        y += yStep
        x += 1
        
        line.addLine(to: CGPoint(x: x, y: y))
    }
    
    return line
}

struct ContentView: View {
    var body: some View {
        Canvas { context, size in
            let p1 = CGPoint(x: 10, y: 40), p2 = CGPoint(x: 300, y: 100)
            let p3 = CGPoint(x: 50, y: 400), p4 = CGPoint(x: 70, y: 10)
            let line1 = lineDDA(p1, p2), line2 = lineDDA(p3, p4)
            context.stroke(line1, with: .color(.red), lineWidth: 0.5)
            context.stroke(line2, with: .color(.white), lineWidth: 0.5)
        }
        .frame(width: 600, height: 600)
    }
}

#Preview {
    ContentView()
}
