//
//  SceneAssembler.swift
//  dz_08
//
//  Created by Dmitriy Dudyrev on 16.04.2025.
//
import UIKit

final class MainSceneAssembler {
    func makeScene() -> UIViewController {
        let networkClient = NetworkClient()
        let presenter = MainPresenter(networkClient: networkClient)
        let view = MainViewController (presenter: presenter)
        presenter.view = view
        
        return view
    }
}
