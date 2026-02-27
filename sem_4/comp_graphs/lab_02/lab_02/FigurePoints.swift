//
//  FigurePoints.swift
//  lab_02
//
//  Created by Dmitriy Dudurev on 27.02.2026.
//

import Foundation
let x = 0.0, y = 0.0
let gitara = [
    [
        CGPoint(x: x, y: y),

        CGPoint(x: x - 40, y: y),
        CGPoint(x: x - 55, y: y - 25),
        CGPoint(x: x - 60, y: y - 50),
        CGPoint(x: x - 55, y: y - 75),
        CGPoint(x: x - 75 / 2, y: y - 110),
        CGPoint(x: x - 45, y: y - 130),
        CGPoint(x: x - 45, y: y - 150),

        CGPoint(x: x - 44, y: y - 152),
        CGPoint(x: x - 43, y: y - 154),
        CGPoint(x: x - 42, y: y - 156),
        CGPoint(x: x - 41, y: y - 158),
        CGPoint(x: x - 75 / 2, y: y - 160),

        CGPoint(x: x - 5 / 2,   y: y - 160),
        CGPoint(x: x, y: y - 160),
        CGPoint(x: x + 5 / 2,   y: y - 160),

        CGPoint(x: x + 75 / 2,  y: y - 160),
        CGPoint(x: x + 41,  y: y - 158),
        CGPoint(x: x + 42,  y: y - 156),
        CGPoint(x: x + 43,  y: y - 154),
        CGPoint(x: x + 44,  y: y - 152),
        CGPoint(x: x + 45,  y: y - 150),

        CGPoint(x: x + 45, y: y - 130),
        CGPoint(x: x + 75 / 2,  y: y - 110),
        CGPoint(x: x + 55, y: y - 75),
        CGPoint(x: x + 60, y: y - 50),
        CGPoint(x: x + 55, y: y - 25),
        CGPoint(x: x + 40,  y: y),

        CGPoint(x: x, y: y)
    ],
    [
        CGPoint(x: x - 20, y: y - 40),
        CGPoint(x: x + 20, y: y - 40),
        CGPoint(x: x + 20, y: y - 50),
        CGPoint(x: x - 20, y: y - 50),
        CGPoint(x: x - 20, y: y - 40)
    ],
    [
        CGPoint(x: x - 3, y: y - 50),
        CGPoint(x: x - 3, y: y - 280),
    ],
    [
        CGPoint(x: x, y: y - 50),
        CGPoint(x: x, y: y - 280),
    ],
    [
        CGPoint(x: x + 3, y: y - 50),
        CGPoint(x: x + 3, y: y - 280),
    ],
    [
        CGPoint(x: x - 10, y: y - 160),
        CGPoint(x: x - 10, y: y - 260),
        CGPoint(x: x - 15, y: y - 270),
        CGPoint(x: x - 10, y: y - 300),
        
        CGPoint(x: x + 10, y: y - 300),
        CGPoint(x: x + 15, y: y - 270),
        CGPoint(x: x + 10, y: y - 260),
        CGPoint(x: x + 10, y: y - 160),
        
    ],
    [
        CGPoint(x: x + 15.000000, y: y + -80.000000),
        CGPoint(x: x + 12.990381, y: y + -72.500000),
        CGPoint(x: x + 7.500000, y: y + -67.009619),
        CGPoint(x: x + 0.000000, y: y + -65.000000),
        CGPoint(x: x + -7.500000, y: y + -67.009619),
        CGPoint(x: x + -12.990381, y: y + -72.500000),
        CGPoint(x: x + -15.000000, y: y + -80.000000),
        CGPoint(x: x + -12.990381, y: y + -87.500000),
        CGPoint(x: x + -7.500000, y: y + -92.990381),
        CGPoint(x: x + -0.000000, y: y + -95.000000),
        CGPoint(x: x + 7.500000, y: y + -92.990381),
        CGPoint(x: x + 12.990381, y: y + -87.500000),
        CGPoint(x: x + 15.000000, y: y + -80.000000),
    ],
    [
        CGPoint(x: x + 20.000000, y: y + -80.000000),
        CGPoint(x: x + 17.320508, y: y + -70.000000),
        CGPoint(x: x + 10.000000, y: y + -62.679492),
        CGPoint(x: x + 0.000000, y: y + -60.000000),
        CGPoint(x: x + -10.000000, y: y + -62.679492),
        CGPoint(x: x + -17.320508, y: y + -70.000000),
        CGPoint(x: x + -20.000000, y: y + -80.000000),
        CGPoint(x: x + -17.320508, y: y + -90.000000),
        CGPoint(x: x + -10.000000, y: y + -97.320508),
        CGPoint(x: x + -0.000000, y: y + -100.000000),
        CGPoint(x: x + 10.000000, y: y + -97.320508),
        CGPoint(x: x + 17.320508, y: y + -90.000000),
        CGPoint(x: x + 20.000000, y: y + -80.000000),
    ],
    
    [
        CGPoint(x: x + 20.000000, y: y + -80.000000),
        CGPoint(x: x + 15.000000, y: y + -80.000000)
    ],
    [
        CGPoint(x: x + 17.320508, y: y + -70.000000),
        CGPoint(x: x + 12.990381, y: y + -72.500000)
    ],
    [
        CGPoint(x: x + 10.000000, y: y + -62.679492),
        CGPoint(x: x + 7.500000, y: y + -67.009619)
    ],
    [
        CGPoint(x: x + 0.000000, y: y + -60.000000),
        CGPoint(x: x + 0.000000, y: y + -65.000000)
    ],
    [
        CGPoint(x: x + -10.000000, y: y + -62.679492),
        CGPoint(x: x + -7.500000, y: y + -67.009619)
    ],
    [
        CGPoint(x: x + -17.320508, y: y + -70.000000),
        CGPoint(x: x + -12.990381, y: y + -72.500000)
    ],
    [
        CGPoint(x: x + -20.000000, y: y + -80.000000),
        CGPoint(x: x + -15.000000, y: y + -80.000000)
    ],
    [
        CGPoint(x: x + -17.320508, y: y + -90.000000),
        CGPoint(x: x + -12.990381, y: y + -87.500000)
    ],
    [
        CGPoint(x: x + -10.000000, y: y + -97.320508),
        CGPoint(x: x + -7.500000, y: y + -92.990381)
    ],
    [
        CGPoint(x: x + -0.000000, y: y + -100.000000),
        CGPoint(x: x + -0.000000, y: y + -95.000000)
    ],
    [
        CGPoint(x: x + 10.000000, y: y + -97.320508),
        CGPoint(x: x + 7.500000, y: y + -92.990381)
    ],
    [
        CGPoint(x: x + 17.320508, y: y + -90.000000),
        CGPoint(x: x + 12.990381, y: y + -87.500000)
    ],

]
