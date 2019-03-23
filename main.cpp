#include "data_retriever.h"
#include "image_reader.h"
#include "evaluator.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <set>

using namespace std;


int main() {

    DataRetriever obj;
    Evaluator eval;
//read frmo training images and labels file store in a string
//declare object of data retriever class and operate the methods
//print out what these methods do and check if print a correct model

bool exit = false;

while(!exit) {
    cout <<"What would you like to do:train data, save a model, load a model, classify, or exit?";
    string answer;
    cin >> answer;

    // transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
    if (answer == "train") {
        obj = DataRetriever("trainingimages", "traininglabels");
    } else if (answer == "save") {
        obj.SaveModelToFile("probabilitymodel");
        obj.SavePriorsModelToFile("priorsmodel");
    } else if (answer == "load") {
        obj.LoadModelFromFile("probabilitymodel");
        obj.LoadPriorsModelFromFile("priorsmodel");
    } else if(answer == "classify") {
        eval = Evaluator(obj);
    } else if (answer == "exit") {
        cout << "exit";
        exit = true;
    }
}



// cout << "Enter the trainingimages file name";
// string filename;
// cin >> filename;
// DataRetriever obj;
// obj.RetrieveTrainingImages(filename);

// cout << "Enter the traininglabels file name";
// string filename2;
// cin >> filename2;
// obj.RetrieveTrainingLabels(filename2);

// obj.CreateProbabilityModel();
// cout << obj.probability_model[27][27][9][1];

return 0;
}