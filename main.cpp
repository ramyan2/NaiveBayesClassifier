#include "data_retriever.h"
#include "image_reader.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <set>

using namespace std;


int main() {
//read frmo training images and labels file store in a string
//declare object of data retriever class and operate the methods
//print out what these methods do and check if print a correct model

cout << "Enter the trainingimages file name";
string filename;
cin >> filename;
DataRetriever obj;
obj.RetrieveTrainingImages(filename);

cout << "Enter the traininglabels file name";
string filename2;
cin >> filename2;
obj.RetrieveTrainingLabels(filename2);

obj.CreateProbabilityModel();
cout << obj.probability_model[27][27][9][1];

return 0;
}