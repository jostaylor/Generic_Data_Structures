#include <iostream>
#include "GenStack.h"
#include <fstream>


using namespace std;

/*
Errors that can occur
1. wrong closing delimiter is matched up with opening delimiter
2. extra opening delimiter(s)
3. extra closing delimiter(s)

*/

bool isFileClean(string filename);

int main(int agrc, char** argv){

  // Runs Syntax Checker function once intially
  bool good2go = isFileClean(argv[1]);

  // If the initial file had no delimiter errors
  while (good2go == true){
    int response = 0;
    cout << "Your file has correct syntax and no delimiter errors." << endl;
    cout << "Would you like to input another file?\n(1) Yes\n(2) No" << endl;
    cin >> response;
    // Ensures valid input
    while (!cin || response <= 0 || response >= 3){
      cin.clear();
      cin.ignore(999999, '\n');
      cout << "Please input a valid number for a response." << endl;
      cout << "Would you like to input another file?\n(1) Yes\n(2) No" << endl;
      cin >> response;
    }
    // User says YES and wants to input anoher file
    if (response == 1){
      string response1;
      cout << "Please input your filename with the extension included: " << endl;
      cin >> response1;
      good2go = isFileClean(response1);
    }
    // User says NO and wants to quit
    else if (response == 2){
      cout << "Okay, goodbye!" << endl;
      break;
    }
    // This shouldn't ever occur; just here for safety
    else{
      cout << "Something went wrong with your input. Please try again." << endl;
      exit(1);
    }
  }

  return 0;
}

bool isFileClean(string name_of_file){
  // declare variables
  string file_name = name_of_file;
  ifstream file;
  string line;
  string delimiterString = "[](){}";
  int line_count = 1;
  bool insideString = false;
  bool insideChar = false;
  file.open(file_name);
  GenStack<char>* delimiters = new GenStack<char>(20);

  if (file.is_open()){
    // iterates through file line by line
    while(getline(file, line)){
      // iterates through the line char by char
      for (int i = 0; i < line.size(); ++i){
        // check for quotations and comments
        // If quotation mark denoting string ---> second conditional makes sure its not like quotation right before it --> == '\"'
        if (line[i] == '\"' && line[i-1] != '\\' && insideChar != true){
          insideString = (insideString == true) ? false : true;
        }
        // Ignores line[i] if it is inside of a char ''
        if (line[i] == '\'' && line[i-1] != '\\' && insideString != true){
          insideChar = (insideChar == true) ? false : true;
        }

        // Checks for comment symbols: //, #, --
        if (line[i] == '/' && line[i-1] == '/' && insideString != true && insideChar != true){
          // comment type: // --> ignore rest of line
          i = line.size();
          continue;
        }
        if (line[i] == '#' && insideString != true && insideChar != true){
          // comment type: # --> ignore rest of line
          i = line.size();
          continue;
        }

        // also ensures char is not inside of a string or char
        else if (insideString == false && insideChar == false){

          // Looks to see if the char is in delimiterString variable
          int idx_found = delimiterString.find(line[i]);

          // char was found --> char is a delimiter
          if (idx_found != -1){
            // char is an opening delimiter --> add it to the stack
            if (idx_found % 2 == 0){
              delimiters->push(line[i]);
              //cout << "Char : " << line[i] << " pushed. Line" << line_count <<": " << endl;
              //cout << "stack size: " << delimiters->top << endl;
            }

            // char is a closing delimiter
            else{

              // declare variable
              char top_of_stack = delimiters->peek();

              // If delimiter stack is empty --> then there is a closing delimiter without an opening one --> ERROR
              if (delimiters->isEmpty()){
                cout << "Error - line " << line_count << ": expected declaration before \'" << line[i] << "\' token" << endl;
                exit(1);
              }

              // If the top of the stack has the correctly matching delimiter --> good to go --> remove opening delimiter from stack
              if (top_of_stack == delimiterString[idx_found-1]){
                char top_of_stack = delimiters->pop();
                //cout << "Char : " << line[i] << " removed: " << top_of_stack << "Line" << line_count <<": " << endl;
                //cout << "stack size: " << delimiters->top << endl;
              }

              // the delimiter at the top of the stack does NOT match the given char --> ERROR
              else{
                // Grabs from expected delimiter from the delimiterString variable
                int expected_delimiter_index = delimiterString.find(top_of_stack);
                char expected_delimiter = delimiterString[expected_delimiter_index + 1];
                // Prints out error
                cout << "Error - line " << line_count << ": expected " << expected_delimiter << " and found " << delimiterString[idx_found] << endl;
                exit(1);
              }
            }
          }
        }
      }
      // increments line_count to keep track of LINE NUMBER
      line_count++;
    }
    // File has completed iteration

    // If delimiter stack still has openers in it --> ERROR
    if (!delimiters->isEmpty()){
      // Grabs expected delimiter from the delimiterString variable
      char top_of_stack = delimiters->peek();
      int expected_delimiter_index = delimiterString.find(top_of_stack);
      char expected_delimiter = delimiterString[expected_delimiter_index+1];
      // Prints out error
      cout << "Error: reached end of file; missing " << string(1, expected_delimiter) << ". Stack size: " << delimiters->top << endl;
      exit(1);
    }
  }

  // File could not be opened for some reason --> ERROR --> exit program
  else{
    cout << "File could not be opened and read successfully" << endl;
    cout << "Please input file as a command line argument" << endl;
    cout << "Example usage: \' ./a.out filename.cpp\'" << endl;
    exit(1);
  }

  delete delimiters;

  return true;
}
