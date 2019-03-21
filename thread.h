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

  enum Event {
    THREAD_NONE = -1,

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
  Thread () {
    this->ID = -1;
    this->arrivalTime = -1;
    this->amtBurst = -1;
    this->preState = NONE;
    this->currentState = NEW;
    this->totalCPUtime = -1;
    this->totalIOtime = -1;
    this->clock_state = -1;
    this->eventStatus = static_cast<Event>(-1);
    this->eventStatus = static_cast<Event>(-1);
    this->waitingTime = -1;
    this->taskTime = -1;
    this->loc = 0;
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
  void updateEvent (int update);
  std::string getEvent ();
  std::string getPreEvent ();

  // ------
  int totalCPUtime;
  int totalIOtime;
  int clock_state;
  int waitingTime;
  int taskTime;
  int loc;

private:
  int ID;
  std::vector<Burst> burstPair;
  Burst thrBurst;
  Stage preState;
  Stage currentState;
  int arrivalTime;
  int amtBurst;
  Event eventStatus;
  Event preEvent;

};
