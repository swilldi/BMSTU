//
//  Presenter.swift
//  dz_08
//
//  Created by Dmitriy Dudyrev on 16.04.2025.
//

import Foundation
import UIKit

final class MainPresenter {
    weak var view: MainViewInput?
    private let networkClient: NetworkClientInput
    private var items: [Item] = []
    
    init(networkClient: NetworkClientInput) {
        self.networkClient = networkClient
    }
    
    private func loadItems() {
        let url = "https://fakestoreapi.com/products"
        let completion: ((Result<[Item], NetworkClientError>) -> Void) = { result in
            switch result {
                case .success(let posts):
                    self.items = posts
                    DispatchQueue.main.async {
                        self.view?.updateTable()
                    }
                case .failure (let error):
                    print (error.localizedDescription)
            }
        }
        networkClient.get(urlString: url, completion: completion)
    }
}


extension MainPresenter: MainPresenterInput {
    var itemsCount: Int {
        items.count
    }
    func viewDidLoad() {
        loadItems()
    }
    
    func item(at index: Int) -> Item {
        items[index]
    }
}
