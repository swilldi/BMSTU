//
//  ViewController.swift
//  dz_09
//
//  Created by Dmitriy Dudyrev on 18.04.2025.
//

import UIKit

protocol ViewControllerInput: AnyObject {
    func stopDownloadingIndicator()
    func updateImages(from imagesData: [Data])
}

