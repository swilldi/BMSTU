//
//  MainPresenterInput.swift
//  Animations-Example
//
//  Created by Dunaev Sergey V. on 06.04.2025.
//

import Foundation

protocol MainPresenterInput: AnyObject {
    var animationCellCount: Int { get }

    func viewDidLoad()
    func animationCell(at index: Int) -> AnimationCellModel
    func didSelectRowAt(indexPath: IndexPath)
}
