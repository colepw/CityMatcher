#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <utility>
#include <unordered_set>
#include <unordered_map>

struct Graph;

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

        int getUserMatch(const int& id) const; // Returns the id of the matched User for User of input id number
        std::pair<unsigned char, std::string> isMatched(const int& id) const; // Returns whether of not the User of input id has been matched

        static int totalDesiredCities; // Keeps track of total number of cities being looked for across all Users
        static Graph userGraph; // Keeps track of mapping Users to each other

    protected:
        std::unordered_set<std::string> desiredCities_;
        std::pair<int, std::string> matchedCity_;
        std::string firstName_;
        std::string lastName_;
        std::string email_;
        std::string homeCity_;
        int id_;
};

struct Graph {
    public:
        Graph();
        Graph(const std::vector<User*>& users);
        void buildGraph(const std::vector<User*>& users); // Builds bipartite graph to match Users

    private:
        std::unordered_map<int, std::pair<int, std::string>> g; // Stores which User id maps to which other User id and city
};

#endif // USER_H