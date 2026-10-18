#ifndef PAYMENT_GATEWAY_HPP
#define PAYMENT_GATEWAY_HPP

#include <string>
#include <vector>
#include <iostream>
#include <memory>

// Abstract Base Class representing a generic Payment Processor
class PaymentProcessor {
protected:
    std::string gatewayName;
    double totalVolumeProcessed;
    int successfulTransactions;
    int failedTransactions;

public:
    explicit PaymentProcessor(const std::string& name);
    virtual ~PaymentProcessor() = default;

    // Pure virtual methods ensuring polymorphic interface
    virtual bool processPayment(double amount) = 0;
    virtual double calculateFee(double amount) const = 0;

    // Common query methods
    std::string getGatewayName() const;
    double getTotalVolumeProcessed() const;
    int getSuccessfulTransactions() const;
    int getFailedTransactions() const;
};

// Derived Class: Stripe Payment Processor
class StripeProcessor : public PaymentProcessor {
private:
    std::string apiKey;

public:
    explicit StripeProcessor(const std::string& key);
    ~StripeProcessor() override = default;

    bool processPayment(double amount) override;
    double calculateFee(double amount) const override;
    std::string getApiKey() const;
};

// Derived Class: PayPal Payment Processor
class PayPalProcessor : public PaymentProcessor {
private:
    std::string accountEmail;

public:
    explicit PayPalProcessor(const std::string& email);
    ~PayPalProcessor() override = default;

    bool processPayment(double amount) override;
    double calculateFee(double amount) const override;
    std::string getAccountEmail() const;
};

// Derived Class: Crypto Payment Processor
class CryptoProcessor : public PaymentProcessor {
private:
    std::string walletAddress;

public:
    explicit CryptoProcessor(const std::string& wallet);
    ~CryptoProcessor() override = default;

    bool processPayment(double amount) override;
    double calculateFee(double amount) const override;
    std::string getWalletAddress() const;
};

// Payment Engine for batch processing registered gateway instances via polymorphism
class PaymentGatewayEngine {
private:
    std::vector<PaymentProcessor*> processors;

public:
    PaymentGatewayEngine() = default;
    ~PaymentGatewayEngine() = default;

    void registerProcessor(PaymentProcessor* processor);
    int processBatch(double amount);
    double calculateTotalFees(double amount) const;
    size_t getProcessorCount() const;
    void clearProcessors();
};

#endif // PAYMENT_GATEWAY_HPP
