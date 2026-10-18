# CS2002 Lab 01: E-Commerce User Session Manager

## Overview

In modern e-commerce web services, managing user identity, security credentials, and active session states is a critical software engineering requirement. This lab focuses on implementing the `UserAccount` class in C++, which handles user authentication, session state management, email updates, and profile summary generation.

---

## Objectives

- Understand object-oriented state management in C++.
- Enforce encapsulation by maintaining private member variables.
- Implement robust validation for authentication and profile modification.
- Handle state transitions (`isLoggedIn` flags) securely across public interface methods.

---

## Class Specification: `UserAccount`

The `UserAccount` class declaration is provided in `user_session.hpp`. You must implement the member functions in `user_session.cpp`.

### Private Members

- `int userId`: Unique numerical identifier for the user account.
- `std::string username`: User's display name.
- `std::string email`: User's registered email address.
- `std::string passwordHash`: Securely stored password hash.
- `bool isLoggedIn`: Boolean flag tracking current session authentication state (initialized to `false`).

### Public Methods

#### `UserAccount(int id, const std::string& uname, const std::string& mail, const std::string& passHash)`
Constructs a user account object initializing `userId`, `username`, `email`, and `passwordHash`. Sets initial session state `isLoggedIn` to `false`.

#### `int getUserId() const`
Returns the numerical user ID.

#### `std::string getUsername() const`
Returns the user's username.

#### `std::string getEmail() const`
Returns the user's current email address.

#### `std::string getPasswordHash() const`
Returns the user's password hash.

#### `bool getIsLoggedIn() const`
Returns `true` if the session is currently logged in, `false` otherwise.

#### `bool authenticate(const std::string& inputPasswordHash)`
Verifies `inputPasswordHash` against stored `passwordHash`:
- If `inputPasswordHash` matches `passwordHash`, updates `isLoggedIn = true` and returns `true`.
- If passwords do not match, leaves `isLoggedIn` unchanged and returns `false`.

#### `void logout()`
Terminates the current session by setting `isLoggedIn = false`.

#### `bool updateEmail(const std::string& newEmail)`
Updates the user's email address under the following conditions:
- User MUST be logged in (`isLoggedIn == true`).
- `newEmail` MUST NOT be empty.
- `newEmail` MUST contain the `@` character.
- If all conditions are met, updates `email` and returns `true`.
- Otherwise, returns `false` without modifying `email`.

#### `std::string getProfileSummary() const`
Generates and returns a formatted profile summary string:
```text
"ID: <userId> | User: <username> | Email: <email> | Status: <Logged In / Logged Out>"
```
Example: `"ID: 101 | User: alice | Email: alice@example.com | Status: Logged Out"`

---

## Development & Testing

### Commands

Run the public test suite locally:
```bash
make test-public
```
or using the wrapper script:
```bash
./run public
```

To clean build artifacts:
```bash
make clean
```
