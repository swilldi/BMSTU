// Протокол, чтобы экземпляр мог лечиться
protocol Healable {
    var health: Int { get set }
    func heal(amount: Int)
}


// Протокол, чтобы экземпляр мог летать
protocol Flyable {
    var flightSpeed: Int { get set }
    func fly()
}

// Протолок, для предметов
protocol Item {
    var label: String { get }
    var type: ItemType { get }
    var action: (GameCharacter) -> () { get }
    func use(to character: GameCharacter)
}


enum ItemType: Equatable {
    enum PotionSize: Int {
        case small = 20
        case medium = 40
        case large = 80
    }
    
    case heal(value: PotionSize)
    case levelUp
    
    static func == (lhs: ItemType, rhs: ItemType) -> Bool {
        lhs.label == rhs.label
    }
    
    var label: String {
        switch self {
        case .heal(let value):
            "Зелье лечения \(value.rawValue) HP"
        case .levelUp:
            "Зелье повышения уровня"
        }
    }
}


class Potion: Item, CustomStringConvertible {
    
    let type: ItemType
    var label: String
    let action: (GameCharacter) -> Void
    
    init(type: ItemType) {
        self.type = type
        self.label = type.label
        self.action = {
            switch type {
            case .heal(let value):
                $0.heal(amount: value.rawValue)
            case .levelUp:
                $0.levelUp()
            }
        }
        
    }
    
    func use(to character: GameCharacter) {
        action(character)
    }
    
    var description: String { label }
    
}


class Inventory: CustomStringConvertible {
    var items = [Item]()
    
    var description: String { return "\(items)"}
    
    func add(_ item: Item) {
        items.append(item)
    }
    
    func get(_ type: ItemType) -> Item? {
        // Ищем элемент с нужным типо
        // Если его нет возвращаем nil
        for (i, item) in items.enumerated() {
            if item.type == type {
                return items.remove(at: i)
            }
        }
        return nil
    }

}


class GameCharacter: Healable {
    // начальные значения характиристик
    let defaultHealth = 100
    let defaultLevel = 1
    
    // коэффициенты повышение характиристик
    let healthCoefficient = 10
    
    // объявляем поля класса
    let name: String
    var maxHealth: Int
    var health: Int
    var level: Int
    var inventory = Inventory()
    
    
    init(name: String, health: Int, level: Int) {
        self.name = name
        self.level = level <= 0 ? defaultLevel : level
        maxHealth = (health <= 0 ? defaultHealth : health) + healthCoefficient * (self.level - defaultLevel)
        self.health = maxHealth
    }
    
    // получение урона
    func takeDamage(amount damage: Int) {
        health -= damage
        if health < 0 {
            health = 0
        }
    }
    
    // востановление здоровья
    func heal(amount points: Int) {
        health += points
        if health > maxHealth {
            health = maxHealth
        }
    }
    
    // повышение уровня и характеристик
    func levelUp() {
        level += 1
        maxHealth += healthCoefficient
        health = maxHealth
    }
    
    func takeItem(item: Item) {
        inventory.add(item)
    }
    
    func use(item type: ItemType) {
        if let item = inventory.get(type) {
            item.use(to: self)
        }
    }
}


// Добавляем раширение для класса GameCharacter
extension GameCharacter {
    var isAlive: Bool { health > 0}
}

extension GameCharacter {
    func printCharacterInfo(_ paramenters: [String] = []) {
        print(
        """
        Name: \(name)
        Level: \(level)
        Health: \(health) / \(maxHealth)\(paramenters.isEmpty ? "" : "\n" + paramenters.joined(separator: "\n"))
        Inventory: \(inventory)
        """
        )
    }
}


class Warrior: GameCharacter {
    // начальные значения характиристик
    let defaultArmor = 2
    let defaultPower = 10
    
    // коэффициенты повышение характиристик
    let armorCoefficient = 1
    let powerCoefficient = 1
    
    // объявляем поля класса
    var power: Int
    var armor: Int
    
    
    init(name: String, health: Int, armor: Int, power: Int, level: Int) {
        self.armor = armor <= 0 ? defaultArmor : armor
        self.power = power <= 0 ? defaultPower : power
        super.init(name: name, health: health, level: level)
        
        // повышение характеристик в соответсвии с уровнем персонажа
        self.armor += armorCoefficient * (level - defaultLevel) / 2
        self.power += powerCoefficient * (level - defaultLevel)
    }
    
    // атака другого экземпляра класса GameCharacter
    func attack(target: GameCharacter) {
        target.takeDamage(amount: power)
    }
    
    // получение уроная с учетом брони
    override func takeDamage(amount damage: Int) {
        if damage > armor {
            super.takeDamage(amount: damage - armor)
        }
    }
    
    // повышение уровня и характеристик
    override func levelUp() {
        super.levelUp()
        power += powerCoefficient
        if level % 2 != 0 {
            armor += armorCoefficient
        }
    }
}


class Mage: GameCharacter, Flyable {
    // начальные значения характиристик
    let defaultPhysicPower = 5
    let defaultMagicPower = 10
    
    // коэффициенты повышение характиристик
    let physicPowerCoefficient = 1
    let magicPowerCoefficient = 1
    
    // объявляем поля класса
    var magicPower: Int
    var physicPower: Int
    var flightSpeed = 10
    
    init(name: String, health: Int, magicPower: Int, physicPower: Int, level: Int) {
        self.magicPower = magicPower <= 0 ? magicPower : defaultMagicPower
        self.physicPower = physicPower <= 0 ? physicPower : defaultPhysicPower
        super.init(name: name, health: health, level: level)
        
        self.magicPower += magicPowerCoefficient * (level - defaultLevel)
        self.physicPower += physicPowerCoefficient * (level - defaultLevel)
    }
    
    // атака другого экземпляра класса GameCharacter
    func attack(target: GameCharacter) {
        target.takeDamage(amount: physicPower)
    }
    
    // усиленная атака другого экземпляра класса GameCharacter
    func magicAttack(target: GameCharacter) {
        target.takeDamage(amount: physicPower + magicPower)
    }
    
    func fly() {
        print("I can fly \(flightSpeed) m/h")
    }
    
    // повышение уровня и характеристик
    override func levelUp() {
        super.levelUp()
        magicPower += magicPowerCoefficient
        if level % 2 != 0 {
            physicPower += physicPowerCoefficient
        }
    }
}



// Тестирование GameCharacter
let smallHeal = Potion(type: .heal(value: .small))
let levelUp = Potion(type: .levelUp)


// Лечение с помощью зелья
print("--Провека взаимодействия персонажа с инвенатрем--")
var player_1 = GameCharacter(name: "player_1", health: 100, level: 1)
player_1.printCharacterInfo()
player_1.takeDamage(amount: 40)
print(player_1.health)
print(player_1.inventory)
player_1.takeItem(item: smallHeal)
player_1.takeItem(item: smallHeal)
print(player_1.inventory)
player_1.use(item: .heal(value: .small))
print(player_1.health)
print("\(player_1.inventory)")

// Повышение уровня с помощью зелья
print("\n--Проверка влияния уровня персонажа--")
var player_2 = GameCharacter(name: "player_2", health: 100, level: 1)
player_2.printCharacterInfo()
player_2.takeItem(item: levelUp)
print(player_2.inventory)
player_2.use(item: .levelUp)
player_2.printCharacterInfo()

// Персонаж с не нулевым уровнем
print("\n--Персонаж с не первым уровнем--")
let player_3 = GameCharacter(name: "player_3", health: 100, level: 4)
player_3.printCharacterInfo()
print()

let warrior_1 = Warrior(name: "warrior_1", health: 150, armor: 5, power: 10, level: 3)
warrior_1.printCharacterInfo(["Armor: \(warrior_1.armor)", "Power: \(warrior_1.power)"])
print()

var mage_1 = Mage(name: "mage_1", health: 70, magicPower: 10, physicPower: 5, level: 10)
mage_1.printCharacterInfo(["Magic power: \(mage_1.magicPower)", "Physic power: \(mage_1.physicPower)"])
print()

mage_1.levelUp()
mage_1.printCharacterInfo(["Magic power: \(mage_1.magicPower)", "Physic power: \(mage_1.physicPower)"])

// Уникальные методы дочерних классов
print("\n--Атака и уникальные методы классов--")
let warrior_2 = Warrior(name: "warroir_2", health: 100, armor: 5, power: 10, level: 1)
print("Воин – Health: \(warrior_2.health) HP | Power: \(warrior_2.power) | Armor: \(warrior_2.armor)")
let mage_2 = Mage(name: "mage_2", health: 100, magicPower: 10, physicPower: 3, level: 1)
print("Маг – Health: \(warrior_2.health) HP | Physic power: \(mage_2.physicPower) | Magic power: \(mage_2.magicPower)")

print("\nАтака воина")
warrior_2.attack(target: mage_2)
print("Воин атакует мага\n10 урон воина\n0 защита мага")
print("Воин – Health: \(warrior_2.health)")


print("\nАтака мага")
print("Маг атакует воина магией:\n5 + 10 урон мага\n5 защита воина")
mage_2.magicAttack(target: warrior_2)
print("Воин – Health: \(warrior_2.health)")

print("\nПолет мага")
mage_2.fly()



