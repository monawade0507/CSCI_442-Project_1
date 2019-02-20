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

class Thread {
  struct Burst {
    int cpu;
    int io;
  };

  enum Stage {
    NEW = 0,
    READY = 1,
    RUNNING = 2,
    BLOCKED = 3,
    EXIT = 4
  };

public:
  Thread () {
    this->ID = -1;
  }

  void setID (int id);
  int getID ();
  void setStage (int state);
  int getStage ();
  void setBurstCPU (int cpu);
  void setBurstIO (int io);
  int getBurstCPU (int cpu);
  int getBurstIO (int io);
  std::vector<int> split(std::string str, char delimiter);
  void addToBurstVector (int cpu, int io);
  // std::string getBurstPair ();


private:
  int ID;
  std::vector<Burst> burstPair;
  Burst thrBurst;
  Stage state;
};
