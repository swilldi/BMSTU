//
//  RateView.swift
//  Animations-Example
//
//  Created by Dunaev Sergey V. on 21.04.2025.
//

import UIKit

final class RateView: UIView {
    private(set) var currentRate: Int = 0

    private let maxRate: Int = 5

    private lazy var bgLayer: CAShapeLayer = {
        let layer = CAShapeLayer()
        layer.lineWidth = Constant.lineWidth
        layer.strokeColor = UIColor.lightGray.cgColor
        layer.strokeEnd = 1
        layer.lineCap = .round

        return layer
    }()

    private lazy var fgLayer: CAShapeLayer = {
        let layer = CAShapeLayer()
        layer.lineWidth = Constant.lineWidth
        layer.strokeColor = UIColor.black.cgColor
        layer.strokeEnd = 0
        layer.lineCap = .round

        return layer
    }()

    private lazy var gradientLayer: CAGradientLayer = {
        let layer = CAGradientLayer()
        layer.colors = [UIColor.red.cgColor, UIColor.yellow.cgColor, UIColor.green.cgColor]
        layer.startPoint = .init(x: 0, y: 0.5)
        layer.endPoint = .init(x: 1, y: 0.5)
        layer.mask = fgLayer

        return layer
    }()

    override init(frame: CGRect) {
        super.init(frame: frame)
        setupView()
    }

    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func layoutSubviews() {
        super.layoutSubviews()
        updateLayers()
    }

    func setRate(_ rate: Int) {
        let newRate = max(0, min(rate, maxRate))

        guard currentRate != newRate else { return }

        currentRate = newRate
        configure()
    }

    // MARK: - Private methods

    private func setupView() {
        layer.addSublayer(bgLayer)
        layer.addSublayer(gradientLayer)

        let label1 = makeLabel(text: "🤮")
        let label2 = makeLabel(text: "😒")
        let label3 = makeLabel(text: "😐")
        let label4 = makeLabel(text: "😃")
        let label5 = makeLabel(text: "😍")
        let label6 = makeLabel(text: "🤩")

        let stackView = UIStackView(arrangedSubviews: [label1, label2, label3, label4, label5, label6])
        stackView.axis = .horizontal
        stackView.distribution = .equalSpacing
        stackView.translatesAutoresizingMaskIntoConstraints = false

        addSubview(stackView)

        NSLayoutConstraint.activate([
            stackView.topAnchor.constraint(equalTo: topAnchor),
            stackView.leadingAnchor.constraint(equalTo: leadingAnchor),
            stackView.trailingAnchor.constraint(equalTo: trailingAnchor),

            heightAnchor.constraint(equalToConstant: 60)
        ])

        configure()
    }

    private func makeLabel(text: String) -> UILabel {
        let label = UILabel()
        label.text = text
        label.translatesAutoresizingMaskIntoConstraints = false

        return label
    }

    private func updateLayers() {
        gradientLayer.frame = bounds

        bgLayer.frame = bounds
        bgLayer.path = makeProgressPath().cgPath

        fgLayer.frame = bounds
        fgLayer.path = makeProgressPath().cgPath
    }

    private func makeProgressPath() -> UIBezierPath {
        let path = UIBezierPath()
        path.move(to: .init(x: Constant.lineWidth / 2, y: 50))
        path.addLine(to: .init(x: bounds.width - Constant.lineWidth / 2, y: 50))

        return path
    }

    private func configure() {
        let toValue = CGFloat(currentRate) / CGFloat(maxRate)
        fgLayer.strokeEnd = toValue
    }
}

extension RateView {
    private enum Constant {
        static let lineWidth: CGFloat = 20
        static let animationKey = "strokeAnimation"
        static let totalDuration: TimeInterval = 5
    }
}
