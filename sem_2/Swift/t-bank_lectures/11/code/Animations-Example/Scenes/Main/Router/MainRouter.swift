//
//  MainRouter.swift
//  Animations-Example
//
//  Created by Dunaev Sergey V. on 18.04.2025.
//

import UIKit

final class MainRouter {
    weak var transitionHandler: UIViewController?
}

// MARK: - MainRouterInput

extension MainRouter: MainRouterInput {
    func showMovingAnimation() {
        let viewController = SimpleViewController(simpleAnimation: .moving)
        transitionHandler?.navigationController?.pushViewController(viewController, animated: true)
    }

    func showTransperencyAnimation() {
        let viewController = SimpleViewController(simpleAnimation: .transparency)
        transitionHandler?.navigationController?.pushViewController(viewController, animated: true)
    }

    func showAutoLayoutAnimation() {
        let viewController = AutoLayoutAnimationViewController()
        transitionHandler?.navigationController?.pushViewController(viewController, animated: true)
    }

    func showComboAnimation() {
        let viewController = ComboAnimationViewController()
        transitionHandler?.navigationController?.pushViewController(viewController, animated: true)
    }

    func showCoreAnimation() {
        let viewController = CoreAnimationViewController()
        transitionHandler?.navigationController?.pushViewController(viewController, animated: true)
    }

    func showShadowView() {
        let viewController = ShadowViewController()
        transitionHandler?.navigationController?.pushViewController(viewController, animated: true)
    }
}
