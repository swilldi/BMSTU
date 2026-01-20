import Foundation
import PlaygroundSupport

public func waitAndFinish(_ seconds: TimeInterval = 3) {
    PlaygroundPage.current.needsIndefiniteExecution = true
    DispatchQueue.main.asyncAfter(deadline: .now() + seconds) {
        print("🏁 Завершение работы")
        PlaygroundPage.current.finishExecution()
    }
}
