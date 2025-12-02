#pragma once
#include <string>
#include <stdexcept>
#include <utility>

class Author {
    std::string name;
    int birthYear;

public:
    Author() : name("Unknown"), birthYear(1900) {}

    explicit Author(std::string n, int y = 1900) 
        : name(std::move(n)), birthYear(y) {
        if (y < 1850 || y > 2025) 
            throw std::invalid_argument("Invalid birth year");
    }

    const std::string& getName() const { return name; }
    int getBirthYear() const { return birthYear; }

    void setName(const std::string& n) { name = n; }
    void setBirthYear(int y) {
        if (y < 1850 || y > 2025)
            throw std::invalid_argument("Birth year must be between 1850 and 2025");
        birthYear = y;
    }

    std::string to_string() const {
        return name + " (" + std::to_string(birthYear) + ")";
    }
};