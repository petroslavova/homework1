#pragma once
#include <string>
#include <stdexcept>
#include <utility>

class Loan {
    std::string isbn;
    std::string memberId;
    std::string startDate;
    std::string dueDate;
    bool returned;

public:
    Loan(std::string i, std::string mid, std::string start, std::string due)
        : isbn(std::move(i)), memberId(std::move(mid)), 
          startDate(std::move(start)), dueDate(std::move(due)), 
          returned(false) {
        if (isbn.empty() || memberId.empty() || 
            startDate.empty() || dueDate.empty()) {
            throw std::invalid_argument("All fields are required");
        }
        if (dueDate < startDate) {
            throw std::invalid_argument("Due date must be after start date");
        }
    }

    const std::string& getISBN() const { return isbn; }
    const std::string& getMemberId() const { return memberId; }
    const std::string& getStartDate() const { return startDate; }
    const std::string& getDueDate() const { return dueDate; }
    bool isReturned() const { return returned; }

    void markReturned() { returned = true; }

    bool isOverdue(const std::string& today) const {
        return !returned && today > dueDate;
    }

    std::string to_string() const {
        return "Loan: ISBN=" + isbn + ", Member=" + memberId + 
               ", " + startDate + " to " + dueDate + 
               ", Status: " + (returned ? "Returned" : "Active");
    }
};