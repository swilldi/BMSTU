import Foundation

let url = URL(string: "https://jsonplaceholder.typicode.com/posts")!
var request = URLRequest(url: url)
request.httpMethod = "POST"
request.setValue("application/json", forHTTPHeaderField: "Content-Type")

let post = [
    "userId": "1",
    "title": "Новость дня",
    "body": "Сегодня хорошая погода!"
]
let jsonData = try? JSONSerialization.data(withJSONObject: post)
request.httpBody = jsonData

print("📤 Отправляем запрос:")
print("URL: \(request.url?.absoluteString ?? "")")
print("Метод: \(request.httpMethod ?? "")")
print("Заголовки: \(request.allHTTPHeaderFields ?? [:])")
if let body = request.httpBody {
    print("Тело: \(String(data: body, encoding: .utf8) ?? "")")
}

URLSession.shared.dataTask(with: request) { data, response, error in
    if let data = data {
        print("✅ Данные получены: \(data)")
    } else if let error = error {
        print("❌ Ошибка: \(error)")
    }
}.resume()

waitAndFinish()
