#include <iostream>

class MyArrayList {
private:
    // ① 户口本：int* data; int size; int capacity;
int* data;
int size;
int capacity ;
public:
    // ② 你刚写的构造函数，原样放这
MyArrayList() {
  data = new int[4];
  size = 0;
  capacity = 4;
}

    // ③ 你前面写的四个函数：get / set / push_back / print，原样放这
int get(int i) {
  return data[i];
}

void set(int i, int val) {
  data[i] = val;
  return;
}

void push_back(int val) {
  data[size] = val;
  size++;
  return;
}

void print(){
  for ( int i = 0; i < size; i++) {
    std::cout << data[i] << std::endl;
}  
    return;
}
};

int main() {
    // ④ 刚才那四行：盖房子 arr、三个 push、print
    
MyArrayList arr;
arr.push_back(5);
arr.push_back(7);
arr.push_back(9);
arr.print();
return 0;
}