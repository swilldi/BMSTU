//
//  IntrinsicContentViewController.swift
//  DemoApp
//
//  Created by Anton Danilov on 21.04.2025.
//

import UIKit

// Как меняется intrinsicContentSize

final class IntrinsicContentViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        let label = UILabel()
        label.text = "Hello"
        print(label.intrinsicContentSize)

        let imageView = UIImageView(image: .cat)
        print(imageView.intrinsicContentSize) 
    }
}
