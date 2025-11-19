#include "User.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

// USER START

Graph* User::userGraph = nullptr;

int User::totalDesiredCities = 0;

User::User() : desiredCities_({}), matchedCity_({nullptr, ""}), reverse_(nullptr), firstName_(""), lastName_(""), email_(""), homeCity_(""), id_(-1) {}

User::User(const std::unordered_set<std::string>& desiredCities, const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& homeCity, const int& id)
    : desiredCities_(desiredCities), matchedCity_({nullptr, ""}), reverse_(nullptr), firstName_(firstName), lastName_(lastName), email_(email), homeCity_(homeCity), id_(id) {}

const std::unordered_set<std::string>& User::getDesiredCities() const {
    return this->desiredCities_;
}

User* User::getReverse() const {
    return this->reverse_;
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

void User::displayUserInfo() const {
    const char c = '-';
    std::string sep = "";
    for (std::size_t i = 0; i < 100; ++i) {
        sep += c;
    }
    
    std::string info = '\n' + sep + "\nUser ID: " + std::to_string(this->id_) + '\n' + sep;
    info += ("\nName: " + this->getName() + '\n' + sep);
    info += ("\nEmail: " + this->getEmail() + '\n' + sep);
    info += ("\nHome City: " + this->getHomeCity() + '\n' + sep);
    info += "\nDesired Cities: ";
    for (auto it = this->desiredCities_.begin(); it != this->desiredCities_.end(); ++it) {
        auto next_it = std::next(it);
        info += *it;
        if (next_it != this->desiredCities_.end()) {
            info += ", ";
        } else {
            info += ('\n' + sep);
        }
    }
    info += ("\nMatched to reside with " + this->matchedCity_.first->getName() + "'s residence in " + this->matchedCity_.second + '\n' + sep);
    info += ("\nAllowing " + this->reverse_->getName() + " to reside in their " + this->getHomeCity() + " residence\n" + sep + '\n');

    std::cout << info;
}

void User::addCity(const std::string& city) {
    this->desiredCities_.insert(city);
}

void User::setReverse(User* userPtr) {
    this->reverse_ = userPtr;
}

void User::setMatch(const std::pair<User*, std::string>& p) {
    this->matchedCity_ = p;
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
    if (userGraph != nullptr) delete userGraph;
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

Graph::Graph() : g_({}), from_({}), to_({}), dist_({}), users_({}), maxMatching_(0) {}

Graph::Graph(const std::vector<User*>& users) : maxMatching_(0) {
    this->setUsers(users);
    this->buildGraph();
}

void Graph::setUsers(const std::vector<User*>& users) {
    this->users_ = users;
    for (User* user : this->users_) {
        this->from_[user] = nullptr;
        this->to_[user] = nullptr;
        this->dist_[user] = -1;
    }
}

void Graph::buildGraph() {
    for (std::size_t i = 0; i < this->users_.size(); ++i) {
        const std::unordered_set<std::string>& desiredCities = this->users_[i]->getDesiredCities();
        for (User* user : this->users_) {
            if (user == this->users_[i]) continue;
            if (desiredCities.find(user->getHomeCity()) != desiredCities.end()) {
                this->g_[this->users_[i]].push_back(user);
            }
        }
    }
    this->maxMatching();
}

bool Graph::BFS() {
    std::queue<User*> q;
    for (User* u : this->users_) {
        if (this->from_[u] == nullptr) {
            this->dist_[u] = 0;
            q.push(u);
        } else {
            this->dist_[u] = -1;
        }
    }

    bool found = false;
    while (!q.empty()) {
        User* u = q.front();
        q.pop();
        for (User* v : this->g_[u]) {
            User* w = this->to_[v];
            if (w == nullptr) {
                found = true;
            } else if (this->dist_[w] == -1) {
                this->dist_[w] = this->dist_[u] + 1;
                q.push(w);
            }
        }
    }

    return found;
}

bool Graph::DFS(User* u) {
    for (User* v : this->g_[u]) {
        User* w = this->to_[v];
        if (w == nullptr || (this->dist_[w] == this->dist_[u] + 1 && this->DFS(w))) {
            this->from_[u] = v;
            this->to_[v] = u;
            u->setMatch({v, v->getHomeCity()});
            v->setReverse(u);
            return true;
        }
    }
    this->dist_[u] = -1;

    return false;
}

void Graph::maxMatching() {
    int matching = 0;
    while (this->BFS()) {
        for (User* user : this->users_) {
            if (this->from_[user] == nullptr && this->DFS(user)) ++matching;
        }
    }
    std::cout << '\n' << matching << "/" << this->users_.size() << " Users Matched...\n";

    this->maxMatching_ = matching;
}

// END GRAPH