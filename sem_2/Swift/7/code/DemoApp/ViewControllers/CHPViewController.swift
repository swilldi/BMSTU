//
//  CHPViewController.swift
//  DemoApp
//
//  Created by Anton Danilov on 21.04.2025.
//

import UIKit

// Пример решения типичной ситуации с двумя лейблами в стеке через CHP и CRP

class CHPViewController: UIViewController {

    private let stackView: UIStackView = {
        let stack = UIStackView()
        stack.axis = .horizontal
        stack.spacing = 8
        stack.alignment = .center
        stack.distribution = .fill
        stack.translatesAutoresizingMaskIntoConstraints = false
        return stack
    }()

    private let shortLabel: UILabel = {
        let label = UILabel()
        label.text = "Короткий текст"
        label.font = UIFont.systemFont(ofSize: 16)
        label.backgroundColor = .systemYellow
        label.setContentHuggingPriority(.defaultLow, for: .horizontal)
        label.translatesAutoresizingMaskIntoConstraints = false
        return label
    }()

    private let longLabel: UILabel = {
        let label = UILabel()
        label.text = "Очень длинный текст, который должен обрезаться при недостатке места в стеке"
        label.font = UIFont.systemFont(ofSize: 16)
        label.numberOfLines = 1
        label.lineBreakMode = .byTruncatingTail
        label.backgroundColor = .systemGreen
        label.setContentHuggingPriority(.defaultHigh, for: .horizontal)
        label.translatesAutoresizingMaskIntoConstraints = false
        return label
    }()

    override func viewDidLoad() {
        super.viewDidLoad()
        setupUI()
    }

    private func setupUI() {
        view.backgroundColor = .white

        stackView.addArrangedSubview(longLabel)
        stackView.addArrangedSubview(shortLabel)

        view.addSubview(stackView)

        NSLayoutConstraint.activate([
            stackView.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 20),
            stackView.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 20),
            stackView.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -20)
        ])

        shortLabel.setContentCompressionResistancePriority(.defaultHigh, for: .horizontal)
        longLabel.setContentCompressionResistancePriority(.defaultLow, for: .horizontal)
    }
}

