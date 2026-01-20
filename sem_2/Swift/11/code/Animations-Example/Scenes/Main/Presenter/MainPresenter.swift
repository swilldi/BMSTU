//
//  MainPresenter.swift.swift
//  Animations-Example
//
//  Created by Dunaev Sergey V. on 06.04.2025.
//

import Foundation

final class MainPresenter {
    weak var view: MainViewInput?

    private let router: MainRouterInput

    private lazy var models: [AnimationCellModel] = [
        .init(title: "UIView.animate - перемещение") { [unowned self] in
            self.router.showMovingAnimation()
        },
        .init(title: "UIView.animate - прозрачность") { [unowned self] in
            self.router.showTransperencyAnimation()
        },
        .init(title: "Анимация AutoLayout") { [unowned self] in
            self.router.showAutoLayoutAnimation()
        },
        .init(title: "Комбинированная анимация") { [unowned self] in
            self.router.showComboAnimation()
        },
        .init(title: "Core Animation") { [unowned self] in
            self.router.showCoreAnimation()
        },
        .init(title: "Отрисовка тени") { [unowned self] in
            self.router.showShadowView()
        },
    ]

    init(router: MainRouterInput) {
        self.router = router
    }

    private func loadAnimations() {
        
    }
}

// MARK: - MainPresenterInput

extension MainPresenter: MainPresenterInput {
    var animationCellCount: Int {
        models.count
    }

    func viewDidLoad() {
        loadAnimations()
    }

    func animationCell(at index: Int) -> AnimationCellModel {
        models[index]
    }

    func didSelectRowAt(indexPath: IndexPath) {
        models[indexPath.row].onTap()
    }
}
