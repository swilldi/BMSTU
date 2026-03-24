//
//  ViewProtocol.swift
//  dz_08
//
//  Created by Dmitriy Dudyrev on 16.04.2025.
//

import UIKit

protocol MainViewInput: AnyObject {
    func updateTable()
    func updateDowloadingProcess()
}
