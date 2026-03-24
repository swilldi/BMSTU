//
//  ViewController.swift
//  dz_07
//
//  Created by Dmitriy Dudyrev on 04.04.2025.
//

import UIKit

class ViewController: UIViewController {
    private var itemImage: UIImageView?
    private var companyLabel: UILabel?
    private var titleLabel: UILabel?
    private var priseLabel: UILabel?
    private var nextItemButton: UIButton?
    
    private var items: [Item] = [
        Item(.raven),
        Item(.andromeda),
        Item(.f8c),
        Item(.galaxy),
        Item(.carrack)
    ]
    private var selectedItem: Item?
    private var itemIndex = 0
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .black
        
        selectedItem = items[itemIndex]
        setupUI()
    }
    
    private func setupUI() {
        setupImage()
        setupButton()
        setupCompany()
        setupTitile()
        setupPrise()
        setupConstrains()
    }
    
    // MARK: Создание изображения
    private func setupImage() {
        let image = UIImage(named: selectedItem?.title ?? "Image not found")
        
        let imageView = UIImageView()
        imageView.contentMode = .scaleAspectFit
        imageView.image = image
        
        view.addSubview(imageView)
        
        itemImage = imageView
    }
    
    // MARK: Создание названия компании
    private func setupCompany() {
        let factory = UILabel()
        factory.font = .boldSystemFont(ofSize: 18)
        factory.textColor = .gray
        factory.textAlignment = .center
        factory.numberOfLines = 1
        factory.text = selectedItem?.company.uppercased() ?? "Company not found "
        view.addSubview(factory)
        
        companyLabel = factory
    }
    
    // MARK: Создание названия предмета
    private func setupTitile() {
        let title = UILabel()
        title.font = .boldSystemFont(ofSize: 20)
        title.textColor = .white
        title.textAlignment = .center
        title.numberOfLines = 1
        title.text = selectedItem?.title.capitalized ?? "Title not found"
        view.addSubview(title)
        
        titleLabel = title
    }
    
    // MARK: Создание цены
    private func setupPrise() {
        let prise = UILabel()
        prise.font = .boldSystemFont(ofSize: 23)
        prise.textColor = .white
        prise.textAlignment = .center
        prise.numberOfLines = 1
        prise.text = selectedItem?.formatPrise ?? "Prise not found"
        view.addSubview(prise)
        
        priseLabel = prise
    }
    
    // MARK: Создание кнопки перехода в следующему товару
    private func setupButton() {
        let button = UIButton()
        button.addTarget(self, action: #selector(didTapButton), for: .touchUpInside)
        button.backgroundColor = .white
        
        button.setTitle("Показать слудующий товар", for: .normal)
        button.setTitleColor(.black, for: .normal)
        
        button.layer.cornerRadius = 12
        
        
        view.addSubview(button)
        
        nextItemButton = button
    }
    
    // MARK: Дейстия при нажатии кнопки
    @objc private func didTapButton() {
        nextIndex()
        selectedItem = items[itemIndex]
        
        itemImage?.image = UIImage(named: selectedItem?.title ?? "Image not found")
        companyLabel?.text = selectedItem?.company.uppercased()
        titleLabel?.text = selectedItem?.title.capitalized
        priseLabel?.text = selectedItem?.formatPrise
    }
    
    private func nextIndex() {
        itemIndex = (itemIndex + 1) % items.count
    }
    
    // MARK: Создание относительного расположения элементов
    private func setupConstrains() {
        guard let itemImage,
              let companyLabel,
              let titleLabel,
              let priseLabel,
              let nextItemButton
        else {
            return
        }
    
        
        itemImage.translatesAutoresizingMaskIntoConstraints = false
        companyLabel.translatesAutoresizingMaskIntoConstraints = false
        titleLabel.translatesAutoresizingMaskIntoConstraints = false
        priseLabel.translatesAutoresizingMaskIntoConstraints = false
        nextItemButton.translatesAutoresizingMaskIntoConstraints = false
        
        NSLayoutConstraint.activate([
            // изображение
            itemImage.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 10),
            itemImage.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            itemImage.widthAnchor.constraint(equalTo: view.widthAnchor),
            itemImage.heightAnchor.constraint(equalTo: view.heightAnchor, multiplier: 0.5),
            
            // название компании
            companyLabel.topAnchor.constraint(equalTo: itemImage.bottomAnchor),
            companyLabel.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 10),
            
            // название предмета
            titleLabel.topAnchor.constraint(equalTo: companyLabel.bottomAnchor),
            titleLabel.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 10),
            
            // цена предмета
            priseLabel.topAnchor.constraint(equalTo: titleLabel.bottomAnchor, constant: 10),
            priseLabel.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 10),
            
            // кнопка перехода к следующему предмету
            nextItemButton.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor, constant: -10),
            nextItemButton.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            nextItemButton.widthAnchor.constraint(equalTo: view.heightAnchor, multiplier: 0.4),
            nextItemButton.heightAnchor.constraint(equalTo: view.heightAnchor, multiplier: 0.07)
            
        ])
    }
}

