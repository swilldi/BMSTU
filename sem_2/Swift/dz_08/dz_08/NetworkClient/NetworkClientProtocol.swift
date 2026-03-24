//
//  NetworkClient.swift
//  dz_08
//
//  Created by Dmitriy Dudyrev on 16.04.2025.
//

import Foundation

protocol NetworkClientInput: AnyObject {
    func get <ResponseSchema: Decodable>(
        urlString: String,
        completion: @escaping (Result<ResponseSchema, NetworkClientError>) -> Void
    )
    
    func post<ResponseSchema: Decodable>(
        urlString: String,
        requestBody: Encodable,
        completion: @escaping (Result<ResponseSchema, NetworkClientError>) -> Void
    )
    
    func download(
        urlString: String, progressBlock: ((Double) -> Void)?,
        completion: @escaping (Result<Data, NetworkClientError>) -> Void
        )
}

