#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

class Student { //класс Student
private:

    std::string name_;
    std::string date_;
    std::string class_;
    double averageScore_;

public:
    Student();
    Student(const std::string& name,
            const std::string& date,
            const std::string& classStudent,
            const double averageScore);

    std::string getName();
    std::string getDate();
    std::string getClass();
    double getAverageScore();
    void setName(std::string name);
    void setDate(std::string date);
    void setClass(std::string newClass);
    void setAverageScore(double averageScore);
    bool isCorrect();
    friend std::ostream& operator<<(std::ostream& stream, const Student& student);

    friend std::istream& operator>>(std::istream& stream, Student& student);
};

//Реализация методов класса

Student::Student() {
    name_ = "";
    date_ = "";
    class_ = "";
    averageScore_ = 0.0;
}

Student::Student(const std::string &name, const std::string &date, const std::string &classStudent,
                 const double averageScore) {
    if(this->isCorrect()) {
        name_ = name;
        date_ = date;
        class_ = classStudent;
        averageScore_ = averageScore;
    }
}

std::string Student::getName() {
    return name_;
}

std::string Student::getDate() {
    return date_;
}

std::string Student::getClass() {
    return class_;
}

double Student::getAverageScore() {
    return averageScore_;
}

void Student::setName(std::string name) {
    name_ = name;
}

void Student::setDate(std::string date) {
    date_ = date;
}

void Student::setClass(std::string newClass) {
    class_ = newClass;
}

void Student::setAverageScore(double averageScore) {
    averageScore_ = averageScore;
}



bool Student::isCorrect() {
    if(name_ == "" || date_.size() < 10 || class_ == "" || averageScore_ < 0) {
        std::cout << "\nIncorrect input!\n";
        std::cin.ignore();
        return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& stream, const Student& student) {
    stream
            <<"\nName of student: " << student.name_
            <<"\nDate of birth: " << student.date_
            <<"\nClass: " << student.class_
            <<"\nAverage score: " << student.averageScore_ << std::endl;
    return stream;
}

std::istream& operator>>(std::istream& stream, Student& student) {
    std::string name,date,classS;
    double averageS;

    std::cout << "\nEnter Student Data.\n";
    std::cout << "\nName of student: ";
    std::getline(stream,name);
    student.setName(name);
    std::cout << "Date of birth(YYYY/MM/DD): ";
    stream >> date;
    student.setDate(date);
    std::cout << "Class: ";
    stream >> classS;
    student.setClass(classS);
    std::cout << "Average score: ";
    stream >> averageS;
    student.setAverageScore(averageS);
    return stream;
}

static std::vector<Student> students;//динамический массив для хранения объектов класса

//функции
void addStudent();
void deleteStudent();
void sortStudent();
void searchStudent();
void editStudent();
void listStudent();
void showAll();
bool emptyList();

//реализация функций
void practice() {
    int ch;
    do {
        system("clear");
        std::cout << "\nStudents\n\n"
                  << "1. Add Student\n"
                  << "2. Delete Student\n"
                  << "3. Sort Student\n"
                  << "4. Search Student\n"
                  << "5. Edit Student\n"
                  << "6. List of Student in the class who have an average score below 3\n"
                  << "7. Show list all Students\n"
                  << "0. Exit\n"
                  << "Enter your choose: ";
        std::cin >> ch;
        std::cin.ignore();
        system("clear");

        switch (ch) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                sortStudent();
                break;
            case 4:
                searchStudent();
                break;
            case 5:
                editStudent();
                break;
            case 6:
                listStudent();
                break;
            case 7:
                showAll();
                break;
        }
    } while(ch);
}

void addStudent() {
    Student student;
    std::cin >> student;
    std::cin.ignore();
    if(student.isCorrect()) {
        students.emplace_back(student);
        std::cout << "\nStudent added!\n";
    }
    std::cin.ignore();
}
void deleteStudent() {
    if(emptyList()) {
        return;
    }

    std::string name;

    for(auto it : students) {
        std::cout << it;
    }
    std::cout << "Enter name of student: ";
    std::getline(std::cin,name);

    for(int i = 0; i < students.size(); i++) {
        if(students[i].getName() == name) {
            students.erase(students.begin() + i);
            std::cout << "\nStudent deleted!\n";
            std::cin.ignore();
            return;
        }
    }
    std::cout << "\nStudent not founded!\n";
    std::cin.ignore();
}
void sortStudent() {
    if(emptyList()) {
        return;
    }

    std::string param;
    std::cout << "\nEnter param for sorting: ";
    std::getline(std::cin,param);

    if(param == "Name of student") {
        std::sort(students.begin(),students.end(),[](Student f, Student s) {//по возрастанию
            return f.getName() < s.getName();
        });
    } else if(param == "Date of birth") {
        std::sort(students.begin(),students.end(),[](Student f, Student s) {//по возрастанию
            return f.getDate() < s.getDate();
        });
    } else if(param == "Class") {
        std::sort(students.begin(),students.end(),[](Student f, Student s) {//по возрастанию
            return f.getClass() < s.getClass();
        });
    } else if(param == "Average score") {
        std::sort(students.begin(),students.end(),[](Student f, Student s) {//по убыванию
            return f.getAverageScore() > s.getAverageScore();
        });
    } else {
        std::cout << "\nParam not founded!\n";
        std::cin.ignore();
        return;
    }

    std::cout << "\nStudent sorted!\n";
    std::cin.ignore();

}
void searchStudent() {
    if(emptyList()) {
        return;
    }

    std::string param, temp;
    int coutNF = 0;
    std::cout << "\nEnter param for searching: ";
    std::getline(std::cin,param);

    if(param == "Name of student") {
        std::cout << "\nEnter name for searching: ";
        std::getline(std::cin,temp);
        std::cin.ignore();
        
        for(auto it : students) {
            if(it.getName() == temp) {
                std::cout << it;
            } else {
                coutNF++;
            }
        }
        
        
    } else if(param == "Date of birth") {
        std::cout << "\nEnter date of birth for searching: ";
        std::cin >> temp;
        std::cin.ignore();
        
        for(auto it : students) {
            if(it.getDate() == temp) {
                std::cout << it;
            } else {
                coutNF++;
            }
        }
        
        
    } else if(param == "Class") {
        std::cout << "\nEnter class for searching: ";
        std::cin >> temp;
        std::cin.ignore();
        
        for(auto it : students) {
            if(it.getClass() == temp) {
                std::cout << it;
            } else {
                coutNF++;
            }
        }
        
    } else if(param == "Average score") {
        double newAS;
        std::cout << "\nEnter average score for searching: ";
        std::cin >> newAS;
        std::cin.ignore();

        for(auto it : students) {
            if(it.getAverageScore() == newAS) {
                std::cout << it;
            } else {
                coutNF++;
            }
        }
        
    } else {
        std::cout << "\nParam not founded!\n";
        std::cin.ignore();
        return;
    }
    
    if(coutNF == students.size()) {
        std::cout << "\nStudent not founded!\n";
    }
    std::cin.ignore();
}
void editStudent() {
    if(emptyList()) {
        return;
    }

    showAll();
    std::string name;
    std::cout << "\nEnter name of student: ";
    std::getline(std::cin,name);
    for(int i = 0; i < students.size(); i++) {
        if(students[i].getName() == name) {
            std::string param, temp;
            std::cout << "\nEnter param for editing: ";
            std::getline(std::cin,param);
            
            if(param == "Name of student") {
                std::cout << "Enter new name: ";
                std::getline(std::cin,temp);
                std::cin.ignore();
                students[i].setName(temp);
            } else if(param == "Date of birth") {
                std::cout << "Enter new date of birth: ";
                std::cin >> temp;
                std::cin.ignore();
                students[i].setDate(temp);
            } else if(param == "Class") {
                std::cout << "Enter new class: ";
                std::cin >> temp;
                std::cin.ignore();
                students[i].setClass(temp);
            } else if(param == "Average score") {
                double newAS;
                std::cout << "Enter new average score: ";
                std::cin >> newAS;
                std::cin.ignore();
                students[i].setAverageScore(newAS);
            } else {
                std::cout << "\nParam not founded!\n";
                std::cin.ignore();
                return;
            }
            std::cout << "\nStudent edited!\n";
            std::cin.ignore();
            return;
        }
    }
    std::cout << "\nStudent not founded!\n";
    std::cin.ignore();
}
void listStudent() {
    if(emptyList()) {
        return;
    }

    std::vector<Student> list;
    for(int i = 0; i < students.size(); i++) {
        if(students[i].getAverageScore() < 3.0) {
            list.emplace_back(students[i]);
        }
    }

    if(!(list.empty())) {
        std::cout << "\nList of Student in the class who have an average score below 3\n";
        for(auto it : list) {
            std::cout << it;
        }
    } else {
        std::cout << "\nStudent not founded!\n";
    }
    std::cin.ignore();
}

void showAll() {
    if(emptyList()) {
        return;
    }
    std::cout << "\nAll students\n";
    for(auto it : students) {
        std::cout << it;
    }
    std::cin.ignore();
}

bool emptyList() {
    if(students.empty()) {
         std::cout << "\nThe list of Students is empty!\n";
         std::cin.ignore();
         return true;
    }
    return false;
}
int main() {
    practice();
    return 0;
}


