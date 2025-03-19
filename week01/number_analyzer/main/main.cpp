/*******************************************************************************
 * Number Analyzer
 * BrandonDHaskell
 *
 * A command line program that takes in a set of integers as arguments and
 * returns:
 *      * Count of arguments passed in
 *      * Count of integers passed in
 *      * Average of integers
 *      * Min / Max of integers
 *      * Count of Even / Odd integers
 * 
*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>

bool isInteger(const std::string& str, int& outInt) {
    try {
        size_t pos;
        std::stoi(str, &pos);
        outInt = std::stoi(str, &pos);
        return pos == str.size();   // Ensure entire string was processed
    } catch (...) {
        return false;
    }
}

int getMin(std::vector<int> &vec) {
    
    int num = vec[0];
    for (int v : vec) {
        if (v < num) num = v;
    }
    return num;
}

int getMax(std::vector<int> &vec) {
    
    int num = vec[0];
    for (int v : vec) {
        if (v > num) num = v;
    }
    return num;
}

double getAvg(std::vector<int> &vec) {
    
    double num = 0.0;
    for (int v : vec) {
        num += v;
    }
    return (num / vec.size());
}

int getEvenCount(std::vector<int> &vec) {

    int num = 0;
    for (int v : vec) {
        if (v % 2 == 0) num++;
    }
    return num;
}

int getOddCount(std::vector<int> &vec) {

    int num = 0;
    for (int v : vec) {
        if (v % 2 == 1) num++;
    }
    return num;
}

int main(int argc, char* argv[]) {
    std::cout << "Num of args: " << argc - 1 << "\n";

    // If no numbers entered, end program
    if (argc < 2) {
        std::cout << "No numbers entered.\n";
        return 0;
    }

    // Test if args are Integers and add to vector
    std::vector<int> integers = {};
    for (int i = 1; i < argc; ++i) {
        int num;
        std::string arg = argv[i];

        if (isInteger(arg, num)) {
            integers.push_back(num);
        }
    }

    // If we have integers to evaluate then do this
    if (integers.size() > 0) {
        std::cout << "Integer count: " << integers.size() << "\n";
        std::cout << "Integer max: " << getMax(integers) << "\n";
        std::cout << "Integer min: " << getMin(integers) << "\n";
        std::cout << "Integer avg: " << getAvg(integers) << "\n";
        std::cout << "Even: " << getEvenCount(integers) << "\n";
        std::cout << "Odd: " << getOddCount(integers) << "\n";
    }

}