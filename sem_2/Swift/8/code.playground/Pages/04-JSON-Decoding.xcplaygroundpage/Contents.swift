import Foundation

struct Post: Decodable {
    let userId: Int
    let id: Int?
    let title: String
    let body: String
}

let url = URL(string: "https://jsonplaceholder.typicode.com/posts")!

let task = URLSession.shared.dataTask(with: url) { data, response, error in
    if let data = data {
        do {
            let posts = try JSONDecoder().decode([Post].self, from: data)
            print("✅ Успешно распарсили \(posts.count) постов")
        } catch {
            print("❌ Ошибка парсинга: \(error)")
        }
    } else if let error = error {
        print("❌ Ошибка: \(error)")
    }
}

task.resume()

waitAndFinish()
