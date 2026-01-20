//
//  MainSceneAssembler.swift
//  Animations-Example
//
//  Created by Dunaev Sergey V. on 06.04.2025.
//

import UIKit

final class MainSceneAssembler {
    func makeScene() -> UIViewController {
        let router = MainRouter()
        let presenter = MainPresenter(router: router)
        let view = MainViewController(presenter: presenter)
        presenter.view = view
        router.transitionHandler = view

        return view
    }
}
