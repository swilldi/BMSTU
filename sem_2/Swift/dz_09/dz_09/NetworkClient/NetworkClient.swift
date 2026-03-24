//
//  Client.swift
//  dz_09
//
//  Created by Dmitriy Dudyrev on 18.04.2025.
//

import Foundation
import Alamofire

class NetworkClient: NetworkClientInput {
    
    let queue = DispatchQueue(label: "downloading", attributes: .concurrent)
    let group = DispatchGroup()
    let lock = NSLock()
    
    var downloadedData = [Data]()
    
    func clearDownloadedData() {
        downloadedData = []
    }
    
    func downloadIamge(_ url: String) {
        guard let url = URL(string: url) else {
            print("Ошибка: неправильная URL")
            return
        }

        self.group.enter()
        queue.async {
            AF.request(url).responseData { response in
                self.group.leave()
                self.lock.lock()
                
                switch response.result {
                case .success(let data):
                    print("скачалось ")
                    self.downloadedData.append(data)
                    print(data)
                case .failure(let error):
                    print("Ошибка загрузки: \(error.localizedDescription)")
                }
                self.lock.unlock()
            }
            
        }
    }
}
