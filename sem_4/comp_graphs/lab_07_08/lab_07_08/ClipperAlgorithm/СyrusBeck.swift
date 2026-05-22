//
//  СyrusBeck.swift
//  lab_07
//
//  Created by Dmitriy Dudurev on 15.05.2026.
//

import Foundation
func cyrusBeck(_ segments: [Segment], _ polygon: [CGPoint]) -> [Segment] {
    guard polygon.count >= 3 else { return [] }

    var clippedSegments = [Segment]()

    let n = polygon.count

    // Определяем направление обхода вершин через знак площади
    var signedArea: CGFloat = 0
    for i in 0..<n {
        let a = polygon[i]
        let b = polygon[(i + 1) % n]
        signedArea += (b.x - a.x) * (b.y + a.y)
    }
    // sign приводит нормали к одному виду независимо от порядка вершин
    let sign: CGFloat = signedArea <= 0 ? 1 : -1

    // Для каждого ребра запоминаем стартовую точку и нормаль
    var normals = [CGPoint]()
    var points = [CGPoint]()

    for i in 0..<n {
        let a = polygon[i]
        let b = polygon[(i + 1) % n]
        let edge = CGPoint(x: b.x - a.x, y: b.y - a.y)
        normals.append(CGPoint(x: sign * edge.y, y: -sign * edge.x))
        points.append(a)
    }

    for segment in segments {
        let p1 = segment.p1
        let p2 = segment.p2
        // Вектор направления отрезка
        let d = CGPoint(x: p2.x - p1.x, y: p2.y - p1.y)

        // Параметры входа и выхода отрезка в многоугольник (от 0 до 1)
        var tEnter: CGFloat = 0
        var tLeave: CGFloat = 1
        var visible = true

        // Проверяем отрезок на каждом ребре
        for i in 0..<n {
            let N = normals[i]
            let A = points[i]

            // Вектор от вершины ребра до начала отрезка
            let W = CGPoint(x: p1.x - A.x, y: p1.y - A.y)

            let nd = N.x * d.x + N.y * d.y   // N · D
            let nw = N.x * W.x + N.y * W.y   // N · W

            if nd == 0 {
                // Отрезок параллелен ребру: если лежит снаружи — отбрасываем
                if nw < 0 {
                    visible = false
                    break
                }
            } else {
                // Параметр пересечения с прямой ребра
                let t = -nw / nd
                if nd < 0 {
                    // Отрезок входит — двигаем tEnter вправо
                    tEnter = max(tEnter, t)
                } else {
                    // Отрезок выходит — двигаем tLeave влево
                    tLeave = min(tLeave, t)
                }
            }
        }

        // Если вход < выхода — внутри есть видимая часть
        if visible && tEnter <= tLeave {
            let newP1 = CGPoint(x: p1.x + tEnter * d.x, y: p1.y + tEnter * d.y)
            let newP2 = CGPoint(x: p1.x + tLeave * d.x, y: p1.y + tLeave * d.y)
            clippedSegments.append(Segment(p1: newP1, p2: newP2))
        }
    }

    return clippedSegments
}
