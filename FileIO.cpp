#include "FileIO.h"

FileIO::FileIO() {
  inputFilePath = getInputFilePathFromUser();
  while(true) {
    input.open(inputFilePath);
    if(!input.fail()) {
      if(checkInputFileValidity()) {
        break;
      } else {
        input.close();
        cout << "ERROR: File entered is not the correct format. Please try again with a different file." << endl;
        inputFilePath = getInputFilePathFromUser();
      }
    } else {
      input.close();
      cout << "ERROR: Invalid file path. Please try again." << endl;
      inputFilePath = getInputFilePathFromUser();
    }
  }

  outputFileName = getOutputFileNameFromUser();
  while(true) {
    outputFileName = outputFileName + ".out";
    output.open(outputFileName);
    if(!output.fail()) {
      break;
    } else {
      output.close();
      cout << "ERROR: Invalid file name entered. Please try again." << endl;
      outputFileName = getOutputFileNameFromUser();
    }
  }
}

FileIO::FileIO(string newInputFilePath, string newOutputFileName) {
  if(newInputFilePath.compare("null") != 0) {
    while(true) {
      input.open(newInputFilePath);
      if(!input.fail()) {
        if(checkInputFileValidity()) {
          break;
        } else {
          input.close();
          cout << "ERROR: File entered is not the correct format. Please try again with a different file." << endl;
          newInputFilePath = getInputFilePathFromUser();
        }
      } else {
        input.close();
        cout << "ERROR: Invalid file path. Please try again." << endl;
        newInputFilePath = getInputFilePathFromUser();
      }
    }
    inputFilePath = newInputFilePath;
  } else {
    inputFilePath = "null";
  }

  if(newOutputFileName.compare("null") != 0) {
    while(true) {
      newOutputFileName = newOutputFileName + ".out";
      output.open(newOutputFileName);
      if(!output.fail()) {
        break;
      } else {
        output.close();
        cout << "ERROR: Invalid file name entered. Please try again." << endl;
        outputFileName = getOutputFileNameFromUser();
      }
    }
  } else {
    outputFileName = "null";
  }
}

FileIO::~FileIO() {
  if(input.is_open()) {
    input.close();
  }
  if(output.is_open()) {
    output.close();
  }
}

string FileIO::readNextLine() {
  string tempString = "";
  input >> tempString;
  return tempString;
}

bool FileIO::inputHasDataLeft() {
  return !input.eof();
}

void FileIO::writeData(string data) {
  output << data << endl;
}

string FileIO::getInputFilePathFromUser() {
  cout << "Enter File Path for Input." << endl;
  string tempPath = "";
  cin >> tempPath;
  return tempPath;
}

string FileIO::getOutputFileNameFromUser() {
  cout << "Enter name of the output file. If your file name is already in use, it will be overwritten should it also have the \".out\" extension." << endl;
  string tempPath = "";
  cin >> tempPath;
  return tempPath;
}

bool FileIO::checkInputFileValidity() {
  streampos firstPos = input.tellg();

  string tempString = readNextLine();
  int tempHeight = 0;
  if(checkIfStringIsNumber(tempString)) {
    stringstream stringToNum(tempString);
    stringToNum >> tempHeight;
    if(tempHeight <= 1) {
      return false;
    }
  }

  tempString = readNextLine();
  int tempWidth = 0;
  if(checkIfStringIsNumber(tempString)) {
    stringstream stringToNum(tempString);
    stringToNum >> tempWidth;
    if(tempWidth <= 1) {
      return false;
    }
  }

  int loopCounter = 0;
  while(inputHasDataLeft()) {
    tempString = readNextLine();
    if(tempString.length() != tempWidth) {
      return false;
    }
    ++loopCounter;
    for(int i = 0; i < tempString.length(); ++i) {
      if(tempString[i] != '-' && tempString[i] != 'X') {
        return false;
      }
    }
  }
  if(loopCounter != tempHeight) {
    return false;
  }

  input.seekg(firstPos);
  return true;
}

bool FileIO::checkIfStringIsNumber(string tempString) {
  if(tempString.length() < 1) {
    return false;
  }
  for(int i = 0; i < tempString.length(); ++i) {
    if(!isdigit(tempString[i])) {
      return false;
    }
  }
  return true;
}

bool FileIO::isNeeded() {
  if(!input.is_open() && !output.is_open()) {
    return false;
  } else {
    return true;
  }
}
