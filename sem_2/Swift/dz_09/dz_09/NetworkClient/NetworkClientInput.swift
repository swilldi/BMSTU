//
//  NetworkClientInput.swift
//  dz_09
//
//  Created by Dmitriy Dudyrev on 18.04.2025.
//
import Foundation

protocol NetworkClientInput: AnyObject {
    func downloadIamge(_ url: String)
    func clearDownloadedData()
    
    var queue: DispatchQueue { get }
    var group: DispatchGroup { get }
    var lock: NSLock { get }
    
    var downloadedData: [Data] { get }

}
