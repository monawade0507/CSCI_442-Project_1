// ********************************************************
// * A common set of system include files
// ********************************************************
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/param.h>
#include <vector>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <fstream>
#include <sys/stat.h>
#include <ctype.h>
#include "thread.h"

class Process {
  enum Priority {
    none = -1,
    system = 0,
    interactive = 1,
    normal = 2,
    batch = 3
  };

  enum Event {
    NONE = -1,

    THREAD_ARRIVED = 0,
    // a thread has been created in the system
    THREAD_DISPATCH_COMPLETED = 1,
    // a thread swithc has completed, allowing a new thread to
    // start executing on the CPU
    PROCESS_DISPATCH_COMPLETED = 2,
    // a process swtich has completed, allowing a new thread in a
    // diffrent process to start executing on the CPU
    CPU_BURST_COMPLETED = 3,
    // a thread has finished one of its CPU burst and is once again
    // read to be executed
    IO_BURST_COMPLETED = 4,
    // a thread has finished one of its I/O bursts and is once again
    // ready to be executed
    THREAD_COMPLETED = 5,
    // a thread has finished the last of its CPU bursts
    THREAD_PREEMPTED = 6,
    // a thread has been preempted during execution of one of its CPU bursts
    DISPATCHER_INVOKED = 7
    // The OS dispatcher routing has been invoked to determine the next
    // thread to be run on the CPU
  };

public:
  Process () {
    this->ID = -1;
    this->amtThreads = -1;
    this->threads.clear();
    this->state = none;
    this->event = static_cast<Event>(-1);
  }

  void setID (int id);
  void setAmtThreads (int amt);
  void setState (int stage);
  int getID();
  int getAmtThreads();
  int getState ();
  void addThread (Thread thr);
  void cleanProcess ();
  void updateEvent (int update);
  std::string getEvent ();
  std::string getPriority ();

  // temp Thread used to add to threads
  Thread tmpThread = Thread();
  Event event;

private:
  int ID;
  int amtThreads;
  std::vector<Thread> threads;
  Priority state;

};
