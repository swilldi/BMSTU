import Foundation

let url = URL(string: "https://jsonplaceholder.typicode.com/posts")!

let task = URLSession.shared.dataTask(with: url) { data, response, error in
    if let data = data {
        print("✅ Данные получены: \(data)")
    } else if let error = error {
        print("❌ Ошибка: \(error)")
    }
}

task.resume()

waitAndFinish()
