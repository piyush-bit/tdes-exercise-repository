#include "order_fulfillment.hpp"
#include <stdexcept>

// InsufficientStockException implementation
InsufficientStockException::InsufficientStockException(const std::string& item, int requested, int available)
    : item_(item), requested_(requested), available_(available), message_("") {
    (void)item_;
    (void)requested_;
    (void)available_;
    // TODO: Initialize message_ with format:
    // "Insufficient stock for item '<item>': requested <requested>, available <available>"
}

const char* InsufficientStockException::what() const noexcept {
    // TODO: Return message_.c_str()
    return "Insufficient stock exception";
}

std::string InsufficientStockException::getItem() const {
    // TODO: Return item_
    return "";
}

int InsufficientStockException::getRequested() const {
    // TODO: Return requested_
    return 0;
}

int InsufficientStockException::getAvailable() const {
    // TODO: Return available_
    return 0;
}

// PaymentFailedException implementation
PaymentFailedException::PaymentFailedException(const std::string& orderId, double amount, const std::string& reason)
    : orderId_(orderId), amount_(amount), reason_(reason), message_("") {
    (void)orderId_;
    (void)amount_;
    (void)reason_;
    // TODO: Initialize message_ with format:
    // "Payment failed for order <orderId> (Amount: <amount>): <reason>"
}

const char* PaymentFailedException::what() const noexcept {
    // TODO: Return message_.c_str()
    return "Payment failed exception";
}

std::string PaymentFailedException::getOrderId() const {
    // TODO: Return orderId_
    return "";
}

double PaymentFailedException::getAmount() const {
    // TODO: Return amount_
    return 0.0;
}

std::string PaymentFailedException::getReason() const {
    // TODO: Return reason_
    return "";
}

// OrderProcessor implementation
void OrderProcessor::processOrder(const Order& order) {
    (void)order;
    // TODO: Check order conditions and throw appropriate exceptions:
    // 1. If order.quantity > order.availableStock, throw InsufficientStockException
    // 2. If !order.paymentValid, throw PaymentFailedException
    // 3. If order.systemError, throw std::runtime_error("Database connection failed during order processing")
    // 4. If order.unknownError, throw 500
}

// executeOrderPipeline implementation
std::string executeOrderPipeline(const Order& order, OrderProcessor& processor) {
    (void)order;
    (void)processor;
    // TODO: Execute processor.processOrder(order) inside a try block.
    // Catch exceptions in order:
    // - InsufficientStockException -> return "STOCK_ERROR: " + e.what()
    // - PaymentFailedException      -> return "PAYMENT_ERROR: " + e.what()
    // - std::exception              -> return "STANDARD_ERROR: " + e.what()
    // - catch (...)                 -> return "UNKNOWN_ERROR: Handled by catch-all fallback handler"
    // On success: return "SUCCESS: Order " + order.orderId + " processed successfully"
    return "";
}
