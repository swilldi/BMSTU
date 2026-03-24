//
//  ViewController.swift
//  testURL
//
//  Created by Dmitriy Dudyrev on 15.04.2025.
//

import UIKit

final class MainViewController: UIViewController {
    private let presenter: MainPresenterInput
    private var loadedImages = 0
    private var dowloadedImages = [IndexPath: UIImage]()
    private var totalImages: Int {
        presenter.itemsCount
    }
    
    private var loadedIndexPaths: Set<IndexPath> = []
    private var imageCache: [IndexPath: UIImage] = [:]
    
    private lazy var tableView: UITableView = {
        let tableView = UITableView()
        tableView.register(UITableViewCell.self, forCellReuseIdentifier: Constant.cellId)
        tableView.translatesAutoresizingMaskIntoConstraints = false
        tableView.dataSource = self
        tableView.delegate = self
        
        return tableView
    }()
    
    private lazy var progressLabel: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.text = "Загрузки нет"
        return label
    }()

    private lazy var downloadingIndicator: UIView = { //  Спиннер загрузки
        let view = UIView(frame: self.view.bounds)

        let indocator = UIActivityIndicatorView()
        indocator.style = .large
        indocator.center = view.center
        indocator.startAnimating()

        view.addSubview(indocator)
        view.isHidden = true
        return view
    }()
    
    init(presenter: MainPresenterInput) {
        self.presenter = presenter
        super.init(nibName: nil, bundle: nil)
    }
    
    @available(*, unavailable)
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupView()
        presenter.viewDidLoad()
    }
    
    private func setupView() {
        view.backgroundColor = .white
        
        view.addSubview(tableView)
        view.addSubview(progressLabel)
        view.addSubview(downloadingIndicator)
        
        NSLayoutConstraint.activate([
            progressLabel.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor),
            progressLabel.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            
            tableView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            tableView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
            tableView.topAnchor.constraint(equalTo: progressLabel.bottomAnchor, constant: 20),
            tableView.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor),
        ])
    }
}

extension MainViewController: MainViewInput {
    func updateDowloadingProcess() {
        progressLabel.text = "Загружено: \(dowloadedImages.count / totalImages * 100)%"
    }
    
    func updateTable() {
        tableView.reloadData()
    }
    
    func downloadImage(for item: Item, at indexPath: IndexPath) {
        guard let url = URL(string: item.image) else { return }
        
        if dowloadedImages.keys.contains(indexPath) {
            return
        }
        
        URLSession.shared.dataTask(with: url) { [weak self] data, _, _ in
            guard let self, let data, let image = UIImage(data: data) else { return }
            DispatchQueue.main.async {
                let resizedImage = self.configureImage(image, newSize: CGSize(width: 40, height: 40))
                self.dowloadedImages[indexPath] = resizedImage
                self.updateDowloadingProcess()
                
                if let visibleCell = self.tableView.cellForRow(at: indexPath) {
                    var updatedContent = visibleCell.defaultContentConfiguration()
                    updatedContent.text = item.title
                    updatedContent.image = resizedImage
                    
                    updatedContent.imageProperties.maximumSize = CGSize(width: 40, height: 40)
                    visibleCell.contentConfiguration = updatedContent
                }
            }
        }.resume()
    }
            
    func configureImage(_ image: UIImage, newSize: CGSize) -> UIImage {
        let renderer = UIGraphicsImageRenderer(size: newSize)
        return renderer.image { _ in
            image.draw(in: CGRect(origin: .zero, size: newSize))
        }
    }
}

extension MainViewController: UITableViewDataSource {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        presenter.itemsCount
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        guard let cell = tableView.dequeueReusableCell(withIdentifier: Constant.cellId) else {
            return UITableViewCell()
        }
        
        let item = presenter.item(at: indexPath.row)
        var content = cell.defaultContentConfiguration()
        
        if let image = dowloadedImages[indexPath] {
            content.image = image
        } else {
            content.image = UIImage(systemName: "photo")
            downloadImage(for: item, at: indexPath)
        }
        
        content.text = item.title
        cell.contentConfiguration = content
        return cell
    }
}

extension MainViewController: UITableViewDelegate {}

extension MainViewController {
    private enum Constant {
        static let cellId = "cellId"
    }
}
