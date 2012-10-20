#ifndef WORDGEN_HEADER
#define WORDGEN_HEADER

/*
 *  Verexa's Word List Generator 
 *  
 *  Please read the accompanying LICENSE file
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
