#ifndef WORDGEN_HEADER
#define WORDGEN_HEADER

/*
 *  Verexa's Word List Generator 
 *  
 *  Copyright (c) 2012, Verexa (Luke Fisher)
 *  All rights reserved.
 *  
 *  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *  
 *  1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string>
#include <vector>

/* 
 *  WordGen Class Definition
 */
class WordGen{
  private:
    std::vector<int> word;
    std::vector<bool> change;
    
    int min, counter;
    
    std::string list, output;
    
    void setup(int);
    void check();
    void build();
  
  public:
    int current;
    
    WordGen(int, int, std::string);
    
    std::string next();
    void run();
};

/* 
 *  WordGen Constructor
 */
WordGen::WordGen(int newmax, int newmin, std::string newlist){
  if(newmax > 0 && newmin > 0 && newmin <= newmax && newlist.size() != 0){
    min = newmin;
    counter = newmax;
    list = newlist;

    setup(counter);
  }
}

/* 
 *  WordGen run()
 */
void WordGen::run(){
  while(min <= counter){
    build();
    check();
  }
}

/* 
 *  WordGen next()
 */
std::string WordGen::next(){
  if(min <= counter){
    build();
    check();
    
    return output;
  }
  
  return "";
}

/* 
 *  WordGen setup()
 */
void WordGen::setup(int num){
  current = num;

  for(int a = 0; a < num; a++){
    word.push_back(0);
    change.push_back(false);
  }
}

/*
 *  WordGen check()
 */
void WordGen::check(){
  for(int i = counter - 1; 0 <= i; i--){
    if(change[i]){
      if(word[i] == list.size() - 1){
        if(i == 0){
          word.clear();
          change.clear();

          if(counter != min){
            counter--;
            setup(counter);
          }
          else{
            counter--;
          }
        }
        else{
          change[i - 1] = true;
          word[i] = 0;
          change[i] = false;
        }
      }
      else{
        word[i]++;
        change[i] = false;
      }
    }
  }
}

/* 
 *  WordGen build()
 */
void WordGen::build(){
  output.clear();
  for(int a = 0; a < word.size(); a++){
    output += list[word[a]];
  }
  
  change[counter - 1] = true;
}

#endif