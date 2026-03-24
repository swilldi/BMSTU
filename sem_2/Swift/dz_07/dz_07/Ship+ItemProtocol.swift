//
//  Ships.swift
//  dz_07
//
//  Created by Dmitriy Dudyrev on 04.04.2025.
//

protocol ItemProtocol {
    var title: String { get }
    var company: String { get }
    var prise: Int { get }
    var formatPrise: String { get }
}


protocol ItemCompany {
    var company: String { get }
}


enum ShipCompany: String {
    case aegis = "Aegis Dynamics"
    case anvil = "Anvil Aerospace"
    case rsi = "Roberts Space Industries"
}


enum Ships: Int {
    case raven = 0, andromeda, f8c, galaxy, carrack

    var title: String {
        switch self {
        case .andromeda:
            "andromeda"
        case .f8c:
            "f8c"
        case .galaxy:
            "galaxy"
        case .raven:
            "raven"
        case .carrack:
            "carrack"
        }
    }
    
    var company: String {
        switch self {
        case .andromeda, .galaxy:
            "Roberts Space Industries"
        case .raven:
            "Aegis Dynamics"
        case .f8c, .carrack:
            "Anvil Aerospace"
        }
    }
    
    var prise: Int {
        switch self {
        case .andromeda:
            1000000
        case .galaxy, .carrack:
            3000000
        case .raven:
            400000
        case .f8c:
            1000000
        }
    }
}

struct Item: ItemProtocol {
    
    let type: Ships
    
    var title: String
    var company: String
    var prise: Int
    
    
    var formatPrise: String {
        var strPrise = ""
        var prise = String(prise)
        while !prise.isEmpty {
            strPrise = prise.suffix(3) + strPrise
            prise = String(prise.dropLast(3))
            if !prise.isEmpty {
                strPrise = " " + strPrise
            }
        }
        return strPrise + " UEC"
    }
    
    init(_ type: Ships)
    {
        self.type = type
        title = type.title
        company = type.company
        prise = type.prise
    }
}

