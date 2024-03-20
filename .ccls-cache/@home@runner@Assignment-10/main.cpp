#include <iostream>
#include <fstream>
#include <string>

int main() {
  std::ifstream myfile("input.txt");
  myfile.is_open();
  myfile.close();
}