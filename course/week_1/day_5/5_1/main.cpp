#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <algorithm>
#include <random>


int main() {
    std::vector<int> vector;
    std::list<int> list;
    long int limit = 100000000;
    int size = 100000;
    typedef std::chrono::duration<long double> stop_watch;
    //creating a vector of 50k random indices - will be used later on
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::vector<int> random_index(50000);
    for (int i = 0; i < 50000; i++){
        random_index[i] = i;
    }
    std::shuffle(random_index.begin(), random_index.end(), generator);
    //-------

    auto start_createvec = std::chrono::steady_clock::now();
    while(vector.size() < limit){
        vector.push_back(1);
    }
    auto end_createvec = std::chrono::steady_clock::now();
    std::cout << vector.size() << std::endl;
    stop_watch time_createmil(end_createvec - start_createvec);
    std::cout << "Time to create vector with 100.000.000 elems from back: " << time_createmil.count() << "seconds" << std::endl;

    auto start_clearvec = std::chrono::steady_clock::now();
    while (!vector.empty()){
        vector.pop_back();
    }
    auto end_clearvec = std::chrono::steady_clock::now();
    stop_watch time_removemil(end_clearvec - start_clearvec);
    std::cout << vector.size() << std::endl;
    std::cout << "Time to clear vector with 100.000.000 elems from back: " << time_removemil.count() << "seconds" << std::endl;

    auto start_create100k = std::chrono::steady_clock::now();
    while (vector.size() < size){
        vector.emplace(vector.begin(), 1);
    }
    auto end_create100k = std::chrono::steady_clock::now();
    stop_watch time_create100k(end_create100k - start_create100k);
    std::cout << vector.size() << std::endl;
    std::cout << "Time to create vector with 100.000 elems pushing them in the front: " << time_create100k.count() << "seconds" << std::endl;

    auto start_clear100k = std::chrono::steady_clock::now();
    while (!vector.empty()){
        vector.erase(vector.begin());
    }
    auto end_clear100k = std::chrono::steady_clock::now();
    stop_watch time_clear100k(end_clear100k - start_clear100k);
    std::cout << vector.size() << std::endl;
    std::cout << "Time to clear vector with 100.000 elems removing them from the front:  " << time_clear100k.count() << "seconds" << std::endl;

    vector.resize(50000);
    auto start_rndchange = std::chrono::steady_clock::now();
    for (int i = 0; i < 50000; i++){
        vector[random_index[i]] = i;
    }
    auto end_rndchange = std::chrono::steady_clock::now();
    stop_watch time_rndchange(end_rndchange - start_rndchange);
    std::cout << vector.size() << std::endl;
    std::cout << "Time to change 50k randomly chosen elems in vector: " << time_rndchange.count() << "seconds" << std::endl;


    //LIST
    std::cout << "LIST PART" << std::endl;

    auto start_createlist = std::chrono::steady_clock::now();
    while (list.size() < limit){
        list.push_back(1);
    }
    auto end_createlist = std::chrono::steady_clock::now();
    std::cout << list.size() << std::endl;
    stop_watch time_createmil_list(end_createlist - start_createlist);
    std::cout << "Time to create linked list with 100.000.000 elems pushing them in the back: " << time_createmil.count() << "seconds" << std::endl;

    auto start_clearlist = std::chrono::steady_clock::now();
    while (!list.empty()){
        list.pop_back();
    }
    auto end_clearlist = std::chrono::steady_clock::now();
    stop_watch time_clearlist(end_clearlist - start_clearlist);
    std::cout << list.size() << std::endl;
    std::cout << "Time to clear linked list with 100.000.000 elems removing them from the back: " << time_clearlist.count() << "seconds" << std::endl;

    auto start_create100klist = std::chrono::steady_clock::now();
    while (list.size() < size){
        list.push_front(1);
    }
    auto end_create100klist = std::chrono::steady_clock::now();
    stop_watch time_create100klist(end_create100klist - start_create100klist);
    std::cout << list.size() << std::endl;
    std::cout << "Time to create linked list with 100.000 elems pushing them in the front: " << time_create100klist.count() << "seconds" << std::endl;

    auto start_clear100klist = std::chrono::steady_clock::now();
    while (!list.empty()){
        list.pop_front();
    }
    auto end_clear100klist = std::chrono::steady_clock::now();
    std::cout << list.size() << std::endl;
    stop_watch time_clear100klist(end_clear100klist - start_clear100klist);
    std::cout << "Time to clear linked list with 100.000 elems removing them from the front: " << time_clear100klist.count() << "seconds" << std::endl;


    list.resize(50000);

    std::cout << list.size() << std::endl;
    //due to the nature of the list, to change the element on the certain
    //position one has to iterate through all of the previous elements
    auto start_rndlist = std::chrono::steady_clock::now();
    for (int i = 0; i < 50000; i++){
       *std::next(list.begin(), random_index[i]) = i;
    }
    auto end_rndlist = std::chrono::steady_clock::now();
    stop_watch time_rndlist(end_rndlist - start_rndlist);
    std::cout << list.size() << std::endl;
    std::cout << "Time to randomly change 50k elems in the linked list: " << time_rndlist.count() << "seconds" << std::endl;

    return 0;
}