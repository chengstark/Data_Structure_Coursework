#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

template <class T>
void print(std::vector<T> &data, const std::string &label) {
  std::cout << label << " ";
  for (int i = 0; i < data.size(); i++) {
    std::cout << " " << data[i];
  }
  std::cout << std::endl;
}


template <class T>
void reverse(std::vector<T> &data) {
  if (data.size() == 0 || data.size() == 1) return;
  int left = 0;
  int right = data.size()-1;
  while (left < right) {
      swap(data[left++], data[right--]);
  }
}

template <class T>
void reverse_list(list<T>& iList){
    if (iList.size() == 0 || iList.size() == 1) return;
    typename list<T>::iterator left = iList.begin();
    typename list<T>::reverse_iterator right = iList.rbegin();
    int count = 0;
    while (count <= iList.size() / 2) {
        swap(*left, *right);
        left++;  right++; count++;
    }
}

template <class T>
void print_list(const list<T>& iList, const std::string &label){
    std::cout << label << " ";
    typename list<T>::const_iterator iter;
    for (iter = iList.begin(); iter != iList.end(); iter++)
        cout << *iter << " ";
    cout << "\n\n";
}

template <class T>
void reverse_list2(list<T>& iList){
    if (iList.size() == 0 || iList.size() == 1) return;

    int count = 0;
    typename list<T>:: const_iterator right = iList.end();
    while (count <= iList.size() -1) {
        T the_front = iList.front();
        iList.pop_front();
        right = iList.insert(right, the_front);
        typename list<T>:: const_iterator right2 = iList.end();
        count ++;
    }
}


int main() {
  std::vector<int> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);

  print(data,"before:");
  reverse(data);
  print(data,"after: ");

  std::vector<std::string> data2;
  data2.push_back("apple");
  data2.push_back("banana");
  data2.push_back("carrot");
  data2.push_back("date");

  print(data2,"before:");
  reverse(data2);
  print(data2,"after: ");

  std::list<int> data3;
  data3.push_back(1);
  data3.push_back(2);
  data3.push_back(3);
  data3.push_back(4);
  data3.push_back(5);
  data3.push_back(6);
  data3.push_back(7);

  print_list(data3,"before:");
  reverse_list(data3);
  print_list(data3,"after: ");

  std::list<std::string> data4;
  data4.push_back("apple");
  data4.push_back("banana");
  data4.push_back("carrot");
  data4.push_back("date");

  print_list(data4,"before:");
  reverse_list(data4);
  print_list(data4,"after: ");

    std::list<int> data5;
    data5.push_back(1);
    data5.push_back(2);
    data5.push_back(3);
    data5.push_back(4);
    data5.push_back(5);
    data5.push_back(6);
    data5.push_back(7);

    print_list(data5,"before:");
    reverse_list2(data5);
    print_list(data5,"after: ");
}