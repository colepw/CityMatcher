#include "User.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

int User::totalDesiredCities = 0;

User::User() {}

User::User(const std::unordered_set<std::string>& desiredCities, const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& homeCity, const int& id)
    : desiredCities_(desiredCities), firstName_(firstName), lastName_(lastName), email_(email), homeCity_(homeCity), id_(id) {}

std::unordered_set<std::string> User::getDesiredCities() const {
    return this->desiredCities_;
}

std::string User::getFirstName() const {
    return this->firstName_;
}

std::string User::getLastName() const {
    return this->lastName_;
}

std::string User::getName() const {
    std::string name = this->firstName_ + " " + this->lastName_;
    return name;
}

std::string User::getEmail() const {
    return this->email_;
}

std::string User::getHomeCity() const {
    return this->homeCity_;
}

int User::getId() const {
    return this->id_;
}

void User::addCity(const std::string& city) {
    this->desiredCities_.insert(city);
}

void User::setName(const std::string& first, const std::string& last) {
    this->firstName_ = first;
    this->lastName_ = last;
}

void User::setEmail(const std::string& email) {
    this->email_ = email;
}

void User::setHomeCity(const std::string& city) {
    this->homeCity_ = city;
}

void User::setId(const int& id) {
    this->id_ = id;
}