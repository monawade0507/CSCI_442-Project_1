#include "simulator.h"


int main(int argc, char* argv[]) {
  bool fileNameEntered = false;
  Simulator sim = Simulator();
  bool FCFS_on = false;

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
  sim.createProcessAndThread();
  sim.simulate();
  if (FCFS_on) {
    sim.FCFS();
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
    this->tmpProcess.updateEvent(0);
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
        eventQueue.insert( std::pair<int, Process>(this->time, this->tmpProcess));

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
    //ptr ++;
    this->tmpProcess.cleanProcess();

  }

}

// Main loop
void Simulator::simulate () {
  // Print out event queue as desired
  // Loop through map
  for (const auto& elem : eventQueue) {
    //elem.first gives the key -> int
    //elem.second gives mapped element -> Process
    std::cout << "At time " << elem.first << ": " << std::endl;
    Process tmp = elem.second;
    std::cout << "  " << tmp.getEvent() << std::endl;
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

void Simulator::FCFS () {
  std::cout << "FCFS algorithm " << std::endl;
}
