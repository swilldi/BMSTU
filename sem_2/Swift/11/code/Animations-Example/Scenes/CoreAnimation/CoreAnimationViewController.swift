//
//  CoreAnimationViewController.swift
//  Animations-Example
//
//  Created by Dunaev Sergey V. on 21.04.2025.
//

import UIKit

final class CoreAnimationViewController: UIViewController {
    private lazy var rateLabel: UILabel = {
        let label = UILabel()
        label.text = "0"
        label.textColor = .systemIndigo
        label.font = .systemFont(ofSize: 72, weight: .bold)
        label.translatesAutoresizingMaskIntoConstraints = false

        return label
    }()

    private lazy var rateView: RateView = {
        let view = RateView()
        view.translatesAutoresizingMaskIntoConstraints = false

        return view
    }()

    private lazy var minusButton: UIButton = {
        let button = UIButton(
            configuration: .borderedTinted(),
            primaryAction: UIAction(title: "➖") { [unowned self] _ in self.didTapMinusButton() }
        )
        button.translatesAutoresizingMaskIntoConstraints = false

        return button
    }()

    private lazy var plusButton: UIButton = {
        let button = UIButton(
            configuration: .borderedTinted(),
            primaryAction: UIAction(title: "➕") { [unowned self] _ in self.didTapPlusButton() }
        )
        button.translatesAutoresizingMaskIntoConstraints = false

        return button
    }()

    override func viewDidLoad() {
        super.viewDidLoad()
        setupView()
    }

    private func setupView() {
        view.backgroundColor = .white

        view.addSubview(rateLabel)
        view.addSubview(rateView)
        view.addSubview(plusButton)
        view.addSubview(minusButton)

        NSLayoutConstraint.activate([
            rateView.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            rateView.centerYAnchor.constraint(equalTo: view.centerYAnchor),
            rateView.widthAnchor.constraint(equalToConstant: 320),

            rateLabel.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            rateLabel.bottomAnchor.constraint(equalTo: rateView.topAnchor, constant: -24),

            minusButton.topAnchor.constraint(equalTo: rateView.bottomAnchor, constant: 32),
            minusButton.centerXAnchor.constraint(equalTo: view.centerXAnchor, constant: -40),
            minusButton.widthAnchor.constraint(equalToConstant: 48),
            minusButton.heightAnchor.constraint(equalToConstant: 48),

            plusButton.topAnchor.constraint(equalTo: rateView.bottomAnchor, constant: 32),
            plusButton.centerXAnchor.constraint(equalTo: view.centerXAnchor, constant: 40),
            plusButton.widthAnchor.constraint(equalToConstant: 48),
            plusButton.heightAnchor.constraint(equalToConstant: 48),
        ])
    }

    private func didTapPlusButton() {
        rateView.setRate(rateView.currentRate + 1)
        rateLabel.text = "\(rateView.currentRate)"
    }

    private func didTapMinusButton() {
        rateView.setRate(rateView.currentRate - 1)
        rateLabel.text = "\(rateView.currentRate)"
    }
}
