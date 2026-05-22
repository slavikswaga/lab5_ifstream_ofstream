#include <iostream>
#include <string>
#include <fstream>


struct Product
{
    unsigned int code;
    char name[50];
    double price;
    unsigned int count;
};

void write_func(){
    std::ofstream fout("products.bin", std::ios::binary | std::ios::app);
    if(!fout.is_open()){
        std::cout << "Failed opening file!" << std::endl;
        return;
    }
    unsigned int count_products;
    std::cout << "Input the number of products to record their data in the file\n";
    std::cin >> count_products;
    for(int i = 0; i < count_products; i++){
        Product p;
        std::cout << "Input the product code\n";
        std::cin >> p.code;
        std::cout << "Input the product name\n";
        std::cin.ignore();
        std::cin.getline(p.name, 50);
        std::cout << "Input the product price\n";
        std::cin >> p.price;
        std::cout << "Input the product count\n";
        std::cin >> p.count;
        fout.write((char*)&p, sizeof(p));
    }
    fout.close();
    return;
}

void read_func(){
    std::ifstream fin("products.bin", std::ios::binary);
    if(!fin.is_open()){
        std::cout << "File not found!" << std::endl;
        return;
    }
    Product p;
    std::cout << "Products:\n CODE/NAME/PRICE/COUNT" << std::endl;
    while(fin.read((char*)&p, sizeof(p))){
        std::cout << p.code << " " << p.name << " " << p.price << " " << p.count << std::endl;
    }
    fin.close();
    return;
}

void search_by_code(){
    std::ifstream fin("products.bin", std::ios::binary);
    if(!fin.is_open()){
        std::cout << "File not found!" << std::endl;
        return;
    }
    unsigned int code;
    std::cout << "Input the product code for the search\n";
    std::cin >> code;
    Product p;
    bool isFind = false;
    while(fin.read((char*)&p, sizeof(p))){
        if(p.code == code){
            isFind = true;
            std::cout << "Product with code = " << code << " is find:\n";
            std::cout << "CODE/NAME/PRICE/COUNT\n";
            std::cout << p.code << " " << p.name << " " << p.price << " " << p.count << std::endl;
        }
    }
    if(!isFind){
        std::cout << "Product with code = " << code << " is not find\n";
    }
    fin.close();
    return;
}

void summary_price(){
    double sum = 0;
    std::ifstream fin("products.bin", std::ios::binary);
    if(!fin.is_open()){
        std::cout << "File not found!" << std::endl;
        return;
    }
    Product p;
    while(fin.read((char*)&p, sizeof(p))){
        sum += (p.price * p.count);
    }
    std::cout << "Sumary price = " << sum << std::endl;
    fin.close();
    return;
}

int main(){
    int choise = 0;
    std::cout << "Input command number:" << std::endl;
    std::cout << "1 - if you want write products\n";
    std::cout << "2 - if you want read info about all products\n";
    std::cout << "3 - if you want to write the data first and then read it\n";
    std::cout << "4 - if you want to find the product by the product code\n";
    std::cout << "5 - if you want to print the total cost of all products\n";
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
        search_by_code();
        break;
    case 5:
        summary_price();
        break;
    default:
        std::cout << "Unknown command\n";
        break;
    }
    return 0;
}