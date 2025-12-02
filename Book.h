#pragma once
#include <string>
#include <stdexcept>
#include <utility>
#include "Author.h"

class Book {
    std::string title;
    Author author;
    int year;
    double price;
    std::string isbn;
    static int totalBooks;

public:
    Book() : title(""), year(1900), price(0.0), isbn("") { 
        ++totalBooks; 
    }

    Book(std::string t, Author a, int y, double p, std::string i)
        : title(std::move(t)), author(std::move(a)), year(y), price(p), isbn(i) {
        if (y < 1800 || y > 2025) 
            throw std::invalid_argument("Invalid publication year");
        if (p < 0) 
            throw std::invalid_argument("Price cannot be negative");
        if (i.empty())
            throw std::invalid_argument("ISBN cannot be empty");
        ++totalBooks;
    }

    // Rule of 5
    ~Book() { --totalBooks; }
    
    Book(const Book& other) 
        : title(other.title), author(other.author), year(other.year),
          price(other.price), isbn(other.isbn) { 
        ++totalBooks; 
    }
    
    Book(Book&& other) noexcept 
        : title(std::move(other.title)), author(std::move(other.author)),
          year(other.year), price(other.price), isbn(std::move(other.isbn)) {
        ++totalBooks;
        other.year = 0;
        other.price = 0.0;
    }
    
    Book& operator=(const Book& other) {
        if (this != &other) {
            title = other.title;
            author = other.author;
            year = other.year;
            price = other.price;
            isbn = other.isbn;
        }
        return *this;
    }
    
    Book& operator=(Book&& other) noexcept {
        if (this != &other) {
            title = std::move(other.title);
            author = std::move(other.author);
            year = other.year;
            price = other.price;
            isbn = std::move(other.isbn);
            
            other.year = 0;
            other.price = 0.0;
        }
        return *this;
    }

    // Getters
    const std::string& getTitle() const { return title; }
    const Author& getAuthor() const { return author; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    const std::string& getISBN() const { return isbn; }

    // Setters with validation
    void setTitle(const std::string& t) { title = t; }
    void setAuthor(const Author& a) { author = a; }
    
    void setYear(int y) {
        if (y < 1800 || y > 2025)
            throw std::invalid_argument("Year must be between 1800 and 2025");
        year = y;
    }
    
    void setPrice(double p) {
        if (p < 0) 
            throw std::invalid_argument("Price cannot be negative");
        price = p;
    }
    
    void setISBN(const std::string& i) {
        if (i.empty()) 
            throw std::invalid_argument("ISBN cannot be empty");
        isbn = i;
    }

    std::string to_string() const {
        return "\"" + title + "\" by " + author.to_string() + 
               " (" + std::to_string(year) + "), " +
               "ISBN: " + isbn + ", $" + std::to_string(price);
    }

    static int getTotalBooks() { return totalBooks; }
};

// Initialize static member
inline int Book::totalBooks = 0;