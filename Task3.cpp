#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <list>
#include <unistd.h>
#include "types.h"

using namespace std;


void map3(string cleanFileName){
    // split the all words lengths in the string array to their own file
    cout << "*** Map3() slitting data on word lengths ***\n";

     // for each word length from the clean file, slit accordingly and save to own file
    FILE *pipe_open;
    for (int i = MINCOUNT; i <= MAXCOUNT; i++){
        string commandStr = "awk '{if (length($0) ==" + to_string(i) + ") print}' " + cleanFileName + "> T3words" + to_string(i) + ".txt";

        const char * command = commandStr.c_str();
        // open a pipe in write mode (w) to run the command above. exit when error occurs
        if ((pipe_open = popen(command, "w")) == NULL){
            perror("popen error in map3(). splitting clean file");
            exit(EXIT_FAILURE);
        }
    }
    
    // close pipe
    pclose(pipe_open);
    cout << "*** Done processing!!! ***\n";
    cout << "*** Map3() Done splitting ***\n";
    // sort each file  with fork() on the 3rd character 
    cout << "*** Sorting Files for each word lenghts 3 - 15 on 3rd character ***\n";
    
    int id = fork();
    if (id > 0){
        // open each file and sort by the 3rd letter and save to it's own file
        for (int i = MINCOUNT; i <= MAXCOUNT; i++){
            string commandStr = "sort -k1.3,1.15 T3words"+ to_string(i) + ".txt > T3words"
                                + to_string(i) + "sorted.txt";

            const char * command = commandStr.c_str();
            // open a pipe in write mode (w) to run the command above. exit when error occurs
            if ((pipe_open = popen(command, "w")) == NULL){
                perror("popen error in map3(). sort on 3rd letter");
                exit(1);
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

void reduce3(){
    cout << "*** Merging Files for each word lenghts 3 - 15 ***\n";
    // for each word length from the words sorted, merge sort them
    FILE *pipe_open;
    string commandStr = "cat ";
    for (int i = MINCOUNT; i <= MAXCOUNT; i++){
        commandStr += "T3words" + to_string(i) + "sorted.txt ";
    }
    // open a pipe in write mode (w) to run the command above. exit when error occurs
    commandStr += "| sort > T3mergedFile.txt";
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
        const char * cleanFileName = argv[1];
        // load the clean file data to the global string array
        map3(cleanFileName);
        reduce3();
    }

    return 0;
}
