/*
 Переменные/константы
*/

var constant = 2
constant = 3
// попробуем поменять

/*
 Вывод данных
*/

print("Hello")
print("Number - \(constant)")
print("Square - \(constant * constant)")

/*
 Аннотация типов
*/

// constant = "aaa"

/*
 Перечисления
*/

enum Figure {
    case square(Int)
    case circle(Int)
    case rectangle(Int, Int)
}

enum Example {
    case case1(Figure)
}

let square = Figure.square(4)
let rectangle: Figure = .rectangle(1, 2)

// инициализация переменных

/*
 Оператор switch
*/

var var1 = 4
if var1 < 0 {
    print("-")
} else if var1 > 0 {
    print("+")
} else if var1 == 0 {
    print("0")
}

switch var1 {
case 1,2,3:
    print("-")
default:
    print("0 or +")
}

let ourFigure: Figure = .circle(4)

switch ourFigure {
case .square:
    print("It's square")
case .circle:
    print("It's circle")
case .rectangle:
    print("It's rectangle")
}

switch ourFigure {
case .square, .circle, .rectangle:
    print("It's figure")
case .circle:
    print("It's circle")
case .rectangle:
    print("It's rectangle")
}

switch ourFigure {
case .square(let a):
    print("\(a * a)")
case .circle(let r):
    print("\(3.14 * Double(r) * Double(r) / 2)")
case .rectangle(let a, let b):
    print("\(a * b)")
}

// используем ассоциативные значения

/*
 Опционал
*/

var optional: Int? = 5

switch optional {
case .none:
    print("Нет значения")
case .some(let realValue):
    print("\(realValue)")
}

let five = 5
var two: Int? = nil

print("Сумма: \(five + (two ?? 2))")

two = 2
if let unwrappedTwo = two {
    print("Sum: \(five + unwrappedTwo)")
} else {
    print("Incorrect")
}

// опционал это enum
// ошибки еще раз на примере

/*
 Кортежи
*/

var student1: (String, Double, Int) = ("Настя", 3.4, 1)
student1.2 += 1

var student2 = (name: "Никита", grade: 5.0, course: 2)
let name2 = student2.name

// показать как можно еще разложить на неск переменных

/*
 Массивы
*/

var array1 = [1, 2]
array1[0] = 2

var numbers = [1, 2, 3]

numbers.append(4)

numbers += [5]
numbers += [6, 7]
numbers.insert(0, at: 0)

numbers.remove(at: 0)
// numbers.remove(at: 10) // что будет?

/*
 Множества
*/

var alphabet: Set = ["a", "b", "c"]

alphabet.insert("a")
alphabet.insert("d")
alphabet.remove("d")
alphabet.contains("d")

/*
 Словари
*/

var romeNumbers = ["I": 2, "V": 5, "X": 10]

romeNumbers["I"] = 1 // обновили
romeNumbers["L"] = 50 // добавили
romeNumbers["L"] = nil // удалили

romeNumbers

romeNumbers.updateValue(50, forKey: "L")
romeNumbers.updateValue(60, forKey: "L")

if let oldValue = romeNumbers.updateValue(50, forKey: "L") {
    print("Старое значение \(oldValue).")
}

if let number = romeNumbers["L"] {
    print("L - \(number).")
} else {
    print("L не существует")
}
romeNumbers

if let removedValue = romeNumbers.removeValue(forKey: "L") {
    print("Удалили \(removedValue).")
} else {
    print("L не существует")
}

/*
 Циклы
*/

let values = ["one", "two", "three"]

for value in values {
    print(value)
}

for (index, value) in values.enumerated() {
    print("Item at \(index) is \(value)")
}

for (number, romeNumber) in romeNumbers {
  print("\(number): \(romeNumber)")
}

for (_, romeNumber) in romeNumbers {
  print("\(romeNumber)")
}

for romeNumber in romeNumbers.keys {
  print("Римская цифра: \(romeNumber)")
}

for romeNumber in romeNumbers.values {
  print("Цифра: \(romeNumber)")
}

/*
 Примеры
 */

/*
 Перевернуть массив
*/

var array2 = [1,2,3]
// array2.reverse()

var reversedArray2: [Int] = []
var count = array2.count - 1

while count >= 0 {
    reversedArray2.append(array2[count])
    print(array2[count])
    count -= 1
}
reversedArray2

//var reversedArray3: [Int] = []
//count = array2.count - 1
//for i in (count-1)...0 {
//    reversedArray3.append(array2[i])
//}
//reversedArray3

/*
 Дан массив из чисел и строк, получить сумму всех числовых значений
*/

let arrayNew = ["1", "a", "vb1n", "3", "44"]
var sum = 0

for element in arrayNew {
    let elementInt = Int(element)
//    print(elementInt)
//    if let elementInt {
//        sum += elementInt
//    }
    guard let elementInt else {
        continue
        // break, return, throw
    }
    sum += elementInt
}

print(sum)

/*
 Определить количество каждого уникального символа в строке
*/

let string = "buuu"
var dict: [Character: Int] = [:]

for char in string {
    if let count = dict[char] {
        dict[char] = count + 1
    } else {
        dict[char] = 1
    }
//    dict[char, default: 0] += 1
}
dict
