#include "data_retriever.h"
#include "image_reader.h"
#include "evaluator.h"
#include "classifier.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <set>

using namespace std;


int main() {

    Classifier obj;
    Evaluator eval;

bool exit = false;

while(!exit) {
    cout <<"What would you like to do:train data, save a model, load a model, classify, or exit? Use keywords: train, save, load, classify, exit!";
    string answer;
    cin >> answer;

    transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

    if (answer == "train") {
        obj = Classifier("trainingimages2", "traininglabels2");
    } else if (answer == "save") {
        obj.SaveModelToFile("probabilitymodel");
        obj.SavePriorsModelToFile("priorsmodel");
    } else if (answer == "load") {
        obj.LoadModelFromFile("probabilitymodel");
        obj.LoadPriorsModelFromFile("priorsmodel");
    } else if(answer == "classify") {
        eval = Evaluator(obj);
        cout << eval;
    } else if (answer == "exit") {
        cout << "exit";
        exit = true;
    }
}
return 0;
}