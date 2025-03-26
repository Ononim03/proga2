#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// Константы
const int MAX_NAME_LEN = 50; // Максимальная длина ФИО
const int DATE_LEN = 11; // Длина даты рождения в формате dd.mm.yyyy + '\0'
const int MAX_BOOKS = 100; // Максимальное количество книг
const int MAX_AUTHOR_LEN = 100; // Максимальная длина имени автора
const int MAX_TITLE_LEN = 100; // Максимальная длина названия книги
const int MAX_FULLNAMES = 1000; // Максимальное количество ФИО

struct Applicant {
    char surname[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    char patronymic[MAX_NAME_LEN];
    char birthdate[DATE_LEN];
    int score1;
    int score2;
    int score3;
    int totalScore;
};

// Функция для чтения данных одного абитуриента из строки
void readApplicant(char *line, Applicant &applicant) {
    int pos = 0; // Текущая позиция в строке


    int i = 0;
    while (line[pos] != ' ') {
        applicant.surname[i++] = line[pos++];
    }
    applicant.surname[i] = '\0';
    pos++;


    i = 0;
    while (line[pos] != ' ') {
        applicant.name[i++] = line[pos++];
    }
    applicant.name[i] = '\0';
    pos++;


    i = 0;
    while (line[pos] != ' ') {
        applicant.patronymic[i++] = line[pos++];
    }
    applicant.patronymic[i] = '\0';
    pos++;


    i = 0;
    while (line[pos] != ' ') {
        applicant.birthdate[i++] = line[pos++];
    }
    applicant.birthdate[i] = '\0';
    pos++;


    applicant.score1 = 0;
    while (line[pos] >= '0' && line[pos] <= '9') {
        applicant.score1 = applicant.score1 * 10 + (line[pos++] - '0');
    }
    pos++;

    applicant.score2 = 0;
    while (line[pos] >= '0' && line[pos] <= '9') {
        applicant.score2 = applicant.score2 * 10 + (line[pos++] - '0');
    }
    pos++;

    applicant.score3 = 0;
    while (line[pos] >= '0' && line[pos] <= '9') {
        applicant.score3 = applicant.score3 * 10 + (line[pos++] - '0');
    }


    applicant.totalScore = applicant.score1 + applicant.score2 + applicant.score3;
}

// Функция для записи данных одного абитуриента в файл
void writeApplicant(ofstream &out, const Applicant &applicant) {
    out << applicant.surname << " " << applicant.name << " " << applicant.patronymic << " "
            << applicant.birthdate << " " << applicant.totalScore << endl;
}


// Функция сортировки массива абитуриентов
void sortApplicants(Applicant applicants[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (applicants[j].totalScore <= applicants[j + 1].totalScore) {
                swap(applicants[j], applicants[j + 1]);
            }
        }
    }
}

void task() {
    ifstream in("in.txt");
    ofstream out("out.txt");
    ofstream extraout("extraout.txt");

    if (!in || !out || !extraout) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }

    int n; // Количество мест
    cin >> n;

    Applicant applicants[1000];
    int count = 0;

    char line[500];
    while (in.getline(line, sizeof(line)) && count < 1000) {
        readApplicant(line, applicants[count]);
        count++;
    }

    sortApplicants(applicants, count);

    int lastAcceptedIndex = 0;
    for (int i = 0; i < n && i < count; ++i) {
        writeApplicant(out, applicants[i]);
        lastAcceptedIndex = i;
    }

    if (lastAcceptedIndex < count - 1 &&
        applicants[lastAcceptedIndex].totalScore == applicants[lastAcceptedIndex + 1].totalScore) {
        for (int i = lastAcceptedIndex + 1; i < count; ++i) {
            if (applicants[i].totalScore == applicants[lastAcceptedIndex].totalScore) {
                writeApplicant(extraout, applicants[i]);
            } else {
                break;
            }
        }
    }

    in.close();
    out.close();
    extraout.close();
}

void class1() {
}

int task1() {
    ifstream in("in1.txt");
    char line[500];
    in.getline(line, sizeof(line));
    int count = 0;
    int pos = 0;
    bool flag = false;
    while (line[pos] != '\0') {
        if (line[pos] == '.') break;
        if (line[pos] == ' ') {
            flag = false;
        } else if (!flag) {
            flag = true;
            count++;
        }
        pos++;
    }
    return count;
}

int task2() {
    ifstream in("in2.txt");
    char line[500];
    in.getline(line, sizeof(line));
    int count = 0;
    int pos = 0;
    bool flag = false;
    while (line[pos] != '\0') {
        if (line[pos] == ' ') {
            flag = false;
        } else if (!flag) {
            flag = true;
            if (line[pos] == 'b' || line[pos] == 'B') count++;
        }
        pos++;
    }
    return count;
}

void task3() {
    ifstream in("in3.txt");
    char line[500];
    in.getline(line, sizeof(line));
    int max_len = INT_MIN;
    int min_len = INT_MAX;
    int pos = 0;
    int cur_len = 0;
    bool flag = false;
    while (line[pos] != '\0') {
        if (flag && line[pos] == ' ') {
            flag = false;
            max_len = max(cur_len, max_len);
            min_len = min(cur_len, min_len);
            cur_len = 0;
        } else if (!flag && line[pos] != ' ') {
            flag = true;
            cur_len++;
        } else if (flag && line[pos] != ' ') {
            cur_len++;
        }
        pos++;
    }
    if (flag) {
        max_len = max(cur_len, max_len);
        min_len = min(cur_len, min_len);
    }
    cout << max_len << endl;
    cout << min_len << endl;
}

void task4() {
    ifstream in("in4.txt");
    char line[500];
    in.getline(line, sizeof(line));
    int pos = 0;
    bool flag = false;
    while (line[pos] != '\0') {
        if (line[pos] == ')') {
            break;
        }
        if (line[pos] == '(') {
            flag = true;
        } else if (flag) {
            cout << line[pos];
        }
        pos++;
    }
}
int task5() {
    ifstream in("in5.txt");
    char line[500];
    in.getline(line, sizeof(line));
    int pos = 0;
    int count = 0;
    while (line[pos + 2] != '\0') {
        if (line[pos] == 'a' && line[pos + 1] == 'b' && line[pos + 2] == 'c') {
            count++;
        }
        pos++;
    }
    return count;
}

struct Book {
    int code;
    char author[MAX_AUTHOR_LEN];
    char title[MAX_TITLE_LEN];
    int year;
    int shelf;
};

int readBooks(const char *filename, Book books[]) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Ошибка открытия файла!" << endl;
        return 0;
    }

    int count = 0;
    char line[500];

    while (inFile.getline(line, sizeof(line)) && count < MAX_BOOKS) {
        int pos = 0; // Текущая позиция в строке

        int i = 0;
        while (line[pos] != ' ') {
            books[count].code = books[count].code * 10 + (line[pos++] - '0');
        }
        pos++;


        i = 0;
        while (line[pos] != ' ') {
            books[count].author[i++] = line[pos++];
        }
        books[count].author[i] = '\0';
        pos++;


        i = 0;
        while (line[pos] != ' ') {
            books[count].title[i++] = line[pos++];
        }
        books[count].title[i] = '\0';
        pos++;

        books[count].year = 0;
        while (line[pos] != ' ') {
            books[count].year = books[count].year * 10 + (line[pos++] - '0');
        }
        pos++;

        books[count].shelf = 0;
        while (line[pos] >= '0' && line[pos] <= '9') {
            books[count].shelf = books[count].shelf * 10 + (line[pos++] - '0');
        }

        count++;
    }

    inFile.close();
    return count;
}

void findBookLocation(const Book books[], int count) {
    char author[MAX_AUTHOR_LEN];
    char title[MAX_TITLE_LEN];

    cout << "Введите автора: ";
    cin >> author;
    cout << "Введите название: ";
    cin >> title;

    bool found = false;
    for (int i = 0; i < count; ++i) {
        if (strcmp(books[i].author, author) == 0 && strcmp(books[i].title, title) == 0) {
            cout << "Местоположение книги: стеллаж №" << books[i].shelf << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Книга не найдена." << endl;
    }
}

void listBooksByAuthor(const Book books[], int count) {
    char author[MAX_AUTHOR_LEN];
    cout << "Введите автора: ";
    cin >> author;

    bool found = false;
    for (int i = 0; i < count; ++i) {
        if (strcmp(books[i].author, author) == 0) {
            cout << "Шифр: " << books[i].code
                    << ", Название: " << books[i].title
                    << ", Год издания: " << books[i].year
                    << ", Стеллаж: " << books[i].shelf << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Книги данного автора не найдены." << endl;
    }
}

void countBooksByYear(const Book books[], int count) {
    int year;
    cout << "Введите год издания: ";
    cin >> year;

    int bookCount = 0;
    for (int i = 0; i < count; ++i) {
        if (books[i].year == year) {
            bookCount++;
        }
    }

    cout << "Число книг издания " << year << " года: " << bookCount << endl;
}

void task_first() {
    Book books[MAX_BOOKS];
    int count = readBooks("books.txt", books);

    if (count == 0) {
        cerr << "Не удалось прочитать данные из файла." << endl;
        return;
    }

    int choice;
    do {
        cout << "\nВыберите действие:\n"
                << "1. Найти местоположение книги\n"
                << "2. Вывести список книг автора\n"
                << "3. Подсчитать число книг по году издания\n"
                << "0. Выход\n"
                << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
            case 1:
                findBookLocation(books, count);
                break;
            case 2:
                listBooksByAuthor(books, count);
                break;
            case 3:
                countBooksByYear(books, count);
                break;
            case 0:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while (choice != 0);
}

struct FullName {
    char surname[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    char patronymic[MAX_NAME_LEN];
};

int readFullNames(FullName fullNames[]) {
    ifstream inFile("fullnames.txt");
    if (!inFile) {
        cerr << "Ошибка открытия файла!" << endl;
        return 0;
    }

    int count = 0;
    char line[200];

    while (inFile.getline(line, sizeof(line)) && count < MAX_FULLNAMES) {
        int pos = 0;

        int i = 0;
        while (line[pos] != ' ') {
            fullNames[count].surname[i++] = line[pos++];
        }
        fullNames[count].surname[i] = '\0';
        pos++;

        i = 0;
        while (line[pos] != ' ') {
            fullNames[count].name[i++] = line[pos++];
        }
        fullNames[count].name[i] = '\0';
        pos++;

        i = 0;
        while (line[pos] != '\0') {
            fullNames[count].patronymic[i++] = line[pos++];
        }
        fullNames[count].patronymic[i] = '\0';

        count++;
    }

    inFile.close();
    return count;
}

void writeFullNames(const FullName fullNames[], int count) {
    ofstream outFile("outfullnames.txt");
    if (!outFile) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }

    for (int i = 0; i < count; ++i) {
        outFile << fullNames[i].surname << " "
                << fullNames[i].name << " "
                << fullNames[i].patronymic << endl;
    }

    outFile.close();
}

bool compareFullNames(const FullName &a, const FullName &b) {
    int cmpSurname = strcmp(a.surname, b.surname);
    if (cmpSurname != 0) {
        return cmpSurname < 0;
    }
    int cmpName = strcmp(a.name, b.name);
    if (cmpName != 0) {
        return cmpName < 0;
    }
    return strcmp(a.patronymic, b.patronymic) < 0;
}

void sortFullNames(FullName fullNames[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (!compareFullNames(fullNames[j], fullNames[j + 1])) {
                swap(fullNames[j], fullNames[j + 1]);
            }
        }
    }
}

void task_second() {
    FullName fullNames[MAX_FULLNAMES];
    int count = readFullNames(fullNames);

    if (count == 0) {
        cout << "Не удалось прочитать данные из файла." << endl;
        return;
    }

    // Сортировка списка ФИО
    sortFullNames(fullNames, count);

    // Запись отсортированного списка в файл
    writeFullNames(fullNames, count);
}

int main() {
    system("chcp 65001");
    cout << task5();
    return 0;
}
