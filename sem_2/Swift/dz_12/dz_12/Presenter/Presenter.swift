//
//  Presenter.swift
//  dz_09
//
//  Created by Dmitriy Dudyrev on 18.04.2025.
//

import Foundation

class Presenter: PresenterInput {
    weak var view: ViewController?
    private let networkClient: NetworkClientInput
    
    let queue = DispatchQueue(label: "downloading")
    let group = DispatchGroup()
    let lock = NSLock()
    
    let imagesUrl: [String] = [
        "https://www.alleycat.org/wp-content/uploads/2016/06/Day-32-Denby.jpg",
        "https://wallpapers.com/images/hd/labrador-puppy-pictures-ebqowhvos88tknf0.jpg",
        "https://i.pinimg.com/736x/11/1a/54/111a5480ff5f17d14a2f9290c4f9641a.jpg"
    ]
    
    init(networkClient: NetworkClientInput, view: ViewController) {
        self.networkClient = networkClient
        self.view = view
    }
    
    func downoadImages() {
        for url in imagesUrl {
            networkClient.downloadImage(url)
        }

        didFinishLoadingImages()
    }
    
    private func didFinishLoadingImages() {
        networkClient.group.notify(queue: .main) {
            print("Картинки загрузились")
            print(self.networkClient.downloadedData)
            self.view?.stopDownloadingIndicator()
            self.view?.updateImages(from: self.networkClient.downloadedData)
            self.networkClient.clearDownloadedData()
        }
    }
}
