//
//  SutherlandHodgman.swift
//  lab_07_08_09
//
//  Created by Dmitriy Dudurev on 22.05.2026.
//

import Foundation

func subPoint(_ a: CGPoint, _ b: CGPoint) -> CGPoint {
    return CGPoint(x: b.x - a.x, y: b.y - a.y)
}
func crossVectors(_ a: CGPoint, _ b: CGPoint) -> CGFloat {
    return a.x * b.y - a.y * b.x
}

private func lineIntersection(_ a: CGPoint, _ b: CGPoint, _ c: CGPoint, _ d: CGPoint) -> CGPoint? {
    let r = subPoint(a, b)
    let s = subPoint(c, d)
    let denom = r.x * s.y - r.y * s.x
    
    if abs(denom) < 1e-9 {
        return nil
    }
    
    let ca = subPoint(a, c)
    let t = crossVectors(ca, s) / denom

    return CGPoint(x: a.x + t * r.x, y: a.y + t * r.y)
}

private func signedArea(_ poly: [CGPoint]) -> CGFloat {
    var sum: CGFloat = 0
    for i in 0..<poly.count {
        let a = poly[i]
        let b = poly[(i + 1) % poly.count]
        sum += a.x * b.y - b.x * a.y
    }
    return sum / 2
}


func sutherlandHodgman(_ segmentsPoints: [CGPoint], _ polygon: [CGPoint]) -> [CGPoint] {
    var output = segmentsPoints
    if signedArea(output) < 0 {
        output.reverse()
    }

    // Нормализуем направление обхода отсекателя
    var clip = polygon
    if signedArea(clip) < 0 {
        clip.reverse()
    }

    for i in 0..<clip.count {
        let clipP1 = clip[i]
        let clipP2 = clip[(i + 1) % clip.count]
        let d = subPoint(clipP2, clipP1)
        
        let inside: (CGPoint) -> Bool = { p in
            crossVectors(d, subPoint(clipP1, p)) <= 0
        }
        let input = output
        output = []
        
        for j in 0..<input.count {
            let s = input[(j + input.count - 1) % input.count]
            let e = input[j]

            let sInline = inside(s)
            let eInline = inside(e)

            if eInline && sInline {
                output.append(e)
            } else if eInline {
                if let x = lineIntersection(s, e, clipP1, clipP2) {
                    output.append(x)
                }
                output.append(e)
            } else if sInline {
                if let x = lineIntersection(s, e, clipP1, clipP2) {
                    output.append(x)
                }
            }
        }

        
    }
    
    return output
}
