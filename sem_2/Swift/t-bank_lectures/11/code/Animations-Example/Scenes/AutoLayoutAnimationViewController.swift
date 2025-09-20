//
//  AutoLayoutAnimationViewController.swift
//  Animations-Example
//
//  Created by Dunaev Sergey V. on 21.04.2025.
//

import UIKit

final class AutoLayoutAnimationViewController: UIViewController {
    private var widthConstraint: NSLayoutConstraint?
    private var isExpanded = false

    private lazy var animatedView: UIView = {
        let view = UIView()
        view.backgroundColor = .systemBlue
        view.translatesAutoresizingMaskIntoConstraints = false

        return view
    }()

    private lazy var button: UIButton = {
        let button = UIButton(
            configuration: .filled(),
            primaryAction: UIAction(title: "Изменить размер") { [unowned self] _ in
                self.toggleSize()
            }
        )
        button.translatesAutoresizingMaskIntoConstraints = false

        return button
    }()

    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .white
        view.addSubview(animatedView)
        view.addSubview(button)

        let widthConstraint = animatedView.widthAnchor.constraint(equalToConstant: 100)

        NSLayoutConstraint.activate([
            animatedView.heightAnchor.constraint(equalToConstant: 80),
            widthConstraint,
            animatedView.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            animatedView.centerYAnchor.constraint(equalTo: view.centerYAnchor),

            button.topAnchor.constraint(equalTo: animatedView.bottomAnchor, constant: 20),
            button.centerXAnchor.constraint(equalTo: view.centerXAnchor)
        ])

        self.widthConstraint = widthConstraint
    }

    private func toggleSize() {
        isExpanded.toggle()
        widthConstraint?.constant = isExpanded ? 250 : 100

        UIView.animate(withDuration: 0.4, delay: 0, options: [.curveEaseInOut]) {
            self.view.layoutIfNeeded()
        }
    }
}
