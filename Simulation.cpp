#include "Simulation.h"

Simulation::Simulation() {
  userResponse = "";
  fileBeingInputted = false;
  heightFromUser = 0;
  widthFromUser = 0;
  popDensityFromUser = 0;
  fileBeingOutputted = false;
  setupSimulation();
}

Simulation::~Simulation() {

}

void Simulation::run() {
  string returnString = "";
  returnString += "0";
  returnString += "\n";
  returnString += mainGrid->gridToString() + "\n";
  cout << returnString << "Press enter to start!" << endl;
  getline(cin, userResponse);
  if(fileBeingOutputted) {
    fileHandler->writeData(returnString);
  }
  returnString = "";
  cin >> userResponse;
  int generationCounter = 1;
  while(true) {
    returnString += "Generation Number: " + to_string(generationCounter) +  "\n";
    prevGrid = new Grid(mainGrid);
    mainGrid = new Grid(mode->createNewGridFromOldGrid(prevGrid));
    returnString += mainGrid->gridToString();
    if(mainGrid->gridToString().compare(prevGrid->gridToString()) == 0) {
      cout << "Grid is stable." << endl;
      if(fileBeingOutputted) {
        fileHandler->writeData("Grid is stable.");
      }
      break;
    }
    if(mainGrid->isEmpty()) {
      cout << "Next generation grid is empty." << endl;
      if(fileBeingOutputted) {
        fileHandler->writeData("Next generation grid is empty.");
      }
      break;
    }
    if(fileBeingOutputted) {
      fileHandler->writeData(returnString);
    }
    cout << returnString << endl;
    returnString = "";
    if(pauseBetweenGenerations) {
      cout << "Generation complete. Press enter to go to the next one." << endl;
      getline(cin, userResponse);
    }
    ++generationCounter;
  }
  cout << "Simulation complete. Press enter to exit to the program." << endl;
  getline(cin, userResponse);
  
  delete mainGrid;
  delete prevGrid;
}

void Simulation::setupSimulation() {
  while(true) {
    cout << "Do you want to input data through a file or with numbers? Type 1 for file and 2 for numbers." << endl;
    userResponse = "";
    cin >> userResponse;
    if(userResponse[0] == '1') {
      fileBeingInputted = true;
      break;
    } else if (userResponse[0] == '2') {
      fileBeingInputted = false;
      break;
    } else {
      cout << "Invalid response. Please try again." << endl;
    }
  }

  while(true) {
    cout << "Do you want to output to a file? Type 'y' for yes and 'n' for no." << endl;
    userResponse = "";
    cin >> userResponse;
    if(userResponse[0] == 'y' || userResponse[0] == 'Y') {
      fileBeingOutputted = true;
      break;
    } else if (userResponse[0] == 'n' || userResponse[0] == 'N') {
      fileBeingOutputted = false;
      break;
    } else {
      cout << "Invalid response. Please try again." << endl;
    }
  }

  if(!fileBeingInputted) {
    getGridFromUser();
  }
  setupFile();
  if(fileBeingInputted) {
    mainGrid = new Grid(fileHandler);
  }

  gameModeSetup();

  while(true) {
    cout << "Do you want to pause between generations? Type 'y' for yes and 'n' for no. If you pause between generations, you must hit enter to move to the next one. If you do not, the simulation will run without interruption until it stabilizes or all the cells die." << endl;
    userResponse = "";
    cin >> userResponse;
    if(userResponse[0] == 'y' || userResponse[0] == 'Y') {
      pauseBetweenGenerations = true;
      break;
    } else if (userResponse[0] == 'n' || userResponse[0] == 'N') {
      pauseBetweenGenerations = false;
      break;
    } else {
      cout << "Invalid response. Please try again." << endl;
    }
  }
}

void Simulation::getGridFromUser() {
  FileIO* tempFile = new FileIO("null", "null");

  while(true) {
    cout << "Enter the height of your grid." << endl;
    userResponse = "";
    cin >> userResponse;
    if(tempFile->checkIfStringIsNumber(userResponse)) {
      break;
    } else {
      cout << "You did not input a number. Please try again." << endl;
    }
  }
  stringstream stringToNum(userResponse);
  stringToNum >> heightFromUser;
  if(heightFromUser < 2) {
    cout << "Your height is less than 2, which is impossible. Defaulting to 2." << endl;
    heightFromUser = 2;
  }

  while(true) {
    cout << "Enter the width of your grid." << endl;
    userResponse = "";
    cin >> userResponse;
    if(tempFile->checkIfStringIsNumber(userResponse)) {
      break;
    } else {
      cout << "You did not input a number. Please try again." << endl;
    }
  }
  stringstream stringToNum2(userResponse);
  stringToNum2 >> widthFromUser;
  if(widthFromUser < 2) {
    cout << "Your width is less than 2, which is impossible. Defaulting to 2." << endl;
    widthFromUser = 2;
  }

  bool decimalPointFound = false;
  bool validResponse = false;
  while(true) {
    cout << "Enter the population density (between 0 and 1) to use." << endl;
    userResponse = "";
    cin >> userResponse;
    decimalPointFound = false;
    validResponse = true;
    for(int i = 0; i < userResponse.length(); i++) {
      if((userResponse[i] >= '0' && userResponse[i] <= '9') || (userResponse[i] == '.' && !decimalPointFound)) {
        if(userResponse[i] == '.') {
          decimalPointFound = true;
        }
      } else {
        validResponse = false;
        break;
      }
    }
    if(!validResponse) {
      cout << "Invalid answer. Please try again." << endl;
    } else {
      popDensityFromUser = stod(userResponse);
      if(popDensityFromUser <= 0 || popDensityFromUser > 1) {
        cout << "The number you inputted is not between 0 and 1. Please try again." << endl;
      } else {
        break;
      }
    }
  }
  delete tempFile;
  mainGrid = new Grid(heightFromUser, widthFromUser, popDensityFromUser);
}

void Simulation::setupFile() {
  if(fileBeingInputted && fileBeingOutputted) {
    fileHandler = new FileIO();
  } else if (fileBeingInputted) {
    while(true) {
      cout << "Enter File Path for Input." << endl;
      userResponse = "";
      cin >> userResponse;
      if(userResponse.compare("null") == 0) {
        cout << "\"null\" is not a valid file name. Please try again." << endl;
      } else {
        fileHandler = new FileIO (userResponse, "null");
        break;
      }
    }
  } else if (fileBeingOutputted) {
    while(true) {
      cout << "Enter name of the output file. If your file name is already in use, it will be overwritten should it also have the \".out\" extension." << endl;
      userResponse = "";
      cin >> userResponse;
      if(userResponse.compare("null") == 0) {
        cout << "\"null\" is not a valid file name. Please try again." << endl;
      } else {
        fileHandler = new FileIO ("null", userResponse);
        break;
      }
    }
  } else {
    fileHandler = new FileIO("null", "null");
  }
}

void Simulation::gameModeSetup() {
  while(true) {
    cout << "Which game mode are you using? Type 1 for Classic, 2 for Doughnut, and 3 for Mirror." << endl;
    userResponse = "";
    cin >> userResponse;
    if(userResponse[0] == '1') {
      mode = &classic;
      break;
    } else if (userResponse[0] == '2') {
      mode = &doughnut;
      break;
    } else if (userResponse[0] == '3') {
      mode = &mirror;
      break;
    } else {
      cout << "Invalid response. Please try again." << endl;
    }
  }
}
