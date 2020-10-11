/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class FileIO {
  public:
    //Constructor/Destructor
    FileIO();
    FileIO(string newInputFilePath, string newOutputFileName);
    ~FileIO();

    //Methods to read/write data.
    string readNextLine();
    void writeData(string data);

    //Method to check on status of the input file.
    bool inputHasDataLeft();

    //Method to determine if the string passed through is an integer.
    bool checkIfStringIsNumber(string tempString);

  private:
    //Gets the file path/name from the user for both the input and output files.
    string getInputFilePathFromUser();
    string getOutputFileNameFromUser();

    //Determines if the input file passed in by the user is valid.
    bool checkInputFileValidity();

    //Checks if either the input or output streams are in use.
    bool isNeeded();

    //Strings containing the file path of the input and name of the output file.
    string inputFilePath;
    string outputFileName;

    //Objects to take in data from a file and write to a file.
    ifstream input;
    ofstream output;
};
