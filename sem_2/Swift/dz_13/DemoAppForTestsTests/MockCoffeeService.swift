//
//  CoffeeService.swift
//  DemoAppForTests
//
//  Created by Dmitriy Toropkin on 05.05.2025.
//

import Foundation
@testable import DemoAppForTests

// MARK: - Errors

enum CoffeeError: Error {
    case invalidOrderId
    case orderAlreadyCancelled
}

// MARK: - Service

final class MockCoffeeService {
    
    // In-memory storage for mock data
    var availableCoffees: [Coffee] = []
    var orders: [Order] = []
    var nextOrderId = 1000
    
    init() {
        // Prepare mock coffee data
        availableCoffees = [
            Coffee(id: 1, name: "Espresso", price: 2.5, imageURL: "espresso"),
            Coffee(id: 2, name: "Cappuccino", price: 3.5, imageURL: "cappuccino"),
        ]
    }
    
    // Simulates fetching available coffees
    func fetchCoffees() -> [Coffee] {
        return availableCoffees
    }
    
    // Places a new coffee order
    func placeOrder(
        coffeeId: Int,
        quantity: Int,
        customerName: String
    ) -> Order {
        let orderId = nextOrderId
        nextOrderId += 1
        
        let newOrder = Order(
            id: orderId,
            coffeeId: coffeeId,
            quantity: quantity,
            customerName: customerName,
            status: .pending,
            createdAt: Date()
        )
        
        orders.append(newOrder)
        return newOrder
    }
    
    // Gets the status of an existing order
    func getOrderStatus(orderId: Int) throws -> Order {
        if let order = orders.first(where: { $0.id == orderId }) {
            return order
        } else {
            throw CoffeeError.invalidOrderId
        }
    }
    
    // Cancels an existing order
    func cancelOrder(orderId: Int) throws -> Bool {
        if let index = orders.firstIndex(where: { $0.id == orderId }) {
            let order = orders[index]
            
            if order.status == .cancelled {
               throw CoffeeError.orderAlreadyCancelled
            }
            
            let cancelledOrder = Order(
                id: order.id,
                coffeeId: order.coffeeId,
                quantity: order.quantity,
                customerName: order.customerName,
                status: .cancelled,
                createdAt: order.createdAt
            )
            
            orders[index] = cancelledOrder
            return true
        } else {
            throw CoffeeError.invalidOrderId
        }
    }
}
