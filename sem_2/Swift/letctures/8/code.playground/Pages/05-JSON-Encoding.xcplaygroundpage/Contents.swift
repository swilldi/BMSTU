import Foundation

struct Post: Encodable {
    let userId: Int
    let id: Int?
    let title: String
    let body: String
}

let url = URL(string: "https://jsonplaceholder.typicode.com/posts")!
var request = URLRequest(url: url)
request.httpMethod = "POST"
request.setValue("application/json", forHTTPHeaderField: "Content-Type")

let post = Post(userId: 1, id: nil, title: "Новость дня", body: "Сегодня хорошая погода!")
let jsonData = try JSONEncoder().encode(post)
request.httpBody = jsonData

URLSession.shared.dataTask(with: request) { data, response, error in
    if let data = data {
        print("✅ Данные получены: \(String(data: data, encoding: .utf8) ?? "")")
    } else if let error = error {
        print("❌ Ошибка: \(error)")
    }
}.resume()

waitAndFinish()
