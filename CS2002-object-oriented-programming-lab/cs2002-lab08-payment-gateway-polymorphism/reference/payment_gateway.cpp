#include "payment_gateway.hpp"
#include <algorithm>

// ---------------------------------------------------------------------------
// PaymentProcessor Implementation
// ---------------------------------------------------------------------------
PaymentProcessor::PaymentProcessor(const std::string& name)
    : gatewayName(name), totalVolumeProcessed(0.0), successfulTransactions(0), failedTransactions(0) {}

std::string PaymentProcessor::getGatewayName() const {
    return gatewayName;
}

double PaymentProcessor::getTotalVolumeProcessed() const {
    return totalVolumeProcessed;
}

int PaymentProcessor::getSuccessfulTransactions() const {
    return successfulTransactions;
}

int PaymentProcessor::getFailedTransactions() const {
    return failedTransactions;
}

// ---------------------------------------------------------------------------
// StripeProcessor Implementation
// ---------------------------------------------------------------------------
StripeProcessor::StripeProcessor(const std::string& key)
    : PaymentProcessor("Stripe"), apiKey(key) {}

std::string StripeProcessor::getApiKey() const {
    return apiKey;
}

double StripeProcessor::calculateFee(double amount) const {
    if (amount <= 0.0 || apiKey.empty()) {
        return 0.0;
    }
    return (amount * 0.029) + 0.30;
}

bool StripeProcessor::processPayment(double amount) {
    if (amount <= 0.0 || apiKey.empty()) {
        failedTransactions++;
        return false;
    }
    successfulTransactions++;
    totalVolumeProcessed += amount;
    return true;
}

// ---------------------------------------------------------------------------
// PayPalProcessor Implementation
// ---------------------------------------------------------------------------
PayPalProcessor::PayPalProcessor(const std::string& email)
    : PaymentProcessor("PayPal"), accountEmail(email) {}

std::string PayPalProcessor::getAccountEmail() const {
    return accountEmail;
}

double PayPalProcessor::calculateFee(double amount) const {
    if (amount <= 0.0 || amount > 10000.0 || accountEmail.empty() || accountEmail.find('@') == std::string::npos) {
        return 0.0;
    }
    return (amount * 0.0349) + 0.49;
}

bool PayPalProcessor::processPayment(double amount) {
    if (amount <= 0.0 || amount > 10000.0 || accountEmail.empty() || accountEmail.find('@') == std::string::npos) {
        failedTransactions++;
        return false;
    }
    successfulTransactions++;
    totalVolumeProcessed += amount;
    return true;
}

// ---------------------------------------------------------------------------
// CryptoProcessor Implementation
// ---------------------------------------------------------------------------
CryptoProcessor::CryptoProcessor(const std::string& wallet)
    : PaymentProcessor("Crypto"), walletAddress(wallet) {}

std::string CryptoProcessor::getWalletAddress() const {
    return walletAddress;
}

static bool isValidCryptoWallet(const std::string& wallet) {
    return (wallet.rfind("0x", 0) == 0) && (wallet.length() >= 10);
}

double CryptoProcessor::calculateFee(double amount) const {
    if (amount < 5.0 || !isValidCryptoWallet(walletAddress)) {
        return 0.0;
    }
    return 1.50;
}

bool CryptoProcessor::processPayment(double amount) {
    if (amount < 5.0 || !isValidCryptoWallet(walletAddress)) {
        failedTransactions++;
        return false;
    }
    successfulTransactions++;
    totalVolumeProcessed += amount;
    return true;
}

// ---------------------------------------------------------------------------
// PaymentGatewayEngine Implementation
// ---------------------------------------------------------------------------
void PaymentGatewayEngine::registerProcessor(PaymentProcessor* processor) {
    if (processor != nullptr) {
        processors.push_back(processor);
    }
}

int PaymentGatewayEngine::processBatch(double amount) {
    int successCount = 0;
    for (auto* processor : processors) {
        if (processor != nullptr && processor->processPayment(amount)) {
            successCount++;
        }
    }
    return successCount;
}

double PaymentGatewayEngine::calculateTotalFees(double amount) const {
    double totalFees = 0.0;
    for (const auto* processor : processors) {
        if (processor != nullptr) {
            totalFees += processor->calculateFee(amount);
        }
    }
    return totalFees;
}

size_t PaymentGatewayEngine::getProcessorCount() const {
    return processors.size();
}

void PaymentGatewayEngine::clearProcessors() {
    processors.clear();
}
