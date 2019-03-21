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

void Thread::updateEvent (int update) {
  this->preEvent = this->eventStatus;
  this->eventStatus  = static_cast<Event>(update);
}

std::string Thread::getEvent () {
  switch (this->eventStatus)
  {
    case THREAD_ARRIVED:
      return "THREAD_ARRIVED";
      break;
    case THREAD_DISPATCH_COMPLETED:
      return "THREAD_DISPATCH_COMPLETED";
      break;
    case PROCESS_DISPATCH_COMPLETED:
      return "PROCESS_DISPATCH_COMPLETED";
      break;
    case CPU_BURST_COMPLETED:
      return "CPU_BURST_COMPLETED";
      break;
    case IO_BURST_COMPLETED:
      return "IO_BURST_COMPLETED";
      break;
    case THREAD_COMPLETED:
      return "THREAD_COMPLETED";
      break;
    case THREAD_PREEMPTED:
      return "THREAD_PREEMPTED";
      break;
    case DISPATCHER_INVOKED:
      return "DISPATCHER_INVOKED";
      break;
    default:
      return "NONE";
  }
}

std::string Thread::getPreEvent () {
  switch (this->preEvent)
  {
    case THREAD_ARRIVED:
      return "THREAD_ARRIVED";
      break;
    case THREAD_DISPATCH_COMPLETED:
      return "THREAD_DISPATCH_COMPLETED";
      break;
    case PROCESS_DISPATCH_COMPLETED:
      return "PROCESS_DISPATCH_COMPLETED";
      break;
    case CPU_BURST_COMPLETED:
      return "CPU_BURST_COMPLETED";
      break;
    case IO_BURST_COMPLETED:
      return "IO_BURST_COMPLETED";
      break;
    case THREAD_COMPLETED:
      return "THREAD_COMPLETED";
      break;
    case THREAD_PREEMPTED:
      return "THREAD_PREEMPTED";
      break;
    case DISPATCHER_INVOKED:
      return "DISPATCHER_INVOKED";
      break;
    default:
      return "NONE";
  }
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

void Thread::setAmtBurst (int amt) {
  this->amtBurst = amt;
  // Burst tmp;
  // tmp.cpu = -5;
  // tmp.io = -5;
  // for (int i = 0; i < amt; i++) {
  //   burstPair.push_back(tmp);
  // }

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
  this->eventStatus = static_cast<Event>(-1);
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

int Thread::getBurstInfo(int burst, std::string choice) {
  // either pass in cpu or io
  Burst temp;
  if (burst < this->burstPair.size()) {
    temp = this->burstPair.at(burst);
    if ( choice == "cpu" ) {
      return temp.cpu;
    }
    else if ( choice == "io") {
      return temp.io;
    }
    else {
      return -1;
    }
  }
  else {
    return -2;
  }

}
