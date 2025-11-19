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

        const std::unordered_set<std::string>& getDesiredCities() const;
        std::pair<User*, std::string> getUserMatch() const; // Returns pair of pointer to User object and the city of the matched User
        User* getReverse() const;
        std::string getFirstName() const;
        std::string getLastName() const;
        std::string getName() const;
        std::string getEmail() const;
        std::string getHomeCity() const;
        int getId() const;

        void displayUserInfo() const;

        void addCity(const std::string& city);
        void setReverse(User* userPtr);
        void setMatch(const std::pair<User*, std::string>& p);
        void setName(const std::string& first, const std::string& last);
        void setEmail(const std::string& email);
        void setHomeCity(const std::string& city);
        void setId(const int& id);
        
        unsigned char isMatched() const; // Returns whether of not the User has been matched

        static void buildUserGraph(const std::vector<User*>& users);
        static void destroyUserGraph();

        static Graph* userGraph; // Keeps track of mapping Users to each other
        static int totalDesiredCities; // Keeps track of total number of cities being looked for across all Users

    protected:
        std::unordered_set<std::string> desiredCities_;
        std::pair<User*, std::string> matchedCity_;
        User* reverse_;
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

        void setUsers(const std::vector<User*>& users); // Create list of User pointers
        void buildGraph(); // Builds bipartite graph to match Users

        bool BFS();
        bool DFS(User* u);
        void maxMatching();

    protected:
        std::unordered_map<User*, std::vector<User*>> g_; // Stores which Users map to which other Users
        std::unordered_map<User*, User*> from_;
        std::unordered_map<User*, User*> to_;
        std::unordered_map<User*, int> dist_;
        std::vector<User*> users_;
        int maxMatching_;
};

#endif // USER_H