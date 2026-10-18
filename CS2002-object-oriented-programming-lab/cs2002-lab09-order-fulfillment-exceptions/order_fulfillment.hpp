#ifndef ORDER_FULFILLMENT_HPP
#define ORDER_FULFILLMENT_HPP

#include <exception>
#include <string>

// Order representation in the fulfillment pipeline
struct Order {
    std::string orderId;
    std::string item;
    int quantity;
    int availableStock;
    double amount;
    bool paymentValid;
    bool systemError;   // Triggers std::runtime_error
    bool unknownError;  // Triggers raw non-std exception
};

// Custom Exception for inventory stock issues inheriting from std::exception
class InsufficientStockException : public std::exception {
private:
    std::string item_;
    int requested_;
    int available_;
    std::string message_;

public:
    InsufficientStockException(const std::string& item, int requested, int available);
    const char* what() const noexcept override;
    std::string getItem() const;
    int getRequested() const;
    int getAvailable() const;
};

// Custom Exception for payment issues inheriting from std::exception
class PaymentFailedException : public std::exception {
private:
    std::string orderId_;
    double amount_;
    std::string reason_;
    std::string message_;

public:
    PaymentFailedException(const std::string& orderId, double amount, const std::string& reason);
    const char* what() const noexcept override;
    std::string getOrderId() const;
    double getAmount() const;
    std::string getReason() const;
};

// Order Processor Class
class OrderProcessor {
public:
    void processOrder(const Order& order);
};

// Pipeline function executing processOrder with try-catch and catch(...) handlers
std::string executeOrderPipeline(const Order& order, OrderProcessor& processor);

#endif // ORDER_FULFILLMENT_HPP
