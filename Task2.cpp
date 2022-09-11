#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <unistd.h>

#include "types.h"

using namespace std;

/* map2() to separate the words list into separate list with lengths 3-15
   map2() will use fork() to call sort to sort each file on 3rd letter
   result saved in it's own file   
*/

void map2(string cleanFilename){
    cout << "*** Processing File: splitting files for Each lenghts 3 - 15 ***\n";
    // for each word length from the clean file, slit accordingly and save to own file
    FILE *pipe_open;
    for (int i = MINCOUNT; i <= MAXCOUNT; i++){
        string commandStr = "awk '{if (length($0) ==" + to_string(i) + ") print}' "
                            + cleanFilename + "> T2words" + to_string(i) + ".txt";

        const char * command = commandStr.c_str();
        // open a pipe in write mode (w) to run the command above. exit when error occurs
        if ((pipe_open = popen(command, "w")) == NULL){
            perror("popen error in map2(). splitting clean file");
            exit(EXIT_FAILURE);
        }
    }
    
    // close pipe
    pclose(pipe_open);
    cout << "*** Done processing!!! ***\n";

    // sort each file  with fork() on the 3rd character 
    cout << "*** Sorting Files for each word lenghts 3 - 15 on 3rd character ***\n";
    
    int id = fork();

    if (id > 0){
        // open each file and sort by the 3rd letter and save to it's own file
        for (int i = MINCOUNT; i <= MAXCOUNT; i++){
            string commandStr = "sort -k1.3,1.15 T2words"+ to_string(i) + ".txt > T2words"
                                + to_string(i) + "sorted.txt";

            const char * command = commandStr.c_str();
            // open a pipe in write mode (w) to run the command above. exit when error occurs
            if ((pipe_open = popen(command, "w")) == NULL){
                perror("popen error in map2(). sort on 3rd letter");
                exit(EXIT_FAILURE);
            }
        }
        // close pipe
        pclose(pipe_open);
    } else {
        perror("Fork Result");
        exit(1);
    }
    cout << "*** Done Sorting!!! ***\n";
}

/* reduce() opens each of the 13 files to read 1 line at a time for each file
   writing the lowest sort order word from each file and reading the 
   next word from that file. ie. 13 to 1 merge sort
*/

void reduce(){
    cout << "*** Merging Files for each word lenghts 3 - 15 ***\n";
    // for each word length from the words sorted, merge sort them
    FILE *pipe_open;
    string commandStr = "cat ";
    for (int i = MINCOUNT; i <= MAXCOUNT; i++){
        commandStr += "T2words" + to_string(i) + "sorted.txt ";
    }
    // open a pipe in write mode (w) to run the command above. exit when error occurs
    commandStr += "| sort > T2mergedFile.txt";
    const char * command = commandStr.c_str();
    if ((pipe_open = popen(command, "w")) == NULL){
        perror("popen error in reduce()");
        exit(1);
    }
    
    // close pipe
    pclose(pipe_open);
    cout << "*** Done merging files!!! ***\n";
}

int main(int argc, char const *argv[]){ 
    // check if the passed args count is no more than 3 or less than 0
    if (argc >= 0 && argc <= 2){
        // get file names from command args
        string cleanFileName = argv[1];
        map2(cleanFileName);
        reduce();
    }
    return 0;
}
