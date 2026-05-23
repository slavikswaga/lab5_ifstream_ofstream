#include <iostream>
#include <string>
#include <fstream>

struct Student
{
    std::string name;
    unsigned int age;
    double grade;
};

void write_func(){
    std::ofstream fout("students.txt", std::ios::app);
    if(!fout.is_open()){
        std::cout << "Failed opening file!" << std::endl;
        return;
    }
    int count_students = 0;
    std::cout << "Input the number of students to record their data in the file\n";
    std::cin >> count_students;
    for(int i = 0; i < count_students; i++){
        Student s;
        std::cout << "Input name of student\n";
        std::cin >> s.name;
        std::cout << "Input age of student\n";
        std::cin >> s.age;
        std::cout << "Input grade of student\n";
        std::cin >> s.grade;
        fout << s.name << " " << s.age << " " << s.grade << std::endl;
    }
    fout.close();
    return;
}

void read_func(){
    std::ifstream fin("students.txt");
    if(!fin.is_open()){
        std::cout << "File not found!" << std::endl;
        return;
    }
    Student s;
    std::cout << "Students:" << std::endl;
    while(fin >> s.name >> s.age >> s.grade){
        std::cout << s.name << " " << s.age << " " << s.grade << std::endl;
    }
    fin.close();
    return;
}

int main(int, char**){
    int choise = 0;
    std::cout << "Input command number:" << std::endl;
    std::cout << "1 - if you want write students\n";
    std::cout << "2 - if you want read info about all students\n";
    std::cout << "3 - if you want to write the data first and then read it\n";
    std::cin >> choise;
    switch (choise)
    {
    case 1:
        write_func();
        break;
    case 2:
        read_func();
        break;
    case 3:
        write_func();
        read_func();
        break;
    default:
        std::cout << "Unknown command\n";
        break;
    }
    return 0;
}
