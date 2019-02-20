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
#include "process.h"

class Simulator {

enum Event {
  THREAD_ARRIVED,
  // a thread has been created in the system
  THREAD_DISPATCH_COMPLETED,
  // a thread swithc has completed, allowing a new thread to
  // start executing on the CPU
  PROCESS_DISPATCH_COMPLETED,
  // a process swtich has completed, allowing a new thread in a
  // diffrent process to start executing on the CPU
  CPU_BURST_COMPLETED,
  // a thread has finished one of its CPU burst and is once again
  // read to be executed
  IO_BURST_COMPLETED,
  // a thread has finished one of its I/O bursts and is once again
  // ready to be executed
  THREAD_COMPLETED,
  // a thread has finished the last of its CPU bursts
  THREAD_PREEMPTED,
  // a thread has been preempted during execution of one of its CPU bursts
  DISPATCHER_INVOKED
  // The OS dispatcher routing has been invoked to determine the next
  // thread to be run on the CPU
};

public:
  Simulator () {
    this->fileName = "";
    this->numProcesses = -1;
    this->threadSwitchOverhead = -1;
    this->processSwitchOverhead = -1;

  }

  void setFileName (std::string file);
  std::vector<int> split(std::string str, char delimiter);
  std::string getFileName ();
  void parse (std::string line);
  void simulate();    // main loop

private:
  std::string fileName;
  int numProcesses;
  int threadSwitchOverhead;
  int processSwitchOverhead;
  std::vector<Process> processStore;
  std::vector<std::vector<int>> schedule;
};
