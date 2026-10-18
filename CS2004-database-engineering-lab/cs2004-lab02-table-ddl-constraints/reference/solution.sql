-- Reference Solution for CS2004 Lab 02: Digital Wallet Table Schema & Constraints

CREATE TABLE user_wallets (
    wallet_id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    account_number TEXT UNIQUE NOT NULL,
    balance REAL DEFAULT 0.00,
    currency TEXT DEFAULT 'USD'
);
