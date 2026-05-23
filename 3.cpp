#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

struct Sale{
    std::string date_of_sale;
    unsigned int num_of_buyer;
    double sum;
    std::string product_category;
};

Sale pullSale(const std::string& line, Sale& s){
        std::stringstream ss(line);
        std::getline(ss, s.date_of_sale, ',');
        ss >> s.num_of_buyer;
        ss.ignore();
        ss >> s.sum;
        ss.ignore();
        std::getline(ss, s.product_category);
    return s;
}

void printSale(const Sale& s){
    std::cout << s.date_of_sale << " - " << s.num_of_buyer << " - " << s.sum << " - " << s.product_category << std::endl;
    return;
}

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
    std::string file = "";
    std::cout << "Input the file you want to read" << std::endl;
    std::cout << "=====================" << std::endl;
    std::cout << "sales.csv" << std::endl;
    std::cout << "filtered_sales.csv" << std::endl;
    std::cout << "=====================" << std::endl;
    std::cin >> file;
    std::ifstream fin(file);
    if(!fin.is_open()){
        std::cout << "File not found!" << std::endl;
        return;
    }
    std::string line;
    while(std::getline(fin, line)){
        Sale s;
        pullSale(line, s);
        printSale(s);
    }
    fin.close();
    return;
}

void calculate_total_sum(){
    double total_sum = 0;
    std::ifstream fin("sales.csv");
    if(!fin.is_open()){
        std::cout << "File not found!" << std::endl;
        return;
    }
    std::string line;
    while(std::getline(fin, line)){
        Sale s;
        pullSale(line, s);
        total_sum += s.sum;
    }
    fin.close();
    std::cout << "total sales amount = " << total_sum << std::endl;
    return;
}

void write_filtered_sales(){
    std::string necessary_date = "";
    std::cout << "Input necessary date for filtering sales\n";
    std::cout << "format - 'dd.mm.yyyy'\n";
    std::cin >> necessary_date;
    std::vector<Sale> filtered;
    std::ofstream fout("filtered_sales.csv", std::ios::app);
    std::ifstream fin("sales.csv");
    if(!fin.is_open()){
        std::cout << "File not found!" << std::endl;
        return;
    }
    if(!fout.is_open()){
        std::cout << "Failed opening file!" << std::endl;
        return;
    }
    std::string line;
    
    while(std::getline(fin, line)){
        Sale s;
        pullSale(line, s);
        if(s.date_of_sale == necessary_date){
            filtered.push_back(s);
        }
    }
    for(int i = 0; i < filtered.size(); i++){
        printSale(filtered[i]);
    }
    fout.close();
    fin.close();
    return;
}

int main(){
    int choise = 0;
    std::cout << "Input command number:" << std::endl;
    std::cout << "1 - if you want write sales\n";
    std::cout << "2 - if you want read info about sales\n";
    std::cout << "3 - if you want to write the data first and then read it\n";
    std::cout << "4 - if you want to filter sales for date\n";
    std::cout << "5 - if you want to print the total cost of all sales\n";
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
    case 4:
        write_filtered_sales();
        read_func();
        break;
    case 5:
        calculate_total_sum();
        break;
    default:
        std::cout << "Unknown command\n";
        break;
    }
    return 0;
}