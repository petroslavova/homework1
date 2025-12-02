#include <iostream>
#include "Library.h"
using namespace std;

int main() {
    
    Library lib("Градска библиотека");
    
    try {

        Author vazov("Иван Вазов", 1850);
        Author konstantinov("Алеко Константинов", 1863);
        Author pelin("Елин Пелин", 1877);
        

        Book b1("Под игото", vazov, 1894, 25.50, "ISBN-001");
        Book b2("Нема земя", vazov, 1900, 18.90, "ISBN-002");
        Book b3("Бай Ганьо", konstantinov, 1895, 22.00, "ISBN-003");
        Book b4("Гераците", pelin, 1911, 15.75, "ISBN-004");
        
        lib.addBook(b1);
        lib.addBook(b2);
        lib.addBook(b3);
        lib.addBook(b4);
        
        cout << "Книги добавени: " << Book::getTotalBooks() << "\n\n";
        
        lib.addMember(Member("Петър Петров", "M001", 2023));
        lib.addMember(Member("Мария Иванова", "M002", 2024));
        lib.addMember(Member("Георги Георгиев", "M003", 2023));
        
        cout << lib.to_string() << "\n\n";
        
        cout << "Демонстрация на Rule of 5 \n";
        {
            Book temp = b1;            
            Book moved = std::move(temp); 
            
            Book assigned;
            assigned = b2;              
            assigned = std::move(moved); 
        }
        cout << "Брой книги след Rule of 5 демо: " << Book::getTotalBooks() << "\n\n";
        
        cout << "Заемане на книги\n";
        if (lib.loanBook("ISBN-001", "M001", "2025-11-01", "2025-11-15")) {
            cout << "Успешно заемане: ISBN-001\n";
        }
        
        cout << "Налична ли е ISBN-001? " << boolalpha << lib.isBookAvailable("ISBN-001") << "\n";
        
       if (!lib.loanBook("ISBN-001", "M002", "2025-11-02", "2025-11-16")) {
            cout << "Книгата вече е заета!\n";
        }
        
        lib.loanBook("ISBN-003", "M002", "2025-11-01", "2025-11-20");
        lib.loanBook("ISBN-004", "M001", "2025-11-03", "2025-11-17");
        
        cout << "\n" << lib.to_string() << "\n\n";
        
        cout << "Връщане на книга\n";
        if (lib.returnBook("ISBN-001", "M001")) {
            cout << "Книгата е върната успешно\n";
        }
        
        cout << "Налична ли е ISBN-001 сега? " << lib.isBookAvailable("ISBN-001") << "\n\n";
        
        cout << "Търсене по автор\n";
        auto results = lib.findByAuthor("Вазов");
        for (const auto& book : results) {
            cout << "• " << book.to_string() << "\n";
        }
        cout << "\n";
        
        cout << "Тест на валидация\n";
        try {
            Book invalid("", vazov, 1700, -10, "");
        } catch (const exception& e) {
            cout << "Грешка: " << e.what() << "\n";
        }
        
    } catch (const exception& e) {
        cerr << "Грешка: " << e.what() << "\n";
    }
    
    return 0;
}