#include "order_fulfillment.hpp"
#include <stdexcept>
#include <sstream>

// InsufficientStockException implementation
InsufficientStockException::InsufficientStockException(const std::string& item, int requested, int available)
    : item_(item), requested_(requested), available_(available) {
    message_ = "Insufficient stock for item '" + item_ + "': requested " +
               std::to_string(requested_) + ", available " + std::to_string(available_);
}

const char* InsufficientStockException::what() const noexcept {
    return message_.c_str();
}

std::string InsufficientStockException::getItem() const {
    return item_;
}

int InsufficientStockException::getRequested() const {
    return requested_;
}

int InsufficientStockException::getAvailable() const {
    return available_;
}

// PaymentFailedException implementation
PaymentFailedException::PaymentFailedException(const std::string& orderId, double amount, const std::string& reason)
    : orderId_(orderId), amount_(amount), reason_(reason) {
    std::ostringstream ss;
    ss << "Payment failed for order " << orderId_ << " (Amount: " << amount_ << "): " << reason_;
    message_ = ss.str();
}

const char* PaymentFailedException::what() const noexcept {
    return message_.c_str();
}

std::string PaymentFailedException::getOrderId() const {
    return orderId_;
}

double PaymentFailedException::getAmount() const {
    return amount_;
}

std::string PaymentFailedException::getReason() const {
    return reason_;
}

// OrderProcessor implementation
void OrderProcessor::processOrder(const Order& order) {
    if (order.quantity > order.availableStock) {
        throw InsufficientStockException(order.item, order.quantity, order.availableStock);
    }
    if (!order.paymentValid) {
        throw PaymentFailedException(order.orderId, order.amount, "Payment authorization failed");
    }
    if (order.systemError) {
        throw std::runtime_error("Database connection failed during order processing");
    }
    if (order.unknownError) {
        throw 500;
    }
}

// executeOrderPipeline implementation
std::string executeOrderPipeline(const Order& order, OrderProcessor& processor) {
    try {
        processor.processOrder(order);
        return "SUCCESS: Order " + order.orderId + " processed successfully";
    } catch (const InsufficientStockException& e) {
        return std::string("STOCK_ERROR: ") + e.what();
    } catch (const PaymentFailedException& e) {
        return std::string("PAYMENT_ERROR: ") + e.what();
    } catch (const std::exception& e) {
        return std::string("STANDARD_ERROR: ") + e.what();
    } catch (...) {
        return "UNKNOWN_ERROR: Handled by catch-all fallback handler";
    }
}
