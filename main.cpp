#include "Cell.h"
#include "Grid.h"
#include "FileIO.h"

using namespace std;

int main(int argc, char** argv) {
  Grid grid* = null;

  string response = "";
  bool withFile = false;
  bool outputToFile = false;

  while(true) {
    cout << "Do you want to input data through a file or with numbers? Type 1 for file and 2 for numbers." << endl;
    response = "";
    cin >> response;
    if(response[0] == '1') {
      withFile = true;
      break;
    } else if (response[0] == '2') {
      withFile = false;
      break;
    } else {
      cout << "Invalid response. Please try again." << endl;
    }
  }

  while(true) {
    cout << "Do you want to output to a file? Type 'y' for yes and 'n' for no." << endl;
    response = "";
    cin >> response;
    if(response[0] == 'y' || response[0] == 'Y') {
      outputToFile = true;
      break;
    } else if (response[0] == 'n' || response[0] == 'N') {
      outputToFile = false;
      break;
    } else {
      cout << "Invalid response. Please try again." << endl;
    }
  }

  FileIO file*;
  if(withFile && outputToFile) {
    file = new FileIO();
  } else if (withFile && !outputToFile) {
    cout << "Enter File Path for Input." << endl;
    response = "";
    cin >> response;
    file = new FileIO(response, "null");
  } else if (!withFile && outputToFile){
    cout << "Enter name of the output file. Do not add an extension. If your file name is already in use, it will be overwritten should it also have the \".out\" extension." << endl;
    response = "";
    cin >> response;
    file = new FileIO("null", response);
  } else {
    file = new File("null", "null");
  }

  if(withFile) {
    grid* = new Grid(file);
  } else {
    while(true) {
      cout << "Enter the height of your grid." << endl;
      response = "";
      cin >> response;
      if(file.checkIfStringIsNumber(response)) {
        break;
      } else {
        cout << "You did not input a number. Please try again." << endl;
      }
    }
    stringstream stringToNum(response);
    int tempHeight;
    stringToNum >> tempHeight;

    while(true) {
      cout << "Enter the width of your grid." << endl;
      response = "";
      cin >> response;
      if(file.checkIfStringIsNumber(response)) {
        break;
      } else {
        cout << "You did not input a number. Please try again." << endl;
      }
    }
    stringToNum(response);
    int tempWidth;
    stringToNum >> tempWidth;

    bool decimalPointFound = false;
    bool validResponse = false;
    double popDensity = 0;
    while(true) {
      cout << "Enter the population density (between 0 and 1) to use." << endl;
      response = "";
      cin >> response;
      decimalPointFound = false;
      validResponse = true;
      for(int i = 0; i < response.length(); i++) {
        if((response[i] >= '0' && response[i] <= '9') || (response[i] == "." && !decimalPointFound)) {
          if(response[i] == ".") {
            decimalPointFound = true;
          }
        } else {
          validResponse = false;
          break;
        }
      }
      if(!validResponse) {
        cout << "Invalid answer. Please try again."
      } else {
        popDensity = stod(response);
        if(popDensity <= 0 || popDensity > 1) {
          cout << "The number you inputted is not between 0 and 1. Please try again." << endl;
        } else {
          break;
        }
      }
    }

    grid* = new Grid(tempHeight, tempWidth, popDensity);

    cout << "\n" << "\n" << endl;
    cout << grid.gridToString() << endl;

    if(outputToFile) {
      file.writeData(grid.gridToString());
    }

    delete file;
    delete grid;
    return 0;
  }
}
