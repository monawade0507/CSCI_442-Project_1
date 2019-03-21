#include "simulator.h"


int main(int argc, char* argv[]) {
  bool fileNameEntered = false;
  Simulator sim = Simulator();
  bool FCFS_on = false;
  bool verbose_on = false;

  // Handle the command line arguments and determine action
  if (argc == 1) {
    // Only the executable name

  }
  else {
    // Handle the command line arguments here
    for (int i = 1; i < argc; i++) {
      // Determine each flad or file name
      std::string cmd = argv[i];
        // -t, --per_thread -> Output additional per-thread status for arrival
        //  time, service time, etc.
      if ( cmd == "-t" || cmd ==  "--per_thread" ) {
        std::cout << "per_thread tag was used" << std::endl;

      }

        // -v, --verbose -> Output information about every state-changing event
        //  and scheduling decision
      else if ( cmd == "-v" || cmd == "--verbose" ) {
        std::cout << "Verbose tag was used" << std::endl;
        verbose_on = true;

      }

        // -a, --algorithm -> The scheduling algorithm to use. One of FCFs, RR,
        //  Priority, or Custom
      else if ( cmd == "-a" || cmd == "--algorithm" ) {
        std::cout << "Algorithm tag was used" << std::endl;
        for (int j = 1; j < argc; j++) {
          // Determine each flad or file name
          std::string algorithm = argv[j];
          if (algorithm == "FCFS") {
            FCFS_on = true;
          }
        }

      }
        // -h, --help -> Display a help message about these flags then exit
      else if ( cmd == "-h" || cmd == "--help" ) {
        std::cout << "Here are the available tags for simulator: " << std::endl;
        std::cout << "-t, --per_thread" << std::endl;
        std::cout << "  -> Output additional per-thread status for arrival time, service time, etc." << std::endl;
        std::cout << "-v, --verbose" << std::endl;
        std::cout << "  -> Output information about every state-changing event and scheduling decision" << std::endl;
        std::cout << "-a, --algorithm" << std::endl;
        std::cout << "  -> The scheduling algorithm to use. One of FCFs, RR, Priority, or Custom" << std::endl;
        exit(0);
      }
      else if ( cmd.length() > 1 && cmd != "-h" && cmd != "--help" && cmd != "-a" && cmd != "--algorithm" && cmd != "-t" && cmd !=  "--per_thread" && !FCFS_on) {
        // fileName string was provided
        sim.setFileName(cmd);
        std::cout << "File Name entered: " << cmd << std::endl;
        fileNameEntered = true;
      }
    }
  }

  // Extract information for the input file
  if ( fileNameEntered ) {
    std::string line;
    std::ifstream file(sim.getFileName());
    if (file) {
      if (file.is_open()) {
        while (!file.eof()) {
          if (getline (file, line)) {
            // using the string of each line and execute the command
            // Process each line of the file
            sim.parse(line);
          }
        }
      }
      file.close();
    }
    else {
      std::cout << "File does not exist" << std::endl;
    }
  }

  /*
   main loop of the simulation:
   should consist of processing the next event, perhaps adding more future events
   in the queue as a result, advancing the clock (by taking the next scheduled
   event from the front of the event queue), so on until all threads are
   terminated.
  */
  std::cout << "DONE 0" << std::endl;
  sim.createProcessAndThread();
  std::cout << "DONE 1" << std::endl;
  sim.simulate();
  std::cout << "DONE 2" << std::endl;
  if (FCFS_on) {
    sim.FCFS(verbose_on);
  }

}



// ***************************************************************************//
// Simulator Class function implmentations
// ***************************************************************************//

void Simulator::setFileName (std::string file) {
  this->fileName = file;
}

std::string Simulator::getFileName () {
  return this->fileName;
}

std::vector<int> Simulator::split(std::string str, char delimiter) {
  // splits strings into different elements in the vector broken up by the
  // delimiter
  std::vector<int> final;
  std::stringstream ss(str);
  std::string temp;
  int num;
  while (getline(ss, temp, delimiter)) {
    std::stringstream chg(temp);
    chg >> num;
    final.push_back(num);
  }
  return final;
}

void Simulator::parse (std::string line) {
  // split each line into a vector of integers
  std::vector<int> occurence;
  occurence = split(line, ' ');
  if (occurence.size() > 0) {
    schedule.push_back(occurence);
  }
}

void Simulator::createProcessAndThread () {
  int ptr = 0;
  int amnt = 0;
  std::vector<int> header = schedule.at(ptr);
  this->numProcesses = header.at(0);
  this->threadSwitchOverhead = header.at(1);
  this->processSwitchOverhead = header.at(2);
  ptr ++;


  while (amnt < (this->numProcesses)) {
    std::vector<int> prcHeader = schedule.at(ptr);

    this->tmpProcess.setID(prcHeader.at(0));
    this->tmpProcess.setState(prcHeader.at(1));
    this->tmpProcess.setAmtThreads(prcHeader.at(2));
    //this->tmpProcess.updateEvent(0);
    ptr ++;

    int threadCnt = 0;
    while (threadCnt < (this->tmpProcess.getAmtThreads())) {
        std::vector<int> thr = schedule.at(ptr);

        this->tmpProcess.tmpThread.setID(threadCnt);
        this->tmpProcess.tmpThread.setArrivalTime(thr.at(0));
        this->tmpProcess.tmpThread.setAmtBurst(thr.at(1));
        ptr ++;

        // add new thread to event eventQueue
        this->time = this->tmpProcess.tmpThread.getArrivalTime();
        //eventQueue.insert(this->time, this->tmpProcess);
        //eventQueue.insert( std::pair<int, Process>(this->time, this->tmpProcess));
        std::cout << "PLEASE";
        int burstCnt = 0;
        while (burstCnt < (this->tmpProcess.tmpThread.getAmtBurst())) {
          std::vector<int> pair = schedule.at(ptr);

          if (pair.size() == 2) {
            this->tmpProcess.tmpThread.addToBurstVector(pair.at(0), pair.at(1));
          }
          if (pair.size() == 1) {
            this->tmpProcess.tmpThread.addToBurstVector(pair.at(0), 0);
          }
          burstCnt ++;
          ptr ++;
        }

        this->tmpProcess.addThread(this->tmpProcess.tmpThread);
        threadCnt ++;

        //ptr ++;
        this->tmpProcess.tmpThread.cleanThread();
    }

    this->processStore.push_back(this->tmpProcess);
    amnt ++;
    //eventQueue.insert( std::pair<int, Process>(this->time, this->tmpProcess));
    //ptr ++;
    this->tmpProcess.cleanProcess();
    std::cout << "WHY__";
  }

}

// Main loop
void Simulator::simulate () {
  // Print out event queue as desired
  // Loop through map
  for (const auto& elem : processStore) {
    //elem.first gives the key -> int
    //elem.second gives mapped element -> Process
    Process tmp = elem;
    //std::cout << "  " << tmp.getEvent() << std::endl;
    for ( int i = 0; i < tmp.threads.size(); i++) {
      tmp.tmpThread = tmp.threads.at(i);
      std::cout << "  Thread " << tmp.tmpThread.getID() << " ";
      std::cout << "in process " << tmp.getID() << "  [";
      std::cout << tmp.getPriority() << "] " << std::endl;
      tmp.tmpThread.changeStage(1);
      std::cout << "  Transitioned from " << tmp.tmpThread.getPreState();
      std::cout << " to " << tmp.tmpThread.getCurrentState() << std::endl;
      std::cout << std::endl;
      std::cout << "Burst Size: " << tmp.tmpThread.getAmtBurst() << std::endl;
      std::cout << "Burst time: " << std::endl;
      for ( int j = 0; j < tmp.tmpThread.getAmtBurst(); j++) {
        std::cout << "CPU: " << tmp.tmpThread.getBurstInfo(j, "cpu")  << std::endl;
        std::cout << "IO:  " << tmp.tmpThread.getBurstInfo(j, "io") << std::endl;
      }
    }
  }
}

void Simulator::FCFS (bool verbose_act) {

  std::cout << "Starting Processes: " << processStore.size() << std::endl;
  for (int i = 0; i  < processStore.size(); i++ ) {
    std::cout << "Amount of Threads: " << processStore.at(i).threads.size() << std::endl;
  }
  std::cout << std::endl;

/* processStore.front().threads.size()
    Each algorithm will act like individual event handlers
    FCFS will focus on adding the the eventQueue in the FCFS order
      - implement switch case for 8 different events
      - will add events to eventQueue
      - update main clock -> int time
*/

// Add to the eventQueue before launching into while loop for CPU scheduling simulation
// Process are stored in a processStore; each process has a vector of threads
  processStore.front().threads.front().updateEvent(0);
  processStore.front().threads.front().changeStage(0);
  std::cout << "Adding Process " << processStore.front().getID();
  std::cout << "  Thread " << processStore.front().threads.front().getID() << std::endl;
  events.push(processStore.front().threads.front());
  completeSimulation.push(processStore.front().threads.front());
  processStore.front().threads.erase(processStore.front().threads.begin());
  //std::cout << "Remaining Processes: " << processStore.size() << std::endl;
  //std::cout << "Remaining Threads in " << processStore.front().getID() << " : " << processStore.front().threads.size() << std::endl;

  while (!events.empty()) {

    // Check if there are anymore new threads
    if (!processStore.empty()) {
      // means that processes with threads still need to be added to events Queue
      if (!processStore.front().threads.empty()) {
        // means that threads still need to be added to the events Queue
        processStore.front().threads.front().updateEvent(0);
        processStore.front().threads.front().changeStage(0);
        events.push(processStore.front().threads.front());
        completeSimulation.push(processStore.front().threads.front());
        std::cout << "Adding Process " << processStore.front().getID();
        std::cout << "  Thread " << processStore.front().threads.front().getID() << std::endl;
        processStore.front().threads.erase(processStore.front().threads.begin());
        //std::cout << "Remaining Processes: " << processStore.size() - 1 << std::endl;
        //std::cout << "Remaining Threads in " << processStore.front().getID() << " : " << processStore.front().threads.size() << std::endl;
      }
      else {
        // you can remove the process when there are no more threads remaining
        processStore.erase(processStore.begin());
      }

    }

    // Handle the events in the queue
    Thread thr = events.front();
    std::cout << "Handling Thread: " << thr.getID() << std::endl;
    std::cout << "Current Thread Event: " << thr.getEvent() << std::endl;
    events.pop();
    // Testing eventStatus between the 8 different events
    //std::cout << "HERE " << std::endl;

    if (thr.getEvent() == "DISPATCHER_INVOKED") {

      // Navigates all events except for THREAD_COMPLETED
      //std::cout << "DISPATCHER_INVOKED : ";

      if (thr.getPreEvent() == "THREAD_ARRIVED") {
        //std::cout << "Previous event: THREAD_ARRIVED" << std::endl;
        if (thr.getID() == 0) {
          thr.updateEvent(2);
          thr.taskTime = 7;
        }
        else {
          // otherwise, add event "THREAD_DISPATCH_COMPLETED"
          thr.updateEvent(1);
          thr.taskTime = 3;
        }
        // add to the queues
        events.push(thr);
        completeSimulation.push(thr);
        continue;
      }
      if (thr.getPreEvent() == "THREAD_DISPATCH_COMPLETED") {
        // update thread state to running
        //std::cout << "Previous event: THREAD_DISPATCH_COMPLETED" << std::endl;
        thr.updateEvent(3);
        thr.taskTime = 3;
        events.push(thr);
        completeSimulation.push(thr);
        continue;
      }
      if (thr.getPreEvent() == "PROCESS_DISPATCH_COMPLETED") {
        //std::cout << "Previous event: PROCESS_DISPATCH_COMPLETED" << std::endl;
        thr.updateEvent(3);
        thr.taskTime = 7;
        events.push(thr);
        completeSimulation.push(thr);
        continue;
      }
      if (thr.getPreEvent() == "CPU_BURST_COMPLETED") {
        //std::cout << "Previous event: CPU_BURST_COMPLETED" << std::endl;
        thr.changeStage(4);
        thr.taskTime = thr.getBurstInfo(thr.loc, "cpu");
        thr.loc ++;
        events.push(thr);
        completeSimulation.push(thr);
        continue;
      }
      if (thr.getPreEvent() == "IO_BURST_COMPLETED") {
        //std::cout << "Previous event: IO_BURST_COMPLETED" << std::endl;
        thr.changeStage(2);
        if (thr.getBurstInfo(thr.loc, "io") == 0) {
          // if there is no io time, that means it is on the last thread
          thr.loc = 0;
          thr.updateEvent(6);
        }
        else {
          thr.loc ++;
          thr.updateEvent(3);

        }
        thr.taskTime = thr.getBurstInfo(thr.loc, "io");
        events.push(thr);
        completeSimulation.push(thr);
        continue;
      }
    }

    if (thr.getEvent() == "THREAD_ARRIVED") {
      std::cout << "THREAD_ARRIVED" << std::endl;
      // test the thread ID
      //  if ID == 0; then add event "PROCESS_DISPATCH_COMPLETED"
      // change to dispatch
      thr.updateEvent(7);
      thr.taskTime = 0;
      // add to the queues
      events.push(thr);
      completeSimulation.push(thr);
      continue;
    }

    if (thr.getEvent() == "THREAD_DISPATCH_COMPLETED") {
      // update thread state to running
      std::cout << "THREAD_DISPATCH_COMPLETED" << std::endl;
      thr.changeStage(2);
      thr.updateEvent(7);
      thr.taskTime = 0;
      events.push(thr);
      completeSimulation.push(thr);
      continue;
    }

    if (thr.getEvent() == "PROCESS_DISPATCH_COMPLETED") {
      std::cout << "PROCESS_DISPATCH_COMPLETED" << std::endl;
      thr.changeStage(2);
      thr.updateEvent(7);
      thr.taskTime = 0;
      events.push(thr);
      completeSimulation.push(thr);
      continue;
    }

    if (thr.getEvent() == "CPU_BURST_COMPLETED") {
      std::cout << "CPU_BURST_COMPLETED" << std::endl;
      thr.changeStage(3);
      thr.updateEvent(7);
      thr.taskTime = 0;
      events.push(thr);
      completeSimulation.push(thr);
      continue;
    }

    if (thr.getEvent() == "IO_BURST_COMPLETED") {
      std::cout << "IO_BURST_COMPLETED" << std::endl;
      thr.changeStage(2);
      thr.updateEvent(7);
      thr.taskTime = 0;
      events.push(thr);
      completeSimulation.push(thr);
      continue;
    }

    if (thr.getEvent() == "THREAD_COMPLETED") {
      std::cout << "THREAD_COMPLETED" << std::endl;
      // will not add anything to the events anymore; only the completeSimulation
      thr.changeStage(4);
      completeSimulation.push(thr);
      continue;
    }

  }


  std::cout << "completeSimulation Queue size " << completeSimulation.size() << std::endl;
}
