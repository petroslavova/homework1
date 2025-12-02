#pragma once
#include <string>
#include <stdexcept>
#include <utility>

class Member {
    std::string name;
    std::string memberId;
    int yearJoined;

public:
    Member() : name(""), memberId(""), yearJoined(2023) {}

    Member(std::string n, std::string id, int y)
        : name(std::move(n)), memberId(std::move(id)), yearJoined(y) {
        if (memberId.empty()) 
            throw std::invalid_argument("Member ID cannot be empty");
        if (y < 2000 || y > 2025) 
            throw std::invalid_argument("Invalid year");
    }

    const std::string& getName() const { return name; }
    const std::string& getMemberId() const { return memberId; }
    int getYearJoined() const { return yearJoined; }

    void setName(const std::string& n) { name = n; }
    
    void setMemberId(const std::string& id) {
        if (id.empty()) 
            throw std::invalid_argument("Member ID cannot be empty");
        memberId = id;
    }
    
    void setYearJoined(int y) {
        if (y < 2000 || y > 2025) 
            throw std::invalid_argument("Year must be between 2000 and 2025");
        yearJoined = y;
    }

    std::string to_string() const {
        return name + " (ID: " + memberId + 
               ", Joined: " + std::to_string(yearJoined) + ")";
    }
};