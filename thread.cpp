#include "thread.h"

void Thread::setID (int id) {
  this->ID = id;
}

int Thread::getID () {
  return this->ID;
}

void Thread::setStage (int state) {
  this->state = state;
}

int Thread::getStage () {
  return (int)this->state;
}

void Thread::setBurstCPU (int cpu) {
  this->thrBurst.cpu = cpu;
}

void Thread::setBurstIO (int io) {
  this->thrBurst.io = io;
}

int Thread::getBurstCPU () {
  return this->thrBurst.cpu;
}

int Thread::getBurstIO () {
  return this->thrBurst.io;
}

std::vector<int> Thread::split(std::string str, char delimiter) {
  // splits strings into different elements in the vector broken up by the
  // delimiter
  std::vector<int> final;
  std::stringstream ss(str);
  std::string temp;
  int num;
  while (getline(ss, temp, delimiter)) {
    std::stringstream chg(temp);
    chg >> num;
    final.push_back(num);
  }
  return final;
}

void Thread::addToBurstVector(int cpu, int io) {
  Burst temp;
  temp.cpu = cpu;
  temp.io = io;
  this->burstPair.push_back(temp);
}

void Thread::setArrivalTime (int time) {
  this->arrivalTime = time;
}

int Thread::getArrivalTime () {
  return this->arrivalTime;
}
