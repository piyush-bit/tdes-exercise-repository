#ifndef USER_SESSION_HPP
#define USER_SESSION_HPP

#include <string>

class UserAccount {
private:
    int userId;
    std::string username;
    std::string email;
    std::string passwordHash;
    bool isLoggedIn;

public:
    UserAccount(int id, const std::string& uname, const std::string& mail, const std::string& passHash);

    // Getters
    int getUserId() const;
    std::string getUsername() const;
    std::string getEmail() const;
    std::string getPasswordHash() const;
    bool getIsLoggedIn() const;

    // Core session and profile management methods
    bool authenticate(const std::string& inputPasswordHash);
    void logout();
    bool updateEmail(const std::string& newEmail);
    std::string getProfileSummary() const;
};

#endif // USER_SESSION_HPP
