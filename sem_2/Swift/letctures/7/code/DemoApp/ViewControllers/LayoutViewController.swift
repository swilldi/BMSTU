//
//  LayoutViewController.swift
//  DemoApp
//
//  Created by Anton Danilov on 01.04.2025.
//

import UIKit

// Пример верстки кодом из Лекции 7

class LayoutViewController: UIViewController {

    private var titleLabel: UILabel?
    private var mainButton: UIButton?

    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .white
        
        setupButton()
        setupTitle()
        setupConstraints()
    }
}

// MARK: - Private Methods

extension LayoutViewController {

    private func setupButton() {
        let button = UIButton()
        button.addTarget(self, action: #selector(didTapButton), for: .touchUpInside)
        button.backgroundColor = .systemBlue
        button.setTitle("Change title color", for: .normal)
        view.addSubview(button)

        mainButton = button
    }

    @objc private func didTapButton() {
        titleLabel?.textColor = .systemBlue
    }

    private func setupTitle() {
        let title = UILabel()
        title.font = .systemFont(ofSize: 30)
        title.textColor = .black
        title.textAlignment = .center
        title.numberOfLines = 1
        title.text = "Text"
        view.addSubview(title)

        titleLabel = title
    }

    private func setupConstraints() {
        guard let titleLabel, let mainButton else { return }

        titleLabel.translatesAutoresizingMaskIntoConstraints = false
        mainButton.translatesAutoresizingMaskIntoConstraints = false

        NSLayoutConstraint.activate([
            mainButton.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            mainButton.centerYAnchor.constraint(equalTo: view.centerYAnchor),
            mainButton.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
            titleLabel.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            titleLabel.bottomAnchor.constraint(equalTo: mainButton.topAnchor, constant: -20),
            titleLabel.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16)
        ])
    }
}
