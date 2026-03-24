//
//  NetworkClienError.swift
//  dz_08
//
//  Created by Dmitriy Dudyrev on 16.04.2025.
//

import Foundation

enum NetworkClientError: Error {
    /// Неверный URL
    case invalidURL
    /// Ошибка сериализации данных
    case encodingError(Error)
    /// Ошибка сети, обычно из "NSURLErrorDomain
    case networkError(Error)
    /// Ошибка HTTP (status code 4xx, 5xx)
    case httpError(Int)
    /// Ошибка декодирования
    case decodingError(Error)

}
