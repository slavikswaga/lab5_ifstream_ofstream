#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct Sale{
    std::string date_of_sale;
    unsigned int num_of_buyer;
    double sum;
    std::string product_category;
};

void write_func(){
    std::ofstream fout("sales.csv", std::ios::app);
    if(!fout.is_open()){
        std::cout << "Failed opening file!" << std::endl;
        return;
    }
    int count_sales = 0;
    std::cout << "Input the number of sales to record data in the file\n";
    std::cin >> count_sales;
    for(int i = 0; i < count_sales; i++){
        Sale s;
        std::cout << "Input date of sale\n";
        std::cin >> s.date_of_sale;
        std::cout << "Input num of buyer\n";
        std::cin >> s.num_of_buyer;
        std::cout << "Input sum of sale\n";
        std::cin >> s.sum;
        std::cout << "Input product_category of sale\n";
        std::cin >> s.product_category;
        fout << s.date_of_sale << "," << s.num_of_buyer << "," << s.sum << "," << s.product_category << std::endl;
    }
    fout.close();
    return;
}

void read_func(){
    std::ifstream fin("sales.csv");
    std::string line;
    while(std::getline(fin, line)){
        std::stringstream ss(line);
        Sale s;
        std::getline(ss, s.date_of_sale, ',');
        ss >> s.num_of_buyer;
        ss.ignore();
        ss >> s.sum;
        ss.ignore();
        std::getline(ss, s.product_category);
        std::cout << s.date_of_sale << " - " << s.num_of_buyer << " - " << s.sum << " - " << s.product_category << std::endl;
    }
    fin.close();
    return;
}

double calculate_total_sum(){
    double total_sum = 0;
    std::ifstream fin("sales.csv");
    std::string line;
    while(std::getline(fin, line)){
        std::stringstream ss(line);
        Sale s;
        std::getline(ss, s.date_of_sale, ',');
        ss >> s.num_of_buyer;
        ss.ignore();
        ss >> s.sum;
        ss.ignore();
        std::getline(ss, s.product_category);
        total_sum += s.sum;
    }
    fin.close();
    return total_sum;
}
int main(){

    read_func();
    return 0;
}