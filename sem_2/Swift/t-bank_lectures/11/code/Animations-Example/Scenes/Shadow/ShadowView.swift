//
//  ShadowView.swift
//  Animations-Example
//
//  Created by Dunaev Sergey V. on 22.04.2025.
//

import UIKit

final class ShadowView: UIView {
    var cornerRadius: CGFloat = 0 {
        didSet {
            layer.cornerRadius = cornerRadius
            updateShadowPath()
        }
    }

    var shadowOpacity: Float = 0 {
        didSet { layer.shadowOpacity = shadowOpacity }
    }

    var shadowRadius: CGFloat = 0 {
        didSet { layer.shadowRadius = shadowRadius }
    }

    var shadowOffset: CGSize = .zero {
        didSet { layer.shadowOffset = shadowOffset }
    }

    override func layoutSubviews() {
        super.layoutSubviews()
        updateShadowPath()
    }

    private func updateShadowPath() {
        let path = UIBezierPath(roundedRect: bounds, cornerRadius: cornerRadius)
        layer.shadowPath = path.cgPath
    }
}
