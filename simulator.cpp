#include "simulator.h"


int main(int argc, char* argv[]) {
  bool fileNameEntered = false;
  Simulator sim = Simulator();
  bool FCFS_on = false;
  bool RR_on = false;
  bool PRIORITY_on = false;
  bool CUSTOM_on = false;
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
        //  and scheduling de cision
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
          if (algorithm == "RR" ) {
            RR_on = true;
          }
          if (algorithm == "PRIORITY") {
            PRIORITY_on = true;
          }
          if (algorithm == "CUSTOM") {
            CUSTOM_on = true;
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
  //sim.simulate();
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
        this->tmpProcess.tmpThread.processID = tmpProcess.getID();
        this->tmpProcess.tmpThread.setArrivalTime(thr.at(0));
        this->tmpProcess.tmpThread.setAmtBurst(thr.at(1));
        ptr ++;

        // add new thread to event eventQueue
        this->time = this->tmpProcess.tmpThread.getArrivalTime();
        //eventQueue.insert(this->time, this->tmpProcess);
        //eventQueue.insert( std::pair<int, Process>(this->time, this->tmpProcess));
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
  time = 0;
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
  processStore.front().threads.front().changeStage(1);
  time += processStore.front().threads.front().getArrivalTime();
  std::cout << "*************************************" << std::endl;
  //std::cout << "At time: " << time << std::endl;
  std::cout << "  " << processStore.front().threads.front().getEvent() << std::endl;
  std::cout << "  Thread " << processStore.front().threads.front().getID();
  std::cout << "  in process " << processStore.front().threads.front().processID << std::endl;
  std::cout << "  Transitioned from " << processStore.front().threads.front().getPreState();
  std::cout << " to " << processStore.front().threads.front().getCurrentState() << std::endl;
  processStore.front().threads.front().updateEvent(7);
  events.push(processStore.front().threads.front());
  processStore.front().threads.erase(processStore.front().threads.begin());

  while (!events.empty()) {

    // Check if there are anymore new threads
    if (!processStore.empty()) {
      // means that processes with threads still need to be added to events Queue
      if (!processStore.front().threads.empty()) {
        // means that threads still need to be added to the events Queue
        processStore.front().threads.front().updateEvent(0);
        processStore.front().threads.front().changeStage(1);
        time = processStore.front().threads.front().getArrivalTime();
        std::cout << "*************************************" << std::endl;
        //std::cout << "At time: " << time << std::endl;
        std::cout << "  " << processStore.front().threads.front().getEvent() << std::endl;
        std::cout << "  Thread " << processStore.front().threads.front().getID();
        std::cout << "  in process " << processStore.front().threads.front().processID << std::endl;
        std::cout << "  Transitioned from " << processStore.front().threads.front().getPreState();
        std::cout << " to " << processStore.front().threads.front().getCurrentState() << std::endl;
        processStore.front().threads.front().updateEvent(7);
        events.push(processStore.front().threads.front());
        processStore.front().threads.erase(processStore.front().threads.begin());
        continue;
      }
      else {
        // you can remove the process when there are no more threads remaining
        processStore.erase(processStore.begin());

      }
    }

    // Handle the events in the queue
    Thread thr = events.front();
    if (thr.getEvent() == "DISPATCHER_INVOKED") {
      // Navigates all events except for THREAD_COMPLETED
      if (thr.getPreEvent() == "THREAD_ARRIVED") {
        if (thr.getID() == 0) {   // First thread has arrived which means PROCESS dispatch needs to run
          this->threads ++;
          //std::cout << "At time: " << time << std::endl;
          std::cout << "*************************************" << std::endl;
          std::cout << "  " << thr.getEvent() << std::endl;
          std::cout << "  Thread " << thr.getID();
          std::cout << "  in process " << thr.processID << std::endl;
          std::cout << "Selected from " << this->threads << " threads; will run to completion of burst" << std::endl;
          thr.changeStage(1);
          thr.updateEvent(2);
          //events.push(thr);

        }
        else {
          this->threads ++;
          //std::cout << "At time: " << time << std::endl;
          std::cout << "*************************************" << std::endl;
          std::cout << "  " << thr.getEvent() << std::endl;
          std::cout << "  Thread " << thr.getID();
          std::cout << "  in process " << thr.processID << std::endl;
          std::cout << "Selected from " << this->threads << " threads; will run to completion of burst" << std::endl;
          thr.updateEvent(1);
          thr.changeStage(1);
        }
        events.push(thr);
        events.pop();
        continue;
    }
    if (thr.getPreEvent() == "PROCESS_DISPATCH_COMPLETED") {
      thr.changeStage(2);
      std::cout << "*************************************" << std::endl;
      std::cout << "  " << thr.getEvent() << std::endl;
      std::cout << "  Thread " << thr.getID();
      std::cout << "  in process " << thr.processID << std::endl;
      std::cout << "Selected from " << this->threads << " threads; will run to completion of burst" << std::endl;
      thr.updateEvent(3);
      events.push(thr);
      events.pop();
      continue;
    }
    if (thr.getPreEvent() == "THREAD_DISPATCH_COMPLETED") {
      thr.changeStage(2);
      std::cout << "*************************************" << std::endl;
      std::cout << "  " << thr.getEvent() << std::endl;
      std::cout << "  Thread " << thr.getID();
      std::cout << "  in process " << thr.processID << std::endl;
      std::cout << "Selected from " << this->threads << " threads; will run to completion of burst" << std::endl;
      thr.updateEvent(3);
      events.push(thr);
      events.pop();
      continue;
    }

    if (thr.getPreEvent() == "CPU_BURST_COMPLETED") {
      thr.changeStage(2);
      std::cout << "*************************************" << std::endl;
      std::cout << "  " << thr.getEvent() << std::endl;
      std::cout << "  Thread " << thr.getID();
      std::cout << "  in process " << thr.processID << std::endl;
      std::cout << "Selected from " << this->threads << " threads; will run to completion of burst" << std::endl;
      thr.updateEvent(5);
      events.push(thr);
      events.pop();
      continue;
    }


  }

    if (thr.getEvent() == "PROCESS_DISPATCH_COMPLETED") {
      thr.changeStage(2);
      std::cout << "*************************************" << std::endl;
      //std::cout << "At time: " << time << std::endl;
      std::cout << "  " << thr.getEvent() << std::endl;
      std::cout << "  Thread " << thr.getID();
      std::cout << "  in process " << thr.processID << std::endl;
      std::cout << "  Transitioned from " << thr.getPreState();
      std::cout << " to " << thr.getCurrentState() << std::endl;
      thr.updateEvent(7);
      //time += 7;
      //thr.taskTime = 7;
      events.push(thr);
      events.pop();
      continue;
    }

    if (thr.getEvent() == "THREAD_DISPATCH_COMPLETED") {
      thr.changeStage(2);
      std::cout << "*************************************" << std::endl;
      //std::cout << "At time: " << time << std::endl;
      std::cout << "  " << thr.getEvent() << std::endl;
      std::cout << "  Thread " << thr.getID();
      std::cout << "  in process " << thr.processID << std::endl;
      std::cout << "  Transitioned from " << thr.getPreState();
      std::cout << " to " << thr.getCurrentState() << std::endl;
      thr.updateEvent(7);

      //time += 7;
      //thr.taskTime = 7;
      events.push(thr);
      events.pop();
      continue;
    }

    if (thr.getEvent() == "CPU_BURST_COMPLETED") {
      thr.changeStage(3);
      int t = thr.getBurstInfo(thr.loc, "cpu");

      std::cout << "*************************************" << std::endl;
      std::cout << "CPU burst time: " << t << std::endl;
      //std::cout << "At time: " << time << std::endl;
      std::cout << "  " << thr.getEvent() << std::endl;
      std::cout << "  Thread " << thr.getID();
      std::cout << "  in process " << thr.processID << std::endl;
      std::cout << "  Transitioned from " << thr.getPreState();
      std::cout << " to " << thr.getCurrentState() << std::endl;

      // Determine if last CPU
      if (thr.getBurstInfo(thr.loc, "io") == 0) {
        thr.updateEvent(7);
      }
      else {
        thr.updateEvent(4);
      }

      //time += 7;
      //thr.taskTime = 7;
      events.push(thr);
      events.pop();
      continue;
    }

    if (thr.getEvent() == "IO_BURST_COMPLETED") {
      thr.changeStage(1);
      int t = thr.getBurstInfo(thr.loc,"io" );
      std::cout << "*************************************" << std::endl;
      std::cout << "IO burst time: " << t << std::endl;
      //std::cout << "At time: " << time << std::endl;
      std::cout << "  " << thr.getEvent() << std::endl;
      std::cout << "  Thread " << thr.getID();
      std::cout << "  in process " << thr.processID << std::endl;
      std::cout << "  Transitioned from " << thr.getPreState();
      std::cout << " to " << thr.getCurrentState() << std::endl;
      thr.loc ++;
      thr.updateEvent(3);
      events.push(thr);
      events.pop();
      continue;
    }

    if (thr.getEvent() == "THREAD_COMPLETED") {
      threads --;
      thr.changeStage(4);
      std::cout << "*************************************" << std::endl;
      //std::cout << "At time: " << time << std::endl;
      std::cout << "  " << thr.getEvent() << std::endl;
      std::cout << "  Thread " << thr.getID();
      std::cout << "  in process " << thr.processID << std::endl;
      std::cout << "  Transitioned from " << thr.getPreState();
      std::cout << " to " << thr.getCurrentState() << std::endl;
      events.pop();
      continue;
    }
  }
}

void Simulator::RR(bool verbose_act) {
  std::cout << "Round Robin algorithm" << std::endl;
}

void Simulator::PRIORITY(bool verbose_act) {
  std::cout << "Priority algorithm" << std::endl;
}

void Simulator::CUSTOM(bool verbose_act) {
  std::cout << "CUSTOM algorithm" << std::endl;

}
