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
    system = 0,
    interactive = 1,
    normal = 2,
    batch = 3
  };

public:
  Process () {
    this->ID = -1;
  }

private:
  int ID;
  std::vector<Thread> threads;
  Priority state;
};
