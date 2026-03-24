/*
 Дан массив строк. Нужно сгруппировать строки по количеству символов в ней, вывести результат.
 Подсказка: Используйте правильную коллекцию.
*/

import Foundation

let array = ["a", "b3", "cc", "dfa", "4444444", "dfgdsfg"]
var countSymbols = [Int:Array<String>]()

// перебор элеметов массива
for str in array {
    countSymbols[str.count] = (countSymbols[str.count] ?? []) + [str]
}

for amount in countSymbols.keys.sorted() {
    if let elements = countSymbols[amount] {
        print("\(amount) – \(elements)")
    }
}
