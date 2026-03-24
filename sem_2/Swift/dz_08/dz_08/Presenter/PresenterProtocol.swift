//
//  PresenterProtocol.swift
//  dz_08
//
//  Created by Dmitriy Dudyrev on 16.04.2025.
//

import Foundation

protocol MainPresenterInput: AnyObject {
    var itemsCount: Int { get }
    func viewDidLoad()
    func item(at index: Int) -> Item
}
