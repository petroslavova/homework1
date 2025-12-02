#pragma once
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include "Book.h"
#include "Member.h"
#include "Loan.h"

class Library {
    std::string name;
    std::vector<Book> books;
    std::vector<Member> members;
    std::vector<Loan> loans;

public:
    Library(std::string n = "City Library") : name(std::move(n)) {}

    void addBook(const Book& b) { 
        if (hasBook(b.getISBN()))
            throw std::invalid_argument("Book with this ISBN already exists");
        books.push_back(b); 
    }
    
    void addMember(const Member& m) { 
        if (isMemberRegistered(m.getMemberId()))
            throw std::invalid_argument("Member with this ID already exists");
        members.push_back(m); 
    }

    bool hasBook(const std::string& isbn) const {
        return std::any_of(books.begin(), books.end(),
            [&](const Book& b) { return b.getISBN() == isbn; });
    }

    bool isBookAvailable(const std::string& isbn) const {
        if (!hasBook(isbn)) return false;
        
        return std::none_of(loans.begin(), loans.end(),
            [&](const Loan& l) { 
                return l.getISBN() == isbn && !l.isReturned(); 
            });
    }

    bool isMemberRegistered(const std::string& memberId) const {
        return std::any_of(members.begin(), members.end(),
            [&](const Member& m) { return m.getMemberId() == memberId; });
    }

    bool loanBook(const std::string& isbn, const std::string& memberId,
                  const std::string& start, const std::string& due) {
        if (!hasBook(isbn) || !isMemberRegistered(memberId) || 
            !isBookAvailable(isbn)) {
            return false;
        }
        
        try {
            loans.emplace_back(isbn, memberId, start, due);
            return true;
        } catch (const std::exception&) {
            return false;
        }
    }

    bool returnBook(const std::string& isbn, const std::string& memberId) {
        for (auto& loan : loans) {
            if (loan.getISBN() == isbn && 
                loan.getMemberId() == memberId && 
                !loan.isReturned()) {
                loan.markReturned();
                return true;
            }
        }
        return false;
    }

    std::vector<Book> findByAuthor(const std::string& authorName) const {
        std::vector<Book> result;
        for (const auto& book : books) {
            if (book.getAuthor().getName().find(authorName) != std::string::npos) {
                result.push_back(book);
            }
        }
        return result;
    }

    std::string to_string() const {
        int activeLoans = 0;
        for (const auto& loan : loans) {
            if (!loan.isReturned()) ++activeLoans;
        }
        
        return name + "\n" +
               "Total Books: " + std::to_string(books.size()) + "\n" +
               "Total Members: " + std::to_string(members.size()) + "\n" +
               "Active Loans: " + std::to_string(activeLoans) + "\n" +
               "Available Books: " + std::to_string(books.size() - activeLoans);
    }
};