//
//  ComboAnimationViewController.swift
//  Animations-Example
//
//  Created by Dunaev Sergey V. on 21.04.2025.
//

import UIKit

final class ComboAnimationViewController: UIViewController {
    private var textField1Leading: NSLayoutConstraint?
    private var textField2Leading: NSLayoutConstraint?

    private lazy var textField1 = makeTextField(placeholder: "Имя")
    private lazy var textField2 = makeTextField(placeholder: "Фамилия")
    private lazy var button: UIButton = {
        let button = UIButton(configuration: .filled(), primaryAction: UIAction(title: "Продолжить") { _ in })
        button.translatesAutoresizingMaskIntoConstraints = false

        return button
    }()

    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .white
        view.clipsToBounds = true

        view.addSubview(textField1)
        view.addSubview(textField2)
        view.addSubview(button)

        let tf1Leading = textField1.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: -300)
        let tf2Leading = textField2.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: -300)
        self.textField1Leading = tf1Leading
        self.textField2Leading = tf2Leading

        NSLayoutConstraint.activate([
            tf1Leading,
            textField1.topAnchor.constraint(equalTo: view.centerYAnchor, constant: -80),
            textField1.widthAnchor.constraint(equalToConstant: 250),
            textField1.heightAnchor.constraint(equalToConstant: 40),

            tf2Leading,
            textField2.topAnchor.constraint(equalTo: textField1.bottomAnchor, constant: 16),
            textField2.widthAnchor.constraint(equalToConstant: 250),
            textField2.heightAnchor.constraint(equalToConstant: 40),

            button.topAnchor.constraint(equalTo: textField2.bottomAnchor, constant: 32),
            button.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            button.widthAnchor.constraint(equalToConstant: 150),
            button.heightAnchor.constraint(equalToConstant: 50)
        ])

        // Начальное состояние трансформации
        button.transform = CGAffineTransform(translationX: 0, y: 400).scaledBy(x: 0.1, y: 0.1).rotated(by: -.pi)
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        animateTextFields()
    }

    private func makeTextField(placeholder: String) -> UITextField {
        let textField = UITextField()
        textField.backgroundColor = .systemGray6
        textField.placeholder = placeholder
        textField.borderStyle = .roundedRect
        textField.translatesAutoresizingMaskIntoConstraints = false

        return textField
    }

    private func animateTextFields() {
        // Шаг 1 - анимируем первое текстовое поле
        textField1Leading?.constant = (view.frame.width - 250) / 2
        UIView.animate(
            withDuration: 0.5,
            delay: 0,
            usingSpringWithDamping: 0.6,
            initialSpringVelocity: 0,
            options: .curveEaseOut
        ) {
            self.view.layoutIfNeeded()
        } completion: { _ in
            // Шаг 2 - анимируем второе текстовое поле с задержкой
            self.textField2Leading?.constant = (self.view.frame.width - 250) / 2
            UIView.animate(
                withDuration: 0.5,
                delay: 0,
                usingSpringWithDamping: 0.6,
                initialSpringVelocity: 0,
                options: .curveEaseOut
            ) {
                self.view.layoutIfNeeded()
            }
        }

        UIView.animate(
            withDuration: 1.5,
            delay: 0.6,
            usingSpringWithDamping: 0.6,
            initialSpringVelocity: 0.8,
            options: []
        ) {
            self.button.transform = .identity
        }
    }
}
