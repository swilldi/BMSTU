// Пример с лекции

func multipleByTwo(array: [Double]) -> [Double] {
    var modifiedArray: [Double] = []
    for element in array {
        modifiedArray.append(element * 2)
    }
    return modifiedArray
}

func divideByTwo(array: [Double]) -> [Double] {
    var modifiedArray: [Double] = []
    for element in array {
        modifiedArray.append(element / 2)
    }
    return modifiedArray
}

func sumWithTwo(array: [Double]) -> [Double] {
    var modifiedArray: [Double] = []
    for element in array {
        modifiedArray.append(element + 2)
    }
    return modifiedArray
}

func applyFor(array: [Double], action: (Double) -> Double) -> [Double] {
    var modifiedArray: [Double] = []
    for element in array {
        modifiedArray.append(action(element))
    }
    return modifiedArray
}

let multipleByTwo: (Double) -> Double = { argument in
    argument * 2
}

let divideByTwo: (Double) -> Double = { argument in
    argument / 2
}

let sumWithTwo: (Double) -> Double = { argument in
    argument + 2
}

// map

let numbers: [Double] = [1,2,3,4,5]

let multipled = numbers.map { argument in
    multipleByTwo(argument)
}
print(multipled)

let multipled2 = numbers.map {
    multipleByTwo($0)
    sumWithTwo($0)
    return $0
}
print(multipled2)

let multipled3 = numbers.map(multipleByTwo)
print(multipled3)

let strings = ["asd", "WE", "Asd", "J", "ss"]
let stringsLow = strings.map { $0.lowercased() }
print(stringsLow)

// mapValues

let courses = [
    "Student1": 1,
    "Student2": 3,
    "Student3": 2
]
let nextYear = courses.mapValues { $0 + 1 }
print(nextYear)

// filter

let evenNumbers = [10, 15, 22, 33, 40, 51].filter { $0 % 2 == 0 }
print(evenNumbers)

let evenNumbers2 = [15, 33, 51].filter { $0 % 2 == 0 }
print(evenNumbers2)

let shortStrings = ["a", "aaa", "aaaaaa", "aa"].filter { $0.count < 3 }
print(shortStrings)

// reduce

let numbers3 = [1, 2, 3, 4, 5]
let sum = numbers3.reduce(0) { $0 + $1 }
print(sum)

let words = ["Swift", "", "is", "", "", "", "awesome"]
let sentence = words.reduce("") { $0 + " " + $1 }
print(sentence)

let sentence2 = words.reduce("") {
    if $0.isEmpty {
        return $1
    } else {
        return $0 + " " + $1
    }
}
print(sentence2)

let sentence3 = words.reduce("") {
    $0.isEmpty ? $1 : $0 + " " + $1
}
print(sentence3)

let sentence4 = words.reduce("") {
    guard !$0.isEmpty else { return $1 }
    if $1.isEmpty {
        return $0
    } else {
        return $0 + " " + $1
    }
}
print(sentence4)

// flatMap

let array = [[1, 2, 3], [4, 5], [6]]
let flattened = array.flatMap { $0 }
print(flattened)

let dict = [[1:2], [2:3], [3:4]]
let flattenedDict = dict.flatMap { $0 }
print(flattenedDict)

// compactMap

let optionalNumbers: [Int?] = [1, nil, 3, nil, 5]
let nonNilNumbers = optionalNumbers.compactMap { $0 }
print(nonNilNumbers)

let possibleNumbers = ["1", "2", "three", "///4///", "5"]
let onlyNumbers = possibleNumbers.compactMap { str in Int(str) }
print(onlyNumbers.reduce(0) { $0 + $1 })

// zip

let names = ["Student1", "Student2", "Student3"]
let scores = [3, 5, 4]

let result = Array(zip(names, scores))
print(result)

let names2 = ["Student1", "Student2", "Student3"]
let scores2 = [3, 5, 4, 7, 8]

let result2 = Array(zip(names2, scores2))
print(result2)

let names3 = ["Student1", "Student2", nil, "Student3", "Student4", "Student5"]
let scores3 = [3, 5, 4]

let result3 = Array(zip(names3, scores3))
print(result3)

struct Student {
    var name: String
    let grade: Int
}

let student1 = Student(name: "Student1", grade: 5)
var student2 = student1
student2.name = "Student2"

let arrayEx = [1,2,3,4]
var array2Ex = arrayEx
array2Ex.append(5)

print(arrayEx)
print(array2Ex)

