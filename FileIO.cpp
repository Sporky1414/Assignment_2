/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include "FileIO.h"

//Default constructor: takes in user input itself.
FileIO::FileIO() {
  //Gets preliminary file path from user.
  inputFilePath = getInputFilePathFromUser();

  //Loops until the inputFilePath is valid.
  while(true) {
    //Attempts to setup the file reader.
    input.open(inputFilePath);

    //If the file input reader works/sees the file exists, it will move on to check the validity of it.
    if(!input.fail()) {
      //Checks if the filepath given by the user leads to a file with the valid format. Breaks loop if it does.
      if(checkInputFileValidity()) {
        break;
      } else {
        //If the file given does not follow the correct file format, the input will close to be prepared for a new file.
        //The user must then try again and the while loop will continue.
        input.close();
        cout << "ERROR: File entered is not the correct format. Please try again with a different file." << endl;
        inputFilePath = getInputFilePathFromUser();
      }
    } else {
      //The file path entered by the user is not a valid file path. User is alerted of this and has to try again.
      input.close();
      cout << "ERROR: Invalid file path. Please try again." << endl;
      inputFilePath = getInputFilePathFromUser();
    }
  }

  //Gets preliminary output file name from user.
  outputFileName = getOutputFileNameFromUser();
  //Loops until outputFileName is valid.
  while(true) {
    //Adds the ".out" extension to the output file name.
    outputFileName = outputFileName + ".out";

    //Attempts to create the output file.
    output.open(outputFileName);
    if(!output.fail()) {
      //If the output file is created, the loop breaks.
      break;
    } else {
      //If the output file is not created because of a bad name, the user will try again.
      output.close();
      cout << "ERROR: Invalid file name entered. Please try again." << endl;
      outputFileName = getOutputFileNameFromUser();
    }
  }
}

//Constructor: Preliminary input file path and output name given.
FileIO::FileIO(string newInputFilePath, string newOutputFileName) {
  //If the input file path  given is "null", the input of this file class will not be used, so no validity check needed.
  if(newInputFilePath.compare("null") != 0) {
    //Loops until a valid file path is given.
    while(true) {
      //Attempts to setup the input stream.
      input.open(newInputFilePath);
      //Checks if the filepath leads to a valid file.
      if(!input.fail()) {
        //If the input is good, file format of the input file is checked.
        if(checkInputFileValidity()) {
          //Loop breaks if the given file matches the correct file format/layout.
          break;
        } else {
          //File does not meet format criteria. Input is reset and the user is told as such and has to try again.
          input.close();
          cout << "ERROR: File entered is not the correct format. Please try again with a different file." << endl;
          newInputFilePath = getInputFilePathFromUser();
        }
      } else {
        //The file path given does not lead to a valid file. Input is reset and the user is told to try again.
        input.close();
        cout << "ERROR: Invalid file path. Please try again." << endl;
        newInputFilePath = getInputFilePathFromUser();
      }
    }
    //Sets the global inputFilePath to the valid file path from the user.
    inputFilePath = newInputFilePath;
  } else {
    //If no file is being read, the input file path is set to null.
    inputFilePath = "null";
  }

  //Checks if the output file name is "null". If it is, there will be no file outputting, so no need to error check the file.
  if(newOutputFileName.compare("null") != 0) {
    //Loops until the output file name is valid.
    while(true) {
      //Adds the ".out" extension to the user-provided file name.
      newOutputFileName = newOutputFileName + ".out";

      //Attempts to create the output file.
      output.open(newOutputFileName);
      if(!output.fail()) {
        //Loop ends if the output stream successfully creates the output file.
        break;
      } else {
        //Output stream was unable to create the file using this name. It is reset and the user has to try again.
        output.close();
        cout << "ERROR: Invalid file name entered. Please try again." << endl;
        outputFileName = getOutputFileNameFromUser();
      }
    }
  } else {
    //If no file is being outptutted, the output file is set to null.
    outputFileName = "null";
  }
}

//Destructor: Closes the input/output streams (should they be in use.)
FileIO::~FileIO() {
  if(input.is_open()) {
    input.close();
  }
  if(output.is_open()) {
    output.close();
  }
}

//Reads the next line of the input file.
string FileIO::readNextLine() {
  string tempString = "";
  input >> tempString;
  return tempString;
}

//Returns if there is more data in the file to read.
bool FileIO::inputHasDataLeft() {
  return !input.eof();
}

//Writes the argument string to the output file.
void FileIO::writeData(string data) {
  output << data << endl;
}

//Takes in the input file path from the user. It is not error checked in this method.
string FileIO::getInputFilePathFromUser() {
  cout << "Enter File Path for Input." << endl;
  string tempPath = "";
  cin >> tempPath;
  return tempPath;
}

//Takes in the output file name from the user. It is not error checked in this method.
string FileIO::getOutputFileNameFromUser() {
  cout << "Enter name of the output file. If your file name is already in use, it will be overwritten should it also have the \".out\" extension." << endl;
  string tempPath = "";
  cin >> tempPath;
  return tempPath;
}

//Checks if the file connected to the input stream is in the correct format.
bool FileIO::checkInputFileValidity() {
  //Stores the current place the file reader is at so it can go back to it should the file be valid.
  streampos firstPos = input.tellg();

  //Reads the first line of the file.
  string tempString = readNextLine();

  //Checks if the first line of the file is a positive integer (height)
  int tempHeight = 0;
  if(checkIfStringIsNumber(tempString)) {
    //If the first line is a number, it is converted from a string to an int and checked to ensure it is a valid height (not less than 1).
    stringstream stringToNum(tempString);
    stringToNum >> tempHeight;
    if(tempHeight <= 1) {
      return false;
    }
  }
  //Reads the second line of the file.
  tempString = readNextLine();

  //Checks if the second line of the file is a positive integer (width)
  int tempWidth = 0;
  if(checkIfStringIsNumber(tempString)) {
    //If the second line is a number, it is converted from a string to an int and checked to ensure it is a valid width (not less than 1).
    stringstream stringToNum(tempString);
    stringToNum >> tempWidth;
    if(tempWidth <= 1) {
      return false;
    }
  }

  /*
    Checks to ensure rest of file is a 2D grid of only X's and -'s
  */
  //Counts number of loops. Used to check height of grid on file to the one stored earlier.
  int loopCounter = 0;
  //Loops until full file has been read.
  while(inputHasDataLeft()) {
    //Checks to see if each line is the same length as the width of the 2D array. If it is not, the file format is incorrect and false is returned.
    tempString = readNextLine();
    if(tempString.length() != tempWidth) {
      return false;
    }

    //Increments number of rows
    ++loopCounter;

    //Checks if the line has only X's and -'s. False is returned if any other character appears.
    for(int i = 0; i < tempString.length(); ++i) {
      if(tempString[i] != '-' && tempString[i] != 'X') {
        return false;
      }
    }
  }
  //If the number of rows in the file checked does not match the height set by the file at the beginning, the file is in the wrong format (false is returned)
  if(loopCounter != tempHeight) {
    return false;
  }
  //File is in the valid format. Pointer is reset to the beginning and true is returned.
  input.seekg(firstPos);
  return true;
}

//Checks if the argument string can be converted to an integer.
bool FileIO::checkIfStringIsNumber(string tempString) {
  //Empty strings automatically return false.
  if(tempString.length() < 1) {
    return false;
  }

  //Checks if each character in a string is a digit. If it is not, false is returned.
  for(int i = 0; i < tempString.length(); ++i) {
    if(!isdigit(tempString[i])) {
      return false;
    }
  }
  //tempString is a number, true is returned.
  return true;
}

//Returns true if either the input stream or output stream are in use.
bool FileIO::isNeeded() {
  if(!input.is_open() && !output.is_open()) {
    return false;
  } else {
    return true;
  }
}
