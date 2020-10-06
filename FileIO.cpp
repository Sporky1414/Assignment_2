#include "FileIO.h"

FileIO::FileIO() {
  newInputFilePath = getInputFilePathFromUser();
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

  newOutputFileName = getOutputFileNameFromUser();
  while(true) {
    newOutputFileName = newOutputFileName + ".out";
    output.open(newOutputFileName);
    if(!output.fail()) {
      break;
    } else {
      output.close();
      cout << "ERROR: Invalid file name entered. Please try again." << endl;
      newOutputFileName = getOutputFileNameFromUser();
    }
  }
}

FileIO::FileIO(string newInputFilePath, string newOutputFileName) {
  if(newInputFilePath.compare("null") !== 0) {
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
  }

  if(newOutputFileName.compare("null") !== 0) {
    while(true) {
      newOutputFileName = newOutputFileName + ".out";
      output.open(newOutputFileName);
      if(!output.fail()) {
        break;
      } else {
        output.close();
        cout << "ERROR: Invalid file name entered. Please try again." << endl;
        newOutputFileName = getOutputFileNameFromUser();
      }
    }
  }
}

FileIO::~FileIO() {
  if(input.isOpen()) {
    input.close();
  }
  if(output.isOpen()) {
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
  cout << "Enter name of the output file. Do not add an extension. If your file name is already in use, it will be overwritten should it also have the \".out\" extension." << endl;
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
    if(tempHeight == 0) {
      return false;
    }
  }

  tempString = readNextLine();
  int tempWidth = 0;
  if(checkIfStringIsNumber(tempString)) {
    stringstream stringToNum(tempString);
    stringToNum >> tempWidth;
    if(tempWidth == 0) {
      return false;
    }
  }

  int loopCounter = 0;
  while(inputHasDataLeft()) {
    tempString = readNextLine();
    if(tempString.length() !== tempWidth) {
      return false;
    }
    ++loopCounter;
    for(int i = 0; i < tempString.length(); ++i) {
      if(tempString[i] != "-" && tempString[i] != "X") {
        return false;
      }
    }
  }
  if(loopCounter !== height) {
    return false;
  }

  input.seekg(firstpos);
  delete firstPos;
  return true;
}

bool FileIO::checkIfStringIsNumber(string tempString) {
  if(tempString.length() < 1) {
    return false;
  }
  for(int i = 0; i < tempString.length(); ++i) {
    if(!tempString[i].isDigit()) {
      return false;
    }
  }
  return true;
}

bool FileIO::isNeeded() {
  if(!input.isOpen() && !output.isOpen()) {
    return false;
  } else {
    return true;
  }
}
