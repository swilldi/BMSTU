import Foundation

func sendPost() async {
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

    do {
        let (data, response) = try await URLSession.shared.data(for: request)
        print("✅ Ответ получен:")
        if let responseString = String(data: data, encoding: .utf8) {
            print(responseString)
        }
    } catch {
        print("❌ Ошибка: \(error)")
    }
}

Task {
    await sendPost()
}

waitAndFinish()
