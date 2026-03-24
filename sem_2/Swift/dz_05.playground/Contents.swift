import Foundation

// MARK: ЗАДАНИЕ 5

// MARK: Классы с циклической ссылкой
class Person {
    let name: String
    var car: Car?

    init(name: String, car: Car?) {
        print("Создан \(name)")
        self.name = name
        self.car = car
    }

    deinit {
        print("Уничтожен \(name)")
    }
}

class Car {
    var color: String
    var owner: Person?

    init(color: String, owner: Person?) {
        print("Создана машина \(color)")
        self.color = color
        self.owner = owner
    }

    deinit {
        print("Уничтожена машина \(color)")
    }
}


var person1: Person? = Person(name: "Jack", car: nil)
var car1: Car? = Car(color: "Red", owner: person1)
person1!.car = car1
print("Кол-во ссылок на car1: \(CFGetRetainCount(car1))")
print("Кол-во ссылок на person1: \(CFGetRetainCount(person1))")
// удалаяем экземпляр person1
person1 = nil
// пытаемся обратиться к person через car, выводит nil
print("car1?.owner: \(car1?.owner)")
// удаляем car1
car1 = nil
// провереям, что нет возможности обратиться
print("car1?.owner: \(car1?.owner)")
print("person1?.car: \(person1?.car)")

print("---")

// тоже самое но начнем с жкземпляра car1
var person2: Person? = Person(name: "Ann", car: nil)
var car2: Car? = Car(color: "Green", owner: person2)
person2!.car = car2
print("Кол-во ссылок на car2: \(CFGetRetainCount(car2))")
print("Кол-во ссылок на person2: \(CFGetRetainCount(person2))")
// удалаяем экземпляр car2
car2 = nil
// пытаемся обратиться к person через car, выводит nil
print("person2?.car: \(person2?.car)")
//удаляем perosn2
person2 = nil
// провереям, что нет возможности обратиться
print("person2?.car: \(person2?.car)")
print("car2?.owner: \(car2?.owner)")

/*
 MARK: Мини вывод
 Ну на данный момент я не нашел функции, которая выводи
 кол-во ссылок на объект, поэтому хотя бы тексто напишу.
 В данном случае 4 раза выполняется print() из инициализаторов,
 но ни одного print'а из деиницилизаторов => ни один из экземпляров не
 удалаяется полностью, а висит в памяти
 */



//MARK: Без циклического замыкания
//class Person {
//    let name: String
//    weak var car: Car?
//
//    init(name: String, car: Car?) {
//        print("Создан \(name)")
//        self.name = name
//    }
//
//    deinit {
//        print("Уничтожен \(name)")
//    }
//}
//
//class Car {
//    var color: String
//    weak var owner: Person?
//
//    init(color: String, owner: Person?) {
//        print("Создана машина \(color)")
//        self.color = color
//        self.owner = owner
//    }
//
//    deinit {
//        print("Уничтожена машина \(color)")
//    }
//}
//
//
//var person1: Person? = Person(name: "Jack", car: nil)
//var car1: Car? = Car(color: "Red", owner: person1)
//person1!.car = car1
//print("Кол-во ссылок на car1: \(CFGetRetainCount(car1))")
//print("Кол-во ссылок на person1: \(CFGetRetainCount(person1))")
//// удалаяем экземпляр person1
//person1 = nil
//// пытаемся обратиться к person через car, выводит nil
//print("car1?.owner: \(car1?.owner)")
//// удаляем car1
//car1 = nil
//// провереям, что нет возможности обратиться
//print("car1?.owner: \(car1?.owner)")
//print("person1?.car: \(person1?.car)")
//
//print("---")
//
//// тоже самое но начнем с жкземпляра car1
//var person2: Person? = Person(name: "Ann", car: nil)
//var car2: Car? = Car(color: "Green", owner: person2)
//person2!.car = car2
//print("Кол-во ссылок на car2: \(CFGetRetainCount(car2))")
//print("Кол-во ссылок на person2: \(CFGetRetainCount(person2))")
//// удалаяем экземпляр car2
//car2 = nil
//// пытаемся обратиться к person через car, выводит nil
//print("person2?.car: \(person2?.car)")
////удаляем perosn2
//person2 = nil
//// провереям, что нет возможности обратиться
//print("person2?.car: \(person2?.car)")
//print("car2?.owner: \(car2?.owner)")

/*
 MARK: Мини вывод
 при присовении экземплярую nil выполняется его деинициализтор
 => при присовении экземпляру nil он уничтожается полностью, не висит в памяти
 и не появляется зацикливания ссылок
 */


//// MARK: ЗАДАНИЕ 6
//
//class Animal {
//    let name: String
//
//    init(name: String) {
//        self.name = name
//    }
//
//    func speak() {}
//
//}
//
//class Dog: Animal {
//    let voice = "Woaf!"
//
//    override func speak() {
//        print(voice)
//    }
//}
//
//class Cat: Animal {
//    let voice = "Meow!"
//
//    override func speak() {
//        print(voice)
//    }
//}
//
//let dog1 = Dog(name: "Astin"), dog2 = Dog(name: "Crocky"), cat1 = Cat(name: "Tom")
//let animals: Array<Animal> = [dog1, cat1, dog2]
//for animal in animals {
//    animal.speak()
//}

/*
 При наследовании используется virtual table диспечиризация, и поэтому для переорпеделяемого
 метода в дочернем классе изменяется указатель на реалицаю метода. Из-за этого
 реализация метода speak в Cat, Dog, Animal не связаны.
 
 Поэтому для экземпляров класса Dog будет вызываться метод Dog.speak (строка 105, если я ничего не поменял),
 для экземпляров класса Cat будет вызываться метод Cat.speak (строка 114).
 Потому что опять же, у каждого из данных подклассов собсвенный указатель на реализацию метода speak
*/
