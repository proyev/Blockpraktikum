#include <iostream>
#include <map>
#include <string>

int main() {
    int user_input;

    std::map<std::string, int> num_book;
    std::cout << "Please, enter: \n"
    << "\t0 - to exit\n"
    << "\t1 - to add number\n"
    << ">> "<< std::flush;
    std::cin >> user_input;

    while (user_input != 0){
        std::string name;
        int number;
        std::cout << "Enter the name: " << std::flush;
        std::cin >> name;
        std::cout << "Enter the number: " << std::flush;
        std::cin >> number;

        num_book[name] = number;
        std::cout << "Please, enter: \n"
                  << "\t0 - to exit\n"
                  << "\t1 - to add number\n"
                  << ">> "<< std::flush;
        std::cin >> user_input;
    }

    //iterators here
    for (auto next : num_book) std::cout << next.first << " - "
        << next.second << std::endl;


    return 0;
}
