#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>

using namespace std;

void fill_array(vector<int> &array) {
  size_t size;
  int min;
  int max;

  cout << "Enter desired array size: ";
  if(!(cin >> size) || size < 1) {
    throw runtime_error("Invalid size input value");
  }
  cout << "Enter array min value: ";
  if(!(cin >> min)) {
    throw runtime_error("Invalid min input value");
  }
  cout << "Enter array max value: ";
  if(!(cin >> max)) {
    throw runtime_error("Invalid max input value");
  }
  if(min > max) {
    throw invalid_argument("Min must be less or equal to max");
  }

  random_device seed;
  mt19937 random_engine(seed());
  uniform_int_distribution<int> gen(min, max);

  array.resize(size);
  for(size_t i = 0; i < size; i++) {
    array[i] = gen(random_engine);
  }
}

int main() {
  vector<int> list;

  try {
    fill_array(list);
  } catch(const runtime_error &e) {
    cerr << "Runtime error: " << e.what() << endl;
  } catch(const invalid_argument &e) {
    cerr << "Invalid argument: " << e.what() << endl;
  }


  return 0;
}
