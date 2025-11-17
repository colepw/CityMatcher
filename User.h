#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <unordered_set>

class User {
    public:
        User();
        User(const std::unordered_set<std::string>& desiredCities, const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& homeCity, const int& id);

        std::unordered_set<std::string> getDesiredCities() const;
        std::string getFirstName() const;
        std::string getLastName() const;
        std::string getName() const;
        std::string getEmail() const;
        std::string getHomeCity() const;
        int getId() const;

        void addCity(const std::string& city);
        void setName(const std::string& first, const std::string& last);
        void setEmail(const std::string& email);
        void setHomeCity(const std::string& city);
        void setId(const int& id);

    protected:
        std::unordered_set<std::string> desiredCities_;
        std::string firstName_;
        std::string lastName_;
        std::string email_;
        std::string homeCity_;
        int id_;
};

#endif // USER_H