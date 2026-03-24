/*
Создайте структуру книги, которая позволит хранить в себе: Название, Автора, Цену, Жанр (сделайте количество жанров ограниченным используя перечисление).

Создайте класс библиотеки. В нем мы будем хранить книги.
Добавьте методы:
- Добавление книги.
- Фильтрация по жанру.
- Фильтрация по имени.

Создайте класс пользователя. У него будет
 - имя
 - скидка в магазине (как понял вводиться процент скидки. Т.е. в примере скидка 1.5%)
 - корзина с книгами.
Добавьте методы:
- Добавление книг в корзину.
- Подсчет общей стоимости книг в корзине с учетом скидки пользователя.
- Вывод корзины в отсортированном порядке (сделайте различные варианты сортировки по алфавиту/по цене, используя один метод).
*/

enum Genre: String {
    case adventure = "adventure"
    case fiction = "fiction"
    case scienceFiction = "scienceFiction"
    case novel = "novel"
    case poems = "poems"
}


struct Book {
    let title: String
    let author: String
    var price: Float
    let genre: Genre
    
    var description: String {
        "'\(title)' \(author) (\(genre)) – \(price)"
    }
}

class Library {
    var bookShelf = [Book]()
    
    init(){}
    
    func addBook(_ book: Book) {
        bookShelf.append(book)
    }
    
    func addCollectionBook(_ books: [Book]) {
        bookShelf.append(contentsOf: books)
    }
    
    func filterBooks(by genre: Genre) -> [Book] {
        bookShelf.filter { $0.genre == genre }
    }
    
    func filterBooks(byName title: String) -> [Book] {
        bookShelf.filter { $0.title.contains(title) }
    }
    
}



class User {
    
    enum SortType {
        case priceUp
        case priceDown
        case nameUp
        case nameDown
    }
    
    var name: String
    var discount: Float
    var cart = [Book]()
        
    init(name: String, discount: Float = 0) {
        self.name = name
        self.discount = discount / 100
    }
    
    func addToCart(_ books: [Book]) {
        cart.append(contentsOf: books)
    }
    
    func addToCart(_ book: Book) {
        cart.append(book)
    }
    
    func sortedListOfBooks(byType: SortType) -> [Book] {
        var sortMethod: (Book, Book) -> Bool
        
        switch byType {
        case .nameUp:
            sortMethod = { $0.title < $1.title }
        case .nameDown:
            sortMethod = { $0.title > $1.title }
        case .priceUp:
            sortMethod = { $0.price < $1.price }
        case .priceDown:
            sortMethod = { $0.price > $1.price }
        }
        
        return cart.sorted(by: sortMethod)
    }
    
    func totalPrice() -> Float {
        let price = cart.reduce(0) { $0 + $1.price }
        return Float(price) * (1 - discount)
    }
    
}


let library = Library()
library.addBook(
    Book(
        title: "Гарри Поттер и философский камень",
        author: "Дж.К. Роулинг",
        price: 1000,
        genre: .fiction
    )
)
library.addBook(
    Book(
        title: "Война и мир",
        author: "Лев Толстой",
        price: 850,
        genre: .novel
    )
)
library.addBook(
    Book(
        title: "Стихотворение",
        author: "Владимир Маяковский",
        price: 540,
        genre: .poems
    )
)

let booooks = [
    Book(
        title: "451 градус по Фаренгейту",
        author: "Рэй Брэдбери",
        price: 600,
        genre: .fiction
    ),
    Book(
        title: "Собачье сердце",
        author: "Михаил Булгаков",
        price: 600,
        genre: .scienceFiction
    )
    
]

let user = User(name: "Алиса", discount: 0.1)
let novelBooks = library.filterBooks(by: .novel)
user.addToCart(novelBooks)
let booksWithName = library.filterBooks(byName: "Гарри")
user.addToCart(booksWithName)

library.addCollectionBook(booooks)

user.addToCart(library.bookShelf)

print("Итоговая библеотека: \(library.bookShelf)\n")
print("Фантастика из библеотеки: \(library.filterBooks(by: .fiction))\n")
print("Итоговая корзина: \(user.sortedListOfBooks(byType: .priceUp))")
print("Цена корзины: \(user.totalPrice())")


