//
//  SceneDelegate.swift
//  Animations-Example
//
//  Created by Dunaev Sergey V. on 06.04.2025.
//

import UIKit

final class SceneDelegate: UIResponder, UIWindowSceneDelegate {
    var window: UIWindow?

    func scene(
        _ scene: UIScene,
        willConnectTo session: UISceneSession,
        options connectionOptions: UIScene.ConnectionOptions
    ) {
        guard let windowScene = scene as? UIWindowScene else { return }

        let window = UIWindow(windowScene: windowScene)
        let viewController = MainSceneAssembler().makeScene()
        window.rootViewController = UINavigationController(rootViewController: viewController)
        window.makeKeyAndVisible()

        self.window = window
    }
}
