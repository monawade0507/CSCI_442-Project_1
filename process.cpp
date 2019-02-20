#include "process.h"

void Process::setID (int id) {
  this->ID = id;
}

void Process::setAmtThreads (int amt) {
  this->amtThreads = amt;
}

int Process::getID () {
  return this->ID;
}

int Process::getAmtThreads () {
  return this->amtThreads;
}

void Process::setState (int stage) {
  this->state = static_cast<Priority>(stage);
}

int Process::getState () {
  return (int)this->state;
}

void Process::addThread (Thread thr) {
  this->threads.push_back(thr);
}

void Process::cleanProcess () {
  this->ID = -1;
  this->amtThreads = -1;
  this->threads.clear();
  this->state = none;
  this->event = static_cast<Event>(-1);
}

void Process::updateEvent (int update) {
  this->event = static_cast<Event>(update);
}

std::string Process::getEvent () {
  switch (this->event)
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


std::string Process::getPriority () {
  switch (this->state)
  {
    case system:
      return "SYSTEM";
      break;
    case interactive:
      return "INTERACTIVE";
      break;
    case normal:
      return "NORMAL";
      break;
    case batch:
      return "BATCH";
      break;
    default:
      return "NONE";
  }
}
