#include <utility>
#include <iostream>
#include <iomanip>
#include <ostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include "B-Tree.h"

void ReadFile(std::string input_file_name, std::vector<std::vector<std::string>> * book);
int main(int argc , char *argv[])
{
int counter = 0;

std::string input_file_name = std::string(argv[1]); // input file
int max_degree = std::stoi(argv[2]); // max degree
std::string searchword = std::string(argv[3]); // the word we search in our command line argument
std::pair<std::string, int > temp_pair;
temp_pair = std::make_pair(searchword, counter);

BTree Book_creation(max_degree);
Book_creation.ReadFile(input_file_name);

Book_creation.traverse();

Book_creation.search(temp_pair);

return 0;
}          





