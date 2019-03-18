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
    NONE = -1,
    NEW = 0,
    READY = 1,
    RUNNING = 2,
    BLOCKED = 3,
    EXIT = 4
  };



public:
  Thread () {
    this->ID = -1;
    this->arrivalTime = -1;
    this->amtBurst = -1;
    this->preState = NONE;
    this->currentState = NEW;
  }

  void setID (int id);
  int getID ();
  void setStage (int state);
  int getStage ();
  void setBurstCPU (int cpu);
  void setBurstIO (int io);
  int getBurstCPU ();
  int getBurstIO ();
  std::vector<int> split(std::string str, char delimiter);
  void addToBurstVector (int cpu, int io);
  int getBurstInfo (int burst, std::string choice);
  void setArrivalTime (int time);
  int getArrivalTime ();
  void setAmtBurst (int amt);
  int getAmtBurst ();
  void cleanThread();
  void changeStage (int newStages);
  std::string getPreState ();
  std::string getCurrentState();

private:
  int ID;
  std::vector<Burst> burstPair;
  Burst thrBurst;
  Stage preState;
  Stage currentState;
  int arrivalTime;
  int amtBurst;


};
