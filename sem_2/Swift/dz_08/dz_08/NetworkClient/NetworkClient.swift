//
//  NetworkClient.swift
//  dz_08
//
//  Created by Dmitriy Dudyrev on 16.04.2025.
//

import Foundation

final class NetworkClient: NSObject {
    private var progressBlocks: [Int: (Double) -> Void] = [:]
    private var competionBlocks: [Int: (Result<Data, NetworkClientError>) -> Void] = [:]
    
    private lazy var urlSession: URLSession = {
        let configuration = URLSessionConfiguration.default
        return URLSession(configuration: configuration, delegate: self, delegateQueue: nil)
    }()
}

extension NetworkClient: NetworkClientInput {
    func get<ResponseSchema: Decodable>(
        urlString: String,
        completion: @escaping (Result<ResponseSchema, NetworkClientError>) -> Void
    ) {
        guard let url = URL(string: urlString) else {
            completion(.failure(.invalidURL))
            return
        }
        let task = urlSession.dataTask(with: url) { data, response, error in
            if let data = data {
                do {
                    let result = try JSONDecoder().decode(ResponseSchema.self, from: data)
                    completion(.success(result))
                } catch {
                    completion(.failure(.decodingError(error)))
                }
            } else if let error = error {
                completion(.failure(.networkError(error)))
            }
        }
        task.resume()
    }
    func post<ResponseSchema: Decodable>(
        urlString: String,
        requestBody: Encodable,
        completion: @escaping (Result<ResponseSchema, NetworkClientError>) -> Void
    ) {
        guard let url = URL(string: urlString) else {
            completion(.failure(.invalidURL))
            return
        }
        
        var request = URLRequest(url: url)
        request.httpMethod = "POST"
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        do {
            let jsonData = try JSONEncoder().encode(requestBody)
            request.httpBody = jsonData
        } catch {
            completion(.failure(.encodingError(error)))
        }
        
        let task = urlSession.dataTask(with: request) { data, response, error in
            if let data = data {
                do {
                    let result = try JSONDecoder().decode(ResponseSchema.self, from: data)
                    completion(.success(result))
                } catch {
                    completion(.failure(.decodingError(error)))
                }
            } else if let error = error {
                completion(.failure(.networkError(error)))
            }
        }
        task.resume()
        
    }
    
    func download(
        urlString: String,
        progressBlock: ((Double) -> Void)?,
        completion: @escaping (Result<Data, NetworkClientError>) -> Void) {
            guard let url = URL(string: urlString) else {
                completion(.failure(.invalidURL))
                return
            }
            var request = URLRequest(url: url)
            request.httpMethod = "GET"
            
            let task = urlSession.downloadTask(with: request)
            progressBlocks[task.taskIdentifier] = progressBlock
            competionBlocks[task.taskIdentifier] = completion
            task.resume ( )
        }
}

extension NetworkClient: URLSessionTaskDelegate {
    func urlSession(
        _ session: URLSession,
        task: URLSessionTask,
        didCompleteWithError error: Error?
    ) {
        if let error = error {
            competionBlocks[task.taskIdentifier]?(.failure(.networkError(error)))
            
            competionBlocks.removeValue(forKey: task.taskIdentifier)
            progressBlocks.removeValue(forKey: task.taskIdentifier)
        }
    }
}

extension NetworkClient: URLSessionDownloadDelegate {
    func urlSession(_ session: URLSession, downloadTask: URLSessionDownloadTask, didFinishDownloadingTo location: URL) {
        if let completion = competionBlocks[downloadTask.taskIdentifier],
           let data = try? Data (contentsOf: location) {
            completion(.success(data))
        }
        competionBlocks.removeValue (forKey: downloadTask.taskIdentifier)
        progressBlocks.removeValue(forKey: downloadTask.taskIdentifier)
    }
    
    func urlSession(
        _ session: URLSession,
        downloadTask: URLSessionDownloadTask,
        didWriteData bytesWritten: Int64,
        totalBytesWritten: Int64,
        totalBytesExpectedToWrite: Int64
    )
    {
        if totalBytesExpectedToWrite > 0 {
            let progress = Double(totalBytesWritten) / Double(totalBytesExpectedToWrite)
            progressBlocks[downloadTask.taskIdentifier]?(progress)
        }
    }
}
