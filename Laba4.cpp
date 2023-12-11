
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

template <typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;
public:
    Pair(const T1& first, const T2& second) {
        this->first = first;
        this->second = second;
    }
};

class Book {
private:
    std::string name;
    std::string author;
    std::string genre;
public:
    Book(const std::string& name, const std::string& author, const std::string& genre) {
        this->name = name;
        this->author = author;
        this->genre = genre;
    }

    virtual void displayInfo() const {
        std::cout << "��������: " << name << " �����: " << author << " ����: " << genre << std::endl;
    }

    const std::string getBookName() const {
        return name;
    }

    const std::string getBookAuthor() const {
        return author;
    }

    const std::string getBookGenre() const {
        return genre;
    }

    static bool compareBookByName(const Book* book1, const Book* book2) {
        return book1->getBookName() < book2->getBookName();
    }

    static bool compareBookByAuthor(const Book* book1, const Book* book2) {
        return book1->getBookAuthor() < book2->getBookAuthor();
    }

    static bool compareBookByGenre(const Book* book1, const Book* book2) {
        return book1->getBookGenre() < book2->getBookGenre();
    }

    void saveToFile(std::ofstream& file) const {
        file << "��������: " << name << " �����: " << author << " ����: " << genre << std::endl;
    }
};

class Fiction : public Book {
private:
    std::string genre;
public:
    void displayInfo() const override {
        std::cout << "����: " << genre << std::endl;
    }
};
int main() {
    std::setlocale(LC_ALL, "rus");
    int choice;
    std::vector<Book*> library;
    do {
        std::cout << "����" << std::endl;
        std::cout << "0. ��������� ���������" << std::endl;
        std::cout << "1. �������� ����� ����� � ����������" << std::endl;
        std::cout << "2. ����� ����� � ����������" << std::endl;
        std::cout << "3. ������������� �����" << std::endl;
        std::cout << "4. ������� ������ � ������" << std::endl;
        std::cout << "5. �������� ����� � ����" << std::endl;
        std::cout << "�������� ��������: ";
        std::cin >> choice;
        switch (choice) {
        case 0: {
            std::cout << "��������� ���������" << std::endl;
            break;
        }
        case 1: {
            std::string name;
            std::string author;
            std::string genre;
            std::cout << "������� �������� �����: ";
            std::cin >> name;
            std::cout << "������� ������ �����: ";
            std::cin >> author;
            std::cout << "������� ���� �����: ";
            std::cin >> genre;
            library.push_back(new Book(name, author, genre));
            break;
        }
        case 2: {
            std::string foundName;
            std::string foundAuthor;
            std::string foundGenre;
            bool t = false;
            int choice;
            std::cout << "��� �� ������� ������ �����?" << std::endl;
            std::cout << "1. �� ��������" << std::endl;
            std::cout << "2. �� ������" << std::endl;
            std::cout << "3. �� �����" << std::endl;
            std::cout << "��� �����: ";
            std::cin >> choice;
            if (choice == 1) {
                std::cout << "������� �������� �����, ������� ������� �����: ";
                std::cin >> foundName;
                for (const auto& book : library) {
                    if (book->getBookName() == foundName) {
                        book->displayInfo();
                        t = true;
                    }
                    if (t == false) {
                        std::cout << "����� ���� �� ���� �������" << std::endl;
                    }
                }
            }
            if (choice == 2) {
                std::cout << "������� ������ �����, ������� ������� �����: ";
                std::cin >> foundAuthor;
                for (const auto& book : library) {
                    if (book->getBookAuthor() == foundAuthor) {
                        book->displayInfo();
                        t = true;
                    }
                    if (t == false) {
                        std::cout << "����� ���� �� �������" << std::endl;
                    }
                }
            }
            if (choice == 3) {
                std::cout << "������� ���� �����, ������� ������� �����: ";
                std::cin >> foundGenre;
                for (const auto& book : library) {
                    if (book->getBookGenre() == foundGenre) {
                        book->displayInfo();
                        t = true;
                    }
                    if (t == false) {
                        std::cout << "����� ���� �� ���� �������" << std::endl;
                    }
                }
            }
            if (choice < 1 or choice > 3) {
                std::cout << "������  ������ �������" << std::endl;
            }
            break;
        }
        case 3: {
            int choice;
            std::cout << "��� �� ������ ����������� �����?" << std::endl;
            std::cout << "1. �� ��������" << std::endl;
            std::cout << "2. �� ������" << std::endl;
            std::cout << "3. �� �����" << std::endl;
            std::cout << "��� �����: ";
            std::cin >> choice;
            if (choice == 1) {
                std::sort(library.begin(), library.end(), Book::compareBookByName);
                std::cout << "����� ����  ������������� �� ��������" << std::endl;
            }
            if (choice == 2) {
                std::sort(library.begin(), library.end(), Book::compareBookByAuthor);
                std::cout << "����� ���� ������������� �� ������" << std::endl;
            }
            if (choice == 3) {
                std::sort(library.begin(), library.end(), Book::compareBookByGenre);
                std::cout << "����� ���� ������������� �� �����" << std::endl;
            }
            if (choice < 1 or choice > 3) {
                std::cout << "������ ������ �������" << std::endl;
            }
            break;
        }
        case 4: {
            int i = 1;
            for (const auto* book : library) {
                std::cout << i << ". ";
                book->displayInfo();
                i++;
            }
            break;
        }
        case 5: {
            std::ofstream file("books.txt");
            if (file.is_open()) {
                for (const auto* book : library) {
                    book->saveToFile(file);
                }
                file.close();
            }
            else {
                std::cerr << "������ ��� �������� �����" << std::endl;
            }
            std::cout << "������ ��������� � ����" << std::endl;
            break;
        }
        }
    } while (choice != 0);
}