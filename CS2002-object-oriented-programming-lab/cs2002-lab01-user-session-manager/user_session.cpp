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
    // TODO: Compare inputPasswordHash with stored passwordHash.
    // If equal, set isLoggedIn = true and return true.
    // Otherwise, return false.
    (void)inputPasswordHash;
    return false;
}

void UserAccount::logout() {
    // TODO: Set isLoggedIn = false to terminate the user session.
}

bool UserAccount::updateEmail(const std::string& newEmail) {
    // TODO: Update email to newEmail ONLY IF user is logged in (isLoggedIn == true),
    // newEmail is non-empty, and newEmail contains an '@' character.
    // Return true on success, false otherwise.
    (void)newEmail;
    return false;
}

std::string UserAccount::getProfileSummary() const {
    // TODO: Return summary string formatted as:
    // "ID: <userId> | User: <username> | Email: <email> | Status: <Logged In / Logged Out>"
    return "";
}
