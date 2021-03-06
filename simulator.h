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
#include <map>
#include <queue>
#include "process.h"

class Simulator {

public:
  Simulator () {
    this->fileName = "";
    this->numProcesses = -1;
    this->threadSwitchOverhead = -1;
    this->processSwitchOverhead = -1;
    this->time = -1;
    this->threads = 0;
  }

  void setFileName (std::string file);
  std::vector<int> split (std::string str, char delimiter);
  std::string getFileName ();
  void parse (std::string line);
  void createProcessAndThread ();
  void simulate ();    // main loop
  // algorithms
  void FCFS(bool verbose_act);
  void RR(bool verbose_act);
  void PRIORITY(bool verbose_act);
  void CUSTOM(bool verbose_act);

  // temp Process used to add to processStore
  Process tmpProcess = Process();

private:
  std::string fileName;
  int numProcesses;
  int threadSwitchOverhead;
  int processSwitchOverhead;
  int time;
  int threads;
  std::vector<Process> processStore;
  std::vector<std::vector<int>> schedule;

  // Event queue
  // Holds all of the events that occur over a simulation
  std::queue<Thread> events;
  std::queue<Thread> completeSimulation;

};
