#include "simulator.h"


int main(int argc, char* argv[]) {
  bool fileNameEntered = false;
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
      }
      else {
        std::cout << "No flag or file name was provided; existing simulation" << std::endl;
      }
    }
  }
}
