//
//  SceneAssembler.swift
//  dz_09
//
//  Created by Dmitriy Dudyrev on 19.04.2025.
//

import Foundation
import UIKit

final class SceneAssembler {
    func makeScene() -> UIViewController {
        let networkClient = NetworkClient()
        let viewController = ViewController()
        let presenter = Presenter(networkClient: networkClient, view: viewController)
        viewController.presenter = presenter

        return viewController
    }
}
