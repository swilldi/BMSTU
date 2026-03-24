/*
 Есть словарь, в котором ключ - это имя студента, а значение - его оценка на экзамене (может быть nil, если не сдал).
 Нужно найти и вывести среднюю оценку только для студентов, у которых есть оценка. Если не сдали все, так и вывести.
 */

import Foundation

var sumScore = 0, numbersOfScore = 0
var dict1: [String:Int?] = ["A": nil, "B": nil, "C": nil, "D": nil, "E": nil, "F": nil, "G": nil]

for score in dict1.values {
    if let score = score {
        sumScore += score
        numbersOfScore += 1
    }
}

if numbersOfScore == 0 {
    print("Никто не сдал")
} else {
    print(Double(sumScore) / Double(numbersOfScore))
}
