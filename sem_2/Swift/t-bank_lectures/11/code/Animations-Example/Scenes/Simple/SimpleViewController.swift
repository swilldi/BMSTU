//
//  SimpleViewController.swift
//  Animations-Example
//
//  Created by Dunaev Sergey V. on 18.04.2025.
//

import UIKit

final class SimpleViewController: UIViewController {
    private let simpleAnimation: SimpleAnimation

    init(simpleAnimation: SimpleAnimation) {
        self.simpleAnimation = simpleAnimation
        super.init(nibName: nil, bundle: nil)
    }

    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .white

        switch simpleAnimation {
        case .moving:
            performMovingAnimation()
        case .transparency:
            performTransparencyAnimation()
        }
    }

    private func performMovingAnimation() {
        let newView = UIView(frame: CGRect(x: 20, y: 120, width: 100, height: 100))
        newView.backgroundColor = .systemBlue
        
        view.addSubview(newView)
        
        UIView.animate(withDuration: 2) {
            newView.center.x += 200
        }
    }

    private func performTransparencyAnimation() {
        let backgroundView = UIView(frame: CGRect(x: 20, y: 120, width: 100, height: 100))
        backgroundView.backgroundColor = .gray

        view.addSubview(backgroundView)


        let newView = UIView(frame: CGRect(x: 80, y: 160, width: 100, height: 100))
        newView.backgroundColor = .systemCyan

        view.addSubview(newView)

        UIView.animate(withDuration: 2) {
            newView.alpha = 0.5
            newView.backgroundColor = .systemRed
        }
    }
}
