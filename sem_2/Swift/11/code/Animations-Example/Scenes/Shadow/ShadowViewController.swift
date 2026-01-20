//
//  ShadowViewController.swift
//  Animations-Example
//
//  Created by Dunaev Sergey V. on 22.04.2025.
//

import UIKit

final class ShadowViewController: UIViewController {
    private lazy var leftView: UIView = {
        let view = UIView()
        view.backgroundColor = .systemBlue
        view.translatesAutoresizingMaskIntoConstraints = false

        view.layer.cornerRadius = 16
        view.layer.shadowOpacity = 0.3
        view.layer.shadowRadius = 10
        view.layer.shadowOffset = CGSize(width: 0, height: 4)

        return view
    }()

    private lazy var rightView: ShadowView = {
        let view = ShadowView()
        view.backgroundColor = .systemBlue
        view.translatesAutoresizingMaskIntoConstraints = false

        view.cornerRadius = 16
        view.shadowOpacity = 0.3
        view.shadowRadius = 10
        view.shadowOffset = CGSize(width: 0, height: 4)

        return view
    }()

    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .white

        setupView()
    }

    private func setupView() {
        view.addSubview(leftView)
        view.addSubview(rightView)

        NSLayoutConstraint.activate([
            leftView.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 40),
            leftView.centerXAnchor.constraint(equalTo: view.centerXAnchor, constant: -100),
            leftView.widthAnchor.constraint(equalToConstant: 150),
            leftView.heightAnchor.constraint(equalToConstant: 100),

            rightView.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 40),
            rightView.centerXAnchor.constraint(equalTo: view.centerXAnchor, constant: 100),
            rightView.widthAnchor.constraint(equalToConstant: 150),
            rightView.heightAnchor.constraint(equalToConstant: 100),
        ])
    }
}
