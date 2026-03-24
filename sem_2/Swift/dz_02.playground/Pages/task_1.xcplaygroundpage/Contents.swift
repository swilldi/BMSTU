/*
 Дана строка текста, вывести количество уникальных слов в этой строке. Слова разделены пробелами, регистр не учитывается.
 Подсказка: Обратите внимание на методы работы со строками (split, lowercased) и использование коллекций.
 
 let string1 = "apple Orange pineapple PEAR"
 Output: 4

 let string2 = "apple aPPle appLe Apple"
 Output: 1

 */

import Foundation

//let string = "apple Orange pineapple PEAR"
//let string = "apple aPPle appLe Apple"
let string = "1 2 4 2 1 3 5 3 app App aPP ApA 4 5 6 3 2"
var uniqueWords = Set<String>()
for word in string.split(separator: " ") {
    uniqueWords.insert(String(word).lowercased())
}
print(uniqueWords.count)

