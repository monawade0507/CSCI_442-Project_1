#include "thread.h"

void Thread::setID (int id) {
  this->ID = id;
}

int Thread::getID () {
  return this->ID;
}

// void Thread::setStage (int state) {
//   this->state = static_cast<Stage>(state);
// }
//
// int Thread::getStage () {
//   return (int)this->state;
// }

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

void Thread::setAmtBurst (int amt) {
  this->amtBurst = amt;
}

int Thread::getAmtBurst () {
  return this->amtBurst;
}

void Thread::cleanThread () {
  this->burstPair.clear();
  this->ID = -1;
  this->arrivalTime = -1;
  this->amtBurst = -1;
  //this->state = none;
}

void Thread::changeStage (int newStages) {
  this->preState = this->currentState;
  this->currentState = static_cast<Stage>(newStages);
}

std::string Thread::getPreState () {
  switch (this->preState)
    {
      case NEW:
        return "NEW";
        break;
      case READY:
        return "READY";
        break;
      case RUNNING:
        return "RUNNING";
        break;
      case BLOCKED:
        return "BLOCKED";
        break;
      case EXIT:
        return "EXIT";
        break;
      default:
        return "NONE";
    }

}

std::string Thread::getCurrentState () {
  switch (this->currentState)
    {
      case NEW:
        return "NEW";
        break;
      case READY:
        return "READY";
        break;
      case RUNNING:
        return "RUNNING";
        break;
      case BLOCKED:
        return "BLOCKED";
        break;
      case EXIT:
        return "EXIT";
        break;
      default:
        return "NONE";
    }

}
