// Programmer: Dhanush Patel
// Programmer's ID: 1553428

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

#include <cmath>
#include <cstdlib>

#include "DynamicArray.h"
#include "Queue.h"

struct Customer{
  char ID;
  int arrivalT;
  int endT;
};

int getRandomNumberOfArrivals(double);
char genID(char&);
int randTimeAdd(int, int);

int main(){
  srand(time(0));
  rand();

  cout << "Programmer: Dhanush Patel\n";
  cout << "Programmer's ID: 1553428\n";
  cout << "File: " << __FILE__ << "\n\n";
  int numServers = 0, waitMaxLength = 0, minServTime = 0, maxServTime = 0, clockStopTime = 0;
  double avgArrivalRate = 0.0;
  char curAlpha = 'A';

  ifstream fin;
  fin.open("simulation.txt");
  int switchCount = 0;
  while(fin.good()){
    string input;
    getline(fin, input);
    switch(switchCount){
      case 0:
        numServers = atoi(input.c_str());
        cout << "number of servers:     " << numServers << endl;
        break;
      case 1:
        avgArrivalRate = atof(input.c_str());
        break;
      case 2:
        waitMaxLength = atoi(input.c_str());
        cout << "maximum queue length:  " << waitMaxLength << endl;
        break;
      case 3:
        minServTime = atoi(input.c_str());
        cout << "minimum service time:  " << minServTime << " minutes" << endl;
        break;
      case 4:
        maxServTime = atoi(input.c_str());
        cout << "maximum service time:  " << maxServTime << " minutes" << endl;
        break;
      case 5:
        clockStopTime = atoi(input.c_str());
        cout << "customer arrival rate: " << avgArrivalRate << " per minute, for " << clockStopTime << " minutes" << endl;
        break;
      default:
        throw("UH OH - PROBLEM");
    }
    switchCount++;
  }

  Queue<Customer> custQ;
  DynamicArray<Customer> nowServing;
  DynamicArray<bool> serversStatus;

  for(int time = 0; ;time++){
    // handle all services scheduled to complete at this clock time
    for(int i = 0; i < numServers; i++){
      if (serversStatus[i]){ //means is busy
        if(nowServing[i].endT == time) {
          serversStatus[i] = false;
        }
      }
    }
    // handle new arrivals -- can be turned away if wait queue is at maximum length!
    if(time < clockStopTime){
      avgArrivalRate = getRandomNumberOfArrivals(avgArrivalRate);
      for(int i = 0; i < avgArrivalRate; i++){
        if(custQ.size() < waitMaxLength){
          Customer c;
          c.ID = genID(curAlpha);
          c.arrivalT = time;
          custQ.push(c);
        }
      }
    }
    // for idle servers, move customer from wait queue and begin
    for(int i = 0; i < numServers; i++){
      if(!serversStatus[i] && !custQ.empty()){
        nowServing[i] = custQ.front();
        custQ.pop();
        nowServing[i].endT = time + randTimeAdd(minServTime, maxServTime);
        serversStatus[i] = true;
      }
    }
    //output the summary
    //output the current time
    //output a visual representation of the servers and the wait queue
    cout <<"\nTime: " << time << endl;
    cout << "---------------------------" << endl;
    cout << "server now serving wait queue" << endl;
    cout << "------ ----------- ----------" << endl;
    for(int i = 0; i < numServers; i++){
      string show;
        if(!serversStatus[i]){
          show = " ";
        }
        else{
          show = nowServing[i].ID;
        }
      show = serversStatus[i] ? nowServing[i].ID : ' ';
      if(i == 0){
        Queue<Customer> tempQ = custQ;
        string qList;
        for(int j = 0; j < tempQ.size(); j++) {
          qList += tempQ.front().ID;
          tempQ.pop();
        }
        cout << setw(2)  << i << setw(10) << show << setw(10) << qList << endl;
      }
      else {
        cout << setw(2) << i << setw(10) << show << endl;
      }
    }

    int numIdle = 0;
    for(int i = 0; i < numServers; i++){
      if(!serversStatus[i]){
        numIdle++;
      }
    }
    if(numIdle == numServers && time >= clockStopTime){
      break;
    }

    do
    {
      cout << '\n' << "Press ENTER to continue...";
    } while (cin.get() != '\n');
  }
}

int randTimeAdd(const int a, const int b){
  return a + (rand() % b);
}

char genID(char& curAlpha) {
 if(curAlpha == 'Z'){
   curAlpha = 'A';
   return 'Z';
 }
 return curAlpha++;
}

int getRandomNumberOfArrivals(double averageArrivalRate){
  int arrivals = 0;
  double probOfnArrivals = exp(-averageArrivalRate);
  for (double randomValue = (double)rand() / RAND_MAX;
       (randomValue -= probOfnArrivals) > 0.0;
       probOfnArrivals *= averageArrivalRate / static_cast<double>(++arrivals));
  return arrivals;
}