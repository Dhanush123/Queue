// Programmer: Dhanush Patel
// Programmer's ID: 1553428

#include <iostream>
using namespace std;

#include<cassert>

#include "Queue.h"
#include "Queue.h"

int main(){ //TODO: remove 2 in main
  cout << "Programmer: Dhanush Patel\n";
  cout << "Programmer's ID: 1553428\n";
  cout << "File: " << __FILE__ << endl;
  cout << endl;

  Queue<int> a;
  cout << "Using int values:" << endl;
  cout << "Testing Queue constructor and size()\n";
  assert(a.size()==0);

  cout << "\nTesting Queue push(), front(), and pop()\n";
  a.push(456);
  a.push(789);
  cout << "EXPECTED: 456 for 1st element\n";
  int addA = a.front();
  cout << "ACTUAL: " << addA << endl;
  cout << "EXPECTED: 789 for 2nd element\n";
  int addB = a.back();
  cout << "ACTUAL: " << addB << endl;
  cout << endl;
  a.pop();
  a.pop();
  cout << "Testing Queue empty()\n";
  cout << "EXPECTED: true (1) \n";
  cout << "ACTUAL: " << a.empty() << endl;
  cout << endl;

  a.push(111);
  a.push(222);
  cout << "Testing Queue clear()\n";
  a.clear();
  cout << "EXPECTED size = 0\n";
  cout << "ACTUAL: " << a.size() << endl;

  cout << "\nConst object test" << endl;
  const Queue<int> c;
  assert(c.size() == 0);
  assert(c.empty());

  a.push(1000);
  a.push(2000);
  cout << "\nObject copy test\n";
  Queue<int> d(a); // making a copy
  assert(a.size() == d.size());
  for (int i = 0; i < a.size(); i++){
    assert(a.front() == a.front());
    a.pop();
    d.pop();
  }

  a.push(3000);
  a.push(4000);
  // object assignment test
  cout << "\nObject assignment test\n";
  Queue<int> e;
  e = a;
  assert(a.size() == e.size());
  for (int i = 0; i < 10; i++) {
    assert(a.size() == e.size());
    a.pop();
    e.pop();
  }
}