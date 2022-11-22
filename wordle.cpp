// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void combos(
    std::string& in,
    std::multiset<char> floating_set,
    const std::set<std::string>& dict,
    std::set<std::string>& wordle_set,
    unsigned int depth);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    std::string in_temp = in;
    std::multiset<char> floating_set; // Make a set of floating letters
    for(unsigned int i = 0; i < floating.size(); i++){
      floating_set.insert(floating[i]);
    }
    std::set<std::string> wordle_set;
    combos(in_temp, floating_set, dict, wordle_set, 0);

    return wordle_set;
}



// Define any helper functions here
// std::set<std::string> combos(std::string& raw_word, int n, std::vector&<std::string> my_vec){
void combos(
    std::string& in,
    std::multiset<char> floating_set,
    const std::set<std::string>& dict,
    std::set<std::string>& wordle_set,
    unsigned int depth)
{
  if(depth == in.size()){ // BC
    if(dict.find(in) != dict.end() && floating_set.empty()){ // if valid word
      // Check if it is in dictionary and contains all floating words (floating_set should be empty)
      wordle_set.insert(in);
    }
    return;
  }
  else{
    if(in[depth] != '-'){ // If letter is a fixed letter
      combos(in, floating_set, dict, wordle_set, depth + 1); // Go to next letter index
    }
    else{
      std::multiset<char>::iterator it;
      for(it = floating_set.begin(); it != floating_set.end(); ++it){ //    domain is floating letters
        in[depth] = *it;

        // Remove floating letter when passed in as a parameter for next recursion
        std::multiset<char> floating_set_temp = floating_set;
        floating_set_temp.erase(floating_set_temp.find(*it));  // Erase 1 element (in case of duplicate floats)
        combos(in, floating_set_temp, dict, wordle_set, depth + 1);

        in[depth] = '-'; // Turn back into a '-' for next letter in the for-loop
      }
      int fixed_counter = 0;
      for(unsigned int i = depth + 1; i < in.size(); i++){
        if(in[i] != '-') fixed_counter++;
      }
      if(in.size() - depth > floating_set.size() + fixed_counter){ // in.size() - depth = blanks left, whole if-statement checks if I have more blanks than floating characters left
        for(char let = 'a'; let <= 'z'; let++){ //    let (letter): a - z
          in[depth] = let;
          if(floating_set.find(let) != floating_set.end()){ // If letter is a floating letter
            // Remove floating letter when passed in as a parameter for next recursion
            std::multiset<char> floating_set_temp = floating_set;
            floating_set_temp.erase(floating_set_temp.find(let)); // Erase 1 element (in case of duplicate floats)
            combos(in, floating_set_temp, dict, wordle_set, depth + 1);
          }
          else{ // Letter is not a floating letter
            combos(in, floating_set, dict, wordle_set, depth + 1);
          }
          in[depth] = '-'; // Turn back into a '-' for next letter in the for-loop
        }
      }
    }
  }
}

