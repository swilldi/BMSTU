//
//  FrameBoundsViewController.swift
//  DemoApp
//
//  Created by Anton Danilov on 21.04.2025.
//

import UIKit

// Как меняется при различных преобразованиях frame и bounds

final class FrameBoundsViewController: UIViewController {
    
    let customView: UIImageView = {
        let view = UIImageView(frame: CGRect(x: 100, y: 200, width: 200, height: 200))
        view.backgroundColor = .systemBlue
        view.image = UIImage(named: "catImage")

        return view
    }()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupView()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
//                animateView()
        rotateView()
//        changeBounds()
//        changeBoundsOrigin()
    }
    
    private func setupView() {
        view.addSubview(customView)
        view.backgroundColor = .white
        
        print(customView.frame)
        print(customView.bounds)
    }
    
    private func animateView() {
        UIView.animate(withDuration: 5) {
            self.customView.frame = CGRect(x: 50, y: 100, width: 300, height: 150)
        }
        
        print(customView.frame)
        print(customView.bounds)
    }
    
    private func rotateView() {
        UIView.animate(withDuration: 5) {
            self.customView.transform = CGAffineTransform(rotationAngle: .pi / 4)
        }

        addBoundingView()
        print(customView.frame)
        print(customView.bounds)
    }
    
    private func addBoundingView() {
        let boundingView = UIView(frame: customView.frame)
        view.addSubview(boundingView)
        boundingView.backgroundColor = .clear
        boundingView.layer.borderColor = UIColor.red.cgColor
        boundingView.layer.borderWidth = 1
    }

    private func changeBounds() {
        UIView.animate(withDuration: 5) {
            self.customView.bounds = CGRect(x: 100, y: 0, width: 50, height: 50)
        }

        addBoundingView()
        print(customView.frame)
        print(customView.bounds)
    }

    private func changeBoundsOrigin() {
        UIView.animate(withDuration: 5) {
            self.customView.bounds.origin = CGPoint(x: 100, y: 100)
        }

        addBoundingView()
        print(customView.frame)
        print(customView.bounds)
    }
}
