/*
 Дана строка, состоящая только из круглых скобок. Проверить является ли последовательность скобок корректной и вывести результат в консоль.
 let string1 = "(())"
 Output: Корректная

 let string2 = "))(("
 Output: Некорректная

 let string1 = "()()()"
 Output: Корректная
 */

import Foundation

let string = "((99))"
var countOpen: Int = 0
var result = "Корректная"

for symbol in string {
    if symbol == "(" {
        countOpen += 1
    } else if symbol == ")" {
        countOpen -= 1
    }
    
    if countOpen < 0 {
        result = "Некорректная"
        break
    }
}

if countOpen != 0 {
    result = "Некорректная"
}

print(result)
