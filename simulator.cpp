#include "simulator.h"


int main(int argc, char* argv[]) {
  bool fileNameEntered = false;
  Simulator sim = Simulator();

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
      else if ( cmd.length() > 1 && cmd != "-h" && cmd != "--help" && cmd != "-a" && cmd != "--algorithm" && cmd != "-t" && cmd !=  "--per_thread" ) {
        // fileName string was provided
        std::cout << "File Name was provided" << std::endl;
        sim.setFileName(cmd);
        fileNameEntered = true;
      }
      else {
        std::cout << "No flag or file name was provided; existing simulation" << std::endl;
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
  sim.simulate();

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
  schedule.push_back(occurence);
}

// Main loop
void Simulator::simulate () {
  std::cout << schedule.at(0).at(0) << std::endl;
  for (int i = 0; i < schedule.size(); i++) {
    std::vector<int> temp = schedule.at(i);
    for (int j = 0; j < temp.size(); j++) {
      std::cout << temp.at(j);
    }
    std::cout << std::endl;
  }
}
