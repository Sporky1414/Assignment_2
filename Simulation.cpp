/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include "Simulation.h"

//Constructor: Sets up the simulation
Simulation::Simulation() {
  //Initalizes the user input variables and the file booleans
  userResponse = "";
  fileBeingInputted = false;
  heightFromUser = 0;
  widthFromUser = 0;
  popDensityFromUser = 0;
  fileBeingOutputted = false;

  //Rest of the setup is done in the setupSimulation method.
  setupSimulation();
}

//Destructor: Since simulation is not a pointer nor is it stored on the heap, a destructor is not used, since all the deleting is done at the end of the run method.
Simulation::~Simulation() {

}

//Runs the simulation
void Simulation::run() {
  //Creates a string to store each version of the grid as its created.
  string returnString = "";

  //Adds the original grid to the returnString.
  returnString += "0";
  returnString += "\n";
  returnString += mainGrid->gridToString() + "\n";

  //Prints the orignal grid and waits for the user to hit enter to start the simulation.
  cout << returnString << "Press enter to start!" << endl;
  cin.ignore();
  getline(cin, userResponse);

  //If there is a file being ouput, the returnString prints that data.
  if(fileBeingOutputted) {
    fileHandler->writeData(returnString);
  }
  //returnString is cleared.
  returnString = "";

  //Counter for each generation
  int generationCounter = 1;
  while(true) {
    //Puts a header in the returnString
    returnString += "Generation Number: " + to_string(generationCounter) +  "\n";

    //Copies the old grid to the prevGrid pointer.
    prevGrid = new Grid(mainGrid);
    //Creates a new grid,  using the createNewGridFromOldGrid method in the Game Mode base class.
    //The derived object the mode pointer points to determines how the neighbors are counted for this new grid.
    mainGrid = new Grid(mode->createNewGridFromOldGrid(prevGrid));

    //Puts the new grid in the returnString.
    returnString += mainGrid->gridToString();

    //Checks if the grid has changed between generations. If it has, it is stable
    if(mainGrid->gridToString().compare(prevGrid->gridToString()) == 0) {
      //Reports to user/outputs to file (if needed) that the grid is stable.
      cout << "Grid is stable." << endl;
      if(fileBeingOutputted) {
        fileHandler->writeData("Grid is stable.");
      }
      //Gets out of loop, since the simulation is over.
      break;
    }

    //Checks if the grid is empty.
    if(mainGrid->isEmpty()) {
      //If the grid is empty, it is reported to the user/outputted to the file if needed.
      cout << "Next generation grid is empty." << endl;
      if(fileBeingOutputted) {
        fileHandler->writeData("Next generation grid is empty.");
      }
      //Exits loop, since the simulation is complete.
      break;
    }

    //Outputs the data in returnString to the output file should it have been requested.
    if(fileBeingOutputted) {
      fileHandler->writeData(returnString);
    }

    //Outputs the data in returnString to the user.
    cout << returnString << endl;

    //Clears returnString
    returnString = "";

    //If a pause between generations was requested, the program waits for enter to be pressed before continuing.
    if(pauseBetweenGenerations) {
      cout << "Generation complete. Press enter to go to the next one." << endl;
      getline(cin, userResponse);
    }
    //The generation counter is increased.
    ++generationCounter;
  }
  //Tells user to hit enter to end the simulation.
  cout << "Simulation complete. Press enter to exit to the program." << endl;
  getline(cin, userResponse);

  //Deletes pointers.
  delete mainGrid;
  delete prevGrid;
  delete fileHandler;
}


//Sets up the simulation class.
void Simulation::setupSimulation() {
  //Checks if user is inputting data or the grid is coming in through a file.
  while(true) {
    cout << "Do you want to input data through a file or with numbers? Type 1 for file and 2 for numbers." << endl;
    userResponse = "";
    cin >> userResponse;
    //Checks user response for a 1 or 2 as the first character.
    if(userResponse[0] == '1') {
      //If the first character is one, a file is being inputted, so the boolean to do so is set to true and the loop breaks.
      fileBeingInputted = true;
      break;
    } else if (userResponse[0] == '2') {
      //If the first character is two, a file is not being inputted and the grid will be randomly generated with user data, so the fileBeingInputted is set to false. Loop then breaks.
      fileBeingInputted = false;
      break;
    } else {
      //The first character was not a 1 or 2, so the user has to try again.
      cout << "Invalid response. Please try again." << endl;
    }
  }

  //Checks if the user wants to output a file.
  while(true) {
    cout << "Do you want to output to a file? Type 'y' for yes and 'n' for no." << endl;
    userResponse = "";
    cin >> userResponse;
    //Checks user response for a Y/y or N/n as the first character.
    if(userResponse[0] == 'y' || userResponse[0] == 'Y') {
      //If a Y/y is found in the first character of the user response, a file is being outputted, so the boolean is set to true.
      fileBeingOutputted = true;
      break;
    } else if (userResponse[0] == 'n' || userResponse[0] == 'N') {
      //If a N/n is found in the first character of the user response, a file is not being output, so the boolean is set to false.
      fileBeingOutputted = false;
      break;
    } else {
      //If neither occurred, the user must try again to input something.
      cout << "Invalid response. Please try again." << endl;
    }
  }

  //If a file is not being used to create the grid, the getGridFromUser method is called to create the main grid.
  if(!fileBeingInputted) {
    getGridFromUser();
  }
  //The fileHandler is setup with setupFile().
  setupFile();

  //If a file is being inputted, the mainGrid is initialized using the newly intialized fileHandler.
  if(fileBeingInputted) {
    mainGrid = new Grid(fileHandler);
  }

  //The game mode is selected.
  gameModeSetup();

  //Checks if there will be a pause in between generations.
  while(true) {
    cout << "Do you want to pause between generations? Type 'y' for yes and 'n' for no. If you pause between generations, you must hit enter to move to the next one. If you do not, the simulation will run without interruption until it stabilizes or all the cells die." << endl;
    userResponse = "";
    cin >> userResponse;
    //Checks user response for a Y/y or N/n as the first character.
    if(userResponse[0] == 'y' || userResponse[0] == 'Y') {
      //If a Y/y is found in the first character of the user response, the pauseBetweenGenerations boolean is set to true.
      pauseBetweenGenerations = true;
      break;
    } else if (userResponse[0] == 'n' || userResponse[0] == 'N') {
      //If an N/n is found in the first character of the user response, the pauseBetweenGenerations boolean is set to false.
      pauseBetweenGenerations = false;
      break;
    } else {
      //The loop repeats if neither character was used, since it is incorrect.
      cout << "Invalid response. Please try again." << endl;
    }
  }
}

//Initalizes the mainGrid using data from the user.
void Simulation::getGridFromUser() {

  //Creates a temporary fileHandler with no file paths set for string checking.
  FileIO* tempFile = new FileIO("null", "null");

  //Gets height of the grid from the user.
  while(true) {
    cout << "Enter the height of your grid." << endl;
    userResponse = "";
    cin >> userResponse;
    //Checks if the user entered a number for the height
    if(tempFile->checkIfStringIsNumber(userResponse)) {
      break;
    } else {
      //If they did not, the user has to try again.
      cout << "You did not input a number. Please try again." << endl;
    }
  }
  //Converts the height string to an integer and stores it in heightFromUser. If the height given is less than 2, which is not feasible for this simulation, the height is defaulted to 2.
  stringstream stringToNum(userResponse);
  stringToNum >> heightFromUser;
  if(heightFromUser < 2) {
    cout << "Your height is less than 2, which is impossible. Defaulting to 2." << endl;
    heightFromUser = 2;
  }

  //Gets width of the grid from the user.
  while(true) {
    cout << "Enter the width of your grid." << endl;
    userResponse = "";
    cin >> userResponse;
    //Checks if the userResponse is a number for the width.
    if(tempFile->checkIfStringIsNumber(userResponse)) {
      break;
    } else {
      //Loop repeats if the user did not input a number.
      cout << "You did not input a number. Please try again." << endl;
    }
  }
  //Converts the width string to an integer and stores it in widthFromUser. If the width given is less than 2, which is not feasible for this simulation, the width is defaulted to 2.
  stringstream stringToNum2(userResponse);
  stringToNum2 >> widthFromUser;
  if(widthFromUser < 2) {
    cout << "Your width is less than 2, which is impossible. Defaulting to 2." << endl;
    widthFromUser = 2;
  }

  //Sets up booleans to validate the population density
  bool decimalPointFound = false;
  bool validResponse = true;
  //Gets population density from user.
  while(true) {
    cout << "Enter the population density (between 0 and 1) to use." << endl;
    userResponse = "";
    cin >> userResponse;
    //Iterates through the user response to check if it is a decimal number.
    for(int i = 0; i < userResponse.length(); i++) {
      //Checks if each character is a digit or, if one has not been found already, a decimal point.
      if((userResponse[i] >= '0' && userResponse[i] <= '9') || (userResponse[i] == '.' && !decimalPointFound)) {
        //If a decimal point is found, it is marked as having been found. If a second decimal point is found, the response becomes invalid.
        if(userResponse[i] == '.') {
          decimalPointFound = true;
        }
      } else {
        //If the character is not a digit or is a second decimal point, the validResponse boolean is set to false and the loop breaks.
        validResponse = false;
        break;
      }
    }
    //If a valid response was not given, the loop repeats.
    if(!validResponse) {
      cout << "Invalid answer. Please try again." << endl;
    } else {
      //If a valid response was given, the string is converted to a double. If the double is less than/equal to 0 or greater than 1, the loop repeats since it is an invalid population density.
      popDensityFromUser = stod(userResponse);
      if(popDensityFromUser <= 0 || popDensityFromUser > 1) {
        cout << "The number you inputted is not between 0 and 1. Please try again." << endl;
      } else {
        //If the code makes it here, the population density given is valid and the loop ends.
        break;
      }
    }
  }
  //The temporary fileHandler is deleted.
  delete tempFile;

  //mainGrid is initalized using the data found in this method.
  mainGrid = new Grid(heightFromUser, widthFromUser, popDensityFromUser);
}

//Initalizes the fileHandler object based on the fileBeingInputted and fileBeingOutputted booleans.
void Simulation::setupFile() {
  if(fileBeingInputted && fileBeingOutputted) {
    //If both booleans are true, fileHandler is initalized with the default constructor, which sets up the fileHandler and gets the user data.
    fileHandler = new FileIO();
  } else if (fileBeingInputted) {
    //If only fileBeingInputted is true, we must get the initial file path from the user here and ensure it is not "null"
    while(true) {
      cout << "Enter File Path for Input." << endl;
      userResponse = "";
      cin >> userResponse;
      //Checks if the userResponse is "null".
      //If it is not, the rest of the initialization takes place in the FileIO constructor using the user response (for the input) and "null" (for the output) as parameters.
      //Otherwise, the loop repeats.
      if(userResponse.compare("null") == 0) {
        cout << "\"null\" is not a valid file name. Please try again." << endl;
      } else {
        fileHandler = new FileIO (userResponse, "null");
        break;
      }
    }
  } else if (fileBeingOutputted) {
    //If only fileBeingOutputted is true, we must get the initial file name from the user here and ensure it is not "null"
    while(true) {
      cout << "Enter name of the output file. If your file name is already in use, it will be overwritten should it also have the \".out\" extension." << endl;
      userResponse = "";
      cin >> userResponse;
      //Checks if the userResponse is "null".
      //If it is not, the rest of the initialization takes place in the FileIO constructor using "null" (for the input) and userResponse (for the output) as parameters.
      //Otherwise, the loop repeats.
      if(userResponse.compare("null") == 0) {
        cout << "\"null\" is not a valid file name. Please try again." << endl;
      } else {
        fileHandler = new FileIO ("null", userResponse);
        break;
      }
    }
  } else {
    //If the both booleans are false, the fileHandler is doing nothing and is initalized accordingly.
    fileHandler = new FileIO("null", "null");
  }
}

//Sets up the "mode" pointer.
void Simulation::gameModeSetup() {
  //Gets the user selection for the game mode.
  while(true) {
    cout << "Which game mode are you using? Type 1 for Classic, 2 for Doughnut, and 3 for Mirror." << endl;
    userResponse = "";
    cin >> userResponse;
    if(userResponse[0] == '1') {
      //If the user types in a 1, mode is pointed to the classic object created in the header.
      mode = &classic;
      break;
    } else if (userResponse[0] == '2') {
      //If the user types in a 2, mode is pointed to the doughnut object created in the header.
      mode = &doughnut;
      break;
    } else if (userResponse[0] == '3') {
      //If the user types in a 3, mode is pointed to the mirror object created in the header.
      mode = &mirror;
      break;
    } else {
      //The loop repeats since an invalid response was given by the user.
      cout << "Invalid response. Please try again." << endl;
    }
  }
}
