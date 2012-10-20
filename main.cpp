/*
 *  Verexa's Word List Generator
 *  
 *  Please read the accompanying LICENSE file
 */

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "wordgen.h"

using namespace std;

string lower = "abcdefghijklmnopqrstuvwxyz", upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", numbers = "1234567890", special = "_-+=!$%?*()^@#?/\\{}[]~";

// Main function
int main(int argc, char* argv[]){
  printf("  Verexa's Word List Generator\n\n");

  int max_limit, min_limit;
  string list;
    
  // Parse command line input
  for(int a = 0; a < argc; a++){
    string opts = argv[a], opt = "", val = "", pch = "";

    for(int x = 0; x < opts.size(); x++){
      if(opts.at(x) == ':'){
        for(int y = 0; y < x; y++){
          opt += opts[y];
        }

        for(int z = x + 1; z < opts.size(); z++){
          val += opts[z];
        }

        break;
      }
    }

    if(opt == "min") min_limit = atoi(val.c_str());
    else if(opt == "max") max_limit = atoi(val.c_str());
    else if(opt == "list"){
      for(int i = 0; i < val.size(); i++){
        pch = val[i];

        if(pch == "u") list += upper;
        else if(pch == "l") list += lower;
        else if(pch == "n") list += numbers;
        else if(pch == "s") list += special;
      }
    } 
  }

  if(max_limit > 0 && min_limit > 0 && min_limit <= max_limit && list.size() != 0){
    printf("  Choice of Letters Size: %i\n\n  Generating Word List...\n", list.size());

    WordGen gen(max_limit, min_limit, list);
    
    long double on = 0, total = 0;
    int cur = 0;
    
    // Clock timing variables
    clock_t start, now, then;
    double final;

    for(int a = max_limit; a >= min_limit; a--)
      total += pow((double)list.size(), a);
    
    // Run the program
    start = clock();
    then = start;
    now = start;

    string str = gen.next();
    
    while(!str.empty()){
      on++;

      if(cur != gen.current || (double(now - then) / CLOCKS_PER_SEC) >= 2){
        printf("  %i W: %.0Lf of %.0Lf\n", gen.current, on, total);
        then = now;
        cur = gen.current;
      }

      str = gen.next();
      now = clock();
    }
  
    final = (double(now - start) / CLOCKS_PER_SEC);
 
    printf("  Completed Word List Generation!\n\n  Time Taken: %.2lfs\n", final);
  }
  else{
    printf("  Usage: %s [opt]:[val] ...\n\n  [opt]     [val]\n   max      e.g. 6\n   min      e.g. 3\n   list     e.g. lu (l = lowercase, u = uppercase, n = numbers, s = symbols)\n", argv[0]);
  }
}
