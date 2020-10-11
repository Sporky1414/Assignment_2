#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class FileIO {
  public:
    FileIO();
    FileIO(string newInputFilePath, string newOutputFileName);
    ~FileIO();

    string readNextLine();
    bool inputHasDataLeft();
    void writeData(string data);
    bool checkIfStringIsNumber(string tempString);

  private:
    string getInputFilePathFromUser();
    string getOutputFileNameFromUser();
    bool checkInputFileValidity();
    bool isNeeded();

    string inputFilePath;
    string outputFileName;
    ifstream input;
    ofstream output;
};
