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

class Simulator {
public:
  Simulator () {
    this->fileName = "";
  }

  void setFileName (std::string file);
  std::vector<int> split(std::string str, char delimiter);
  std::string getFileName ();
  void parse (std::string line);

private:
  std::string fileName;
};
