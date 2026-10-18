#ifndef DIVIDE_CONQUER_APPS_HPP
#define DIVIDE_CONQUER_APPS_HPP

#include <string>
#include <vector>
#include <cstdint>

/**
 * @brief Represents a single executed financial trade record.
 */
struct Trade {
    uint64_t trade_id;   // Unique trade identifier
    uint64_t timestamp;  // Execution timestamp (in milliseconds since epoch)
    double price;        // Execution price per share/unit
    uint32_t quantity;   // Volume / number of shares traded
    std::string symbol;  // Ticker symbol (e.g., "AAPL", "NVDA")

    bool operator==(const Trade& other) const {
        return trade_id == other.trade_id &&
               timestamp == other.timestamp &&
               price == other.price &&
               quantity == other.quantity &&
               symbol == other.symbol;
    }
};

/**
 * @brief Sorts a vector of trades in-place using Quick Sort (Divide & Conquer).
 * 
 * Primary sort key: timestamp (ascending).
 * Secondary sort key: trade_id (ascending).
 * 
 * @param trades Vector of Trade objects to sort in-place.
 */
void rank_sort_trades(std::vector<Trade>& trades);

/**
 * @brief Merges two pre-sorted trade streams into a single sorted stream using Merge Sort merge logic.
 * 
 * Both streamA and streamB are assumed to be sorted by timestamp (and trade_id).
 * 
 * @param streamA First sorted vector of trades.
 * @param streamB Second sorted vector of trades.
 * @return std::vector<Trade> Merged vector of trades sorted by timestamp (and trade_id).
 */
std::vector<Trade> merge_trade_streams(const std::vector<Trade>& streamA, const std::vector<Trade>& streamB);

/**
 * @brief Finds the 0-based index of the first trade with price >= target_price using Binary Search (Divide & Conquer).
 * 
 * The vector sorted_trades must be pre-sorted in ascending order of price.
 * 
 * @param sorted_trades Vector of trades sorted by price ascending.
 * @param target_price Minimum target price threshold.
 * @return int Index of first trade matching price >= target_price, or -1 if none exists or vector is empty.
 */
int find_price_threshold(const std::vector<Trade>& sorted_trades, double target_price);

#endif // DIVIDE_CONQUER_APPS_HPP
