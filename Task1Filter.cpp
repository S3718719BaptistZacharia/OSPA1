#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <unistd.h>

using namespace std;

/* cleans a dirty file and filter out words of length 3-15,
   duplicates are removed and file is shuffled and the
   result is output to the provided clean file */

void TaskFilter(string dirtyFileName, string cleanFileName){
  // stream vars to be converted to char arrays for dirty and clean filenames
  ostringstream dFile, cFile;
  dFile << dirtyFileName;
  cFile << cleanFileName;
  string dfStr = dFile.str(), 
         cfStr = cFile.str();

  const char* dChar = dfStr.c_str();
  const char* cChar = cfStr.c_str();

  cout << "*** cleaning the dirty file ***\n";
  // print return value of the execl
  cerr << execl( "/bin/sh", "sh", "Task1.sh", dChar, cChar, (char*)NULL);
}

int main(int argc, char const *argv[]){ 
  // check if the passed args count is no more than 3 or less than 0
  if (argc >= 0 && argc <= 3){
    // get file names from command args
    string dirtyFileName = argv[1];
    string cleanFileName = argv[2];
    
    TaskFilter(dirtyFileName, cleanFileName);
  }

  return 0;
}
