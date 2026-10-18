#include "user_session.hpp"

UserAccount::UserAccount(int id, const std::string& uname, const std::string& mail, const std::string& passHash)
    : userId(id), username(uname), email(mail), passwordHash(passHash), isLoggedIn(false) {
}

int UserAccount::getUserId() const {
    return userId;
}

std::string UserAccount::getUsername() const {
    return username;
}

std::string UserAccount::getEmail() const {
    return email;
}

std::string UserAccount::getPasswordHash() const {
    return passwordHash;
}

bool UserAccount::getIsLoggedIn() const {
    return isLoggedIn;
}

bool UserAccount::authenticate(const std::string& inputPasswordHash) {
    if (inputPasswordHash == passwordHash) {
        isLoggedIn = true;
        return true;
    }
    return false;
}

void UserAccount::logout() {
    isLoggedIn = false;
}

bool UserAccount::updateEmail(const std::string& newEmail) {
    if (!isLoggedIn) {
        return false;
    }
    if (newEmail.empty() || newEmail.find('@') == std::string::npos) {
        return false;
    }
    email = newEmail;
    return true;
}

std::string UserAccount::getProfileSummary() const {
    std::string statusStr = isLoggedIn ? "Logged In" : "Logged Out";
    return "ID: " + std::to_string(userId) + " | User: " + username + " | Email: " + email + " | Status: " + statusStr;
}
