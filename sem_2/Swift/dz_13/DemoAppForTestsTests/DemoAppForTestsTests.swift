//
//  DemoAppForTestsTests.swift
//  DemoAppForTestsTests
//
//  Created by Dmitriy Toropkin on 05.05.2025.
//

import XCTest
@testable import DemoAppForTests

final class DemoAppForTestsTests: XCTestCase {
    
    private var sut: MockCoffeeService!
    
    override func setUpWithError() throws {
        // Put setup code here. This method is called before the invocation of each test method in the class.
        try super.setUpWithError()
        
        sut = MockCoffeeService()
    }

    override func tearDownWithError() throws {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        sut = nil
        
        try super.tearDownWithError()
    }

    func test_fetchCoffees() {
        
    }
    
    func test_placeOrder() {
        // given
        let coffeId = 1
        let quantity = 5
        let name = "Name"

        // where
        let lastOrderId = sut.nextOrderId
        let order = sut.placeOrder(coffeeId: coffeId, quantity: quantity, customerName: name)
        
        // then
        XCTAssertEqual(sut.nextOrderId - lastOrderId, 1)
        XCTAssertNotEqual(sut.orders.count, 0)
        
        XCTAssertEqual(order.coffeeId, coffeId)
        XCTAssertEqual(order.quantity, quantity)
        XCTAssertEqual(order.customerName, name)
    }
    
    func test_cancelOrder_postivie() {
        // given
        let order = Order(id: 1, coffeeId: 1, quantity: 1, customerName: "name", status: .pending, createdAt: .now)
        sut.orders = [order]

        // where
        var res: Bool?
        XCTAssertNoThrow(
            res = try sut.cancelOrder(orderId: 1)
        )
        
        // then
        XCTAssertTrue(res ?? false)
    
    }
    
    func test_cancelOrder_invalidId() {
        // given
        let order = Order(id: 1, coffeeId: 1, quantity: 1, customerName: "name", status: .pending, createdAt: .now)
        sut.orders = [order]

        // where & then
        XCTAssertThrowsError(try sut.cancelOrder(orderId: 5)) { error in
                XCTAssertEqual(error as? CoffeeError, CoffeeError.invalidOrderId)
            }
    }
    
    func test_cancelOrder_AlreadyCanceled() {
        // given
        let order = Order(id: 1, coffeeId: 1, quantity: 1, customerName: "name", status: .cancelled, createdAt: .now)
        sut.orders = [order]

        // where & then
//        do {
//            try sut.cancelOrder(orderId: 1)
//        } catch {
//            print("123")
//        }
        XCTAssertThrowsError(try sut.cancelOrder(orderId: 1)) { error in
                XCTAssertEqual(error as? CoffeeError, CoffeeError.orderAlreadyCancelled)
            }
    
    }
    
    func test_getOrderStatus_positive() {
        let order = Order(id: 1, coffeeId: 1, quantity: 1, customerName: "name", status: .cancelled, createdAt: .now)
        sut.orders = [order]

        // where
        var orderRes: Order?
        XCTAssertNoThrow(
            orderRes = try sut.getOrderStatus(orderId: 1)
        )
        
        // then
        XCTAssertNotNil(orderRes)

    }
    
    func test_getOrderStatus_invalidId() {
        let order = Order(id: 1, coffeeId: 1, quantity: 1, customerName: "name", status: .cancelled, createdAt: .now)
        sut.orders = [order]

        // where & then
        XCTAssertThrowsError(try sut.getOrderStatus(orderId: 10)) { error in
            XCTAssertEqual(error as? CoffeeError, CoffeeError.invalidOrderId)
        }
    }

}
