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
}
