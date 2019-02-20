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

public:
  Process () {
    this->ID = -1;
    this->amtThreads = -1;
    this->threads.clear();
    this->state = none;
  }

  void setID (int id);
  void setAmtThreads (int amt);
  void setState (int stage);
  int getID();
  int getAmtThreads();
  int getState ();
  void addThread (Thread thr);
  void cleanProcess ();

  // temp Thread used to add to threads
  Thread tmpThread = Thread();

private:
  int ID;
  int amtThreads;
  std::vector<Thread> threads;
  Priority state;
};
