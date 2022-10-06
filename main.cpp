#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "ArgumentManager.h"
#include "LinkedList.h"
using namespace std;

string extractCommands(ifstream& inFile);

int main(int argc, char* argv[]) {
  
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ifstream command(am.get("command"));
  ofstream output(am.get("output"));

  string inputCommand;
  getline(input, inputCommand);
  LinkedList outList;

  string str;
  while (getline(input, str)){
    if (!str.empty() && inputCommand == "Beginning"){
      outList.addBegin(str);
    }
    else if (!str.empty() && (inputCommand == "End"|| inputCommand == "Alphabetically" || inputCommand == "Length")){
      outList.add(str);
    }
  }
  if (inputCommand == "Alphabetically"){
    outList.sort_by_alpha();
  } 
  else if (inputCommand == "Length"){
    outList.sort_by_length();
  }
  //outList.print();

  
  string commandLine, cdata;
  while (getline(command, commandLine)){
    if (commandLine.size() == 0)
      continue;
    //cout << command << endl;
    if (commandLine.find("Add") != string::npos)
    {
      string index = commandLine.substr(commandLine.find('(') + 1, (commandLine.find(')') - commandLine.find('(')) - 1);
      cdata = commandLine.substr(commandLine.find('[') + 1, (commandLine.find(']') - commandLine.find('[')) - 1);
      
      if (stoi(index) <= outList.getSize()) {
        //cout << "LAST" << endl;
        //cout << indexstr << endl << cdata << endl;
        
        outList.add_by_index(stoi(index), cdata);
      }
    }
    else if (commandLine.find("Remove") != string::npos)
    {
      cdata = commandLine.substr(commandLine.find('[') + 1, (commandLine.find(']') - commandLine.find('[')) - 1);
      //cout << cdata << endl;
      
      outList.remove(cdata);
    }
    else if (commandLine.find("Sort") != string::npos)
    {
      //cout << commandLine << endl;
      if (commandLine.find("length") != string::npos)
        outList.sort_by_length();
      else if (commandLine.find("alphabetically") != string::npos)
        outList.sort_by_alpha();
      //cout << "sorted" << endl;
    }
  }

  output << outList.toString();
  
  
}


/*
x. extract input file

x. check how to add strings into linked list
  - alphabetically: sort by letters
  - length: get string length from shortest to longest
  - beginning: add current string to the front (which current?)
  - end: add current string to the end (which current?)
*don't add empty lines or duplicates

3. extract command file
  - add: add string following the index
    + if out of bound, ditch
    + no duplicates
    + the number (3) is the actual index, meaning the size is 4 (0,1,2,3)
  - remove:
    + sentences contains the string will get removed
  - sort: either alphabetically or length

4. output
*/


