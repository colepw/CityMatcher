#include "User.h"
#include "utility.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>

int main() {
    std::string f;
    std::cin >> f;

    std::ifstream file(f);
    if (!file.is_open()) {
        std::cerr << "Could not open file...\n";
        return 1;
    }

    std::vector<User*> users;
    std::string line;

    while(std::getline(file, line)) {
        if (!line.empty() && line[0] == '#') continue;

        std::stringstream ss(line);
        std::string desiredCities, firstName, lastName, email, homeCity, id;

        std::getline(ss, desiredCities, ',');
        std::getline(ss, firstName, ',');
        std::getline(ss, lastName, ',');
        std::getline(ss, email, ',');
        std::getline(ss, homeCity, ',');
        std::getline(ss, id, ',');

        User* user = new User();
        
        user->setName(firstName, lastName);
        user->setEmail(email);
        user->setHomeCity(homeCity);
        user->setId(std::stoi(id));

        std::stringstream cs(desiredCities);
        std::string city;
        while (std::getline(cs, city, ';')) {
            if (!desiredCities.empty()) { user->addCity(city); ++(user->totalDesiredCities);
        }

        users.push_back(user);
    }

    file.close();

    
    if (!users.empty()) users[0]->destroyUserGraph();

    for (User* p : users) delete p;

    return 0;
}