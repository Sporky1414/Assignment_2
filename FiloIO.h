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

  private:
    string getInputFilePathFromUser();
    string getOutputFileNameFromUser();
    bool checkInputFileValidity(string filePath);
    bool checkIfStringIsNumber(string tempString);
    bool isNeeded();

    string inputFilePath;
    string outputFileName;
    ifstream input;
    ofstream output;
}
