#include "User.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

// USER START

Graph* User::userGraph = nullptr;

int User::totalDesiredCities = 0;

User::User() : desiredCities_({}), firstName_(""), lastName_(""), email_(""), homeCity_(""), id_(-1), matchedCity_({nullptr, ""}) {}

User::User(const std::unordered_set<std::string>& desiredCities, const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& homeCity, const int& id)
    : desiredCities_(desiredCities), firstName_(firstName), lastName_(lastName), email_(email), homeCity_(homeCity), id_(id), matchedCity_({nullptr, ""}) {}

const std::unordered_set<std::string>& User::getDesiredCities() const {
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

void User::buildUserGraph(const std::vector<User*>& users) {
    delete userGraph;
    userGraph = new Graph(users);
}

void User::destroyUserGraph() {
    if (userGraph != nullptr) {
        delete userGraph;
        userGraph = nullptr;
    }
}

std::pair<User*, std::string> User::getUserMatch() const {
    return this->matchedCity_;
}

unsigned char User::isMatched() const {
    return (this->matchedCity_.first != nullptr && this->matchedCity_.second != "");
}

// END USER

// GRAPH START

int Graph::numMatching = 0;

Graph::Graph() : g_({}), users_({}) {}

Graph::Graph(const std::vector<User*>& users) {
    this->setUsers(users);
    this->buildGraph();
}

void Graph::setUsers(const std::vector<User*>& users) {
    this->users_ = users;
}

void Graph::buildGraph() {
    for (std::size_t i = 0; i < this->users_.size(); ++i) {
        std::unordered_set<std::string> desiredCities = this->users_[i]->getDesiredCities();
        for (User* user : this->users_) {
            if (user == this->users_[i]) continue;
            if (desiredCities.find(user->getHomeCity()) != desiredCities.end()) {
                this->g_[this->users_[i]].push_back(user);
            }
        }
    }
}

// END GRAPH