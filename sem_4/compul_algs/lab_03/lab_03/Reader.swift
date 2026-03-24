//
//  Reader.swift
//  lab_03
//
//  Created by Dmitriy Dudurev on 23.03.2026.
//

import Foundation
func readPoints2D(from url: URL) -> [Point] {
    let accessed = url.startAccessingSecurityScopedResource()
    defer { if accessed { url.stopAccessingSecurityScopedResource() } }
    
    guard let content = try? String(contentsOf: url, encoding: .utf8) else { return [] }
    
    return content
        .components(separatedBy: .newlines)
        .compactMap { line -> Point? in
            let parts = line.trimmingCharacters(in: .whitespaces)
                            .components(separatedBy: .whitespaces)
                            .filter { !$0.isEmpty }
            guard parts.count >= 2,
                  let x = Double(parts[0]),
                  let y = Double(parts[1]) else { return nil }
            let p = parts.count >= 3 ? Double(parts[2]) ?? 1.0 : 1.0
            return Point(x: x, y: y, p: p)
        }
}

func readPoints3D(from url: URL) -> [Point3D] {
    let accessed = url.startAccessingSecurityScopedResource()
    defer { if accessed { url.stopAccessingSecurityScopedResource() } }
    
    guard let content = try? String(contentsOf: url, encoding: .utf8) else { return [] }
    
    return content
        .components(separatedBy: .newlines)
        .compactMap { line -> Point3D? in
            let parts = line.trimmingCharacters(in: .whitespaces)
                            .components(separatedBy: .whitespaces)
                            .filter { !$0.isEmpty }
            guard parts.count >= 3,
                  let x = Double(parts[0]),
                  let y = Double(parts[1]),
                  let z = Double(parts[2]) else { return nil }
            let p = parts.count >= 4 ? Double(parts[3]) ?? 1.0 : 1.0
            return Point3D(x: x, y: y, z: z, p: p)
        }
}
