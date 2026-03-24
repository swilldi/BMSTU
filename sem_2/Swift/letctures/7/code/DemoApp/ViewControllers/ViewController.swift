//
//  ViewController.swift
//  DemoApp
//
//  Created by Anton Danilov on 25.03.2025.
//

import UIKit

// Пример работы с аутлетами и экшенами из Лекции 7

class ViewController: UIViewController {

    @IBOutlet weak var mainButton: UIButton!
    @IBOutlet weak var titleLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        titleLabel.text = "New text"
        mainButton.addTarget(self, action: #selector(didTapButton(_:)), for: .touchUpInside)
    }

    @IBAction func didTapButton(_ sender: Any) {
        titleLabel.textColor = .systemBlue
    }
}
