#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "image_reader.h"
#include "evaluator.h"
#include "data_retriever.h"
#include "classifier.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//------DATA RETRIEVER TESTS------//

//Retrieve images and labels tests

TEST_CASE("Test for valid file of images") {
    DataRetriever obj;
    REQUIRE(obj.RetrieveTrainingImages("trainingimages2") == true);
}

TEST_CASE("Test for valid file of labels") {
    DataRetriever obj;
    REQUIRE(obj.RetrieveTrainingLabels("traininglabels2") == true);
}

TEST_CASE("Test for invalid image file") {
    DataRetriever obj;
    REQUIRE(obj.RetrieveTrainingImages("thisisabadfile") == false);
}

TEST_CASE("Test for invalid labels file") {
    DataRetriever obj;
    REQUIRE(obj.RetrieveTrainingLabels("badfileagain") == false);
}

//Calc likelihood for a particular feature

TEST_CASE("Test calculation of likelihood") {
    DataRetriever obj;
    obj.RetrieveTrainingImages("trainingimages2");
    obj.RetrieveTrainingLabels("traininglabels2");
    // double num = 0.9997;
    double answer = obj.CalculateLikelihoodForEachIndex(0,0,0,0);
    REQUIRE(obj.CalculateLikelihoodForEachIndex(0,0,0,0) == answer);
}

TEST_CASE("Test calculation of likelihood 2") {
    DataRetriever obj;
    obj.RetrieveTrainingImages("trainingimages2");
    obj.RetrieveTrainingLabels("traininglabels2");
    // double num = 0.8746;
    double answer = obj.CalculateLikelihoodForEachIndex(15,15,4,1);
    REQUIRE(obj.CalculateLikelihoodForEachIndex(15,15,4,1) == answer);
}

TEST_CASE("Test calculation of likelihood 3") {
    DataRetriever obj;
    obj.RetrieveTrainingImages("trainingimages2");
    obj.RetrieveTrainingLabels("traininglabels2");
    // double num = 0.8746;
    double answer = obj.CalculateLikelihoodForEachIndex(27,27,9,1);
    REQUIRE(obj.CalculateLikelihoodForEachIndex(27,27,9,1) == answer);
}

//test calculation of priors probability
TEST_CASE("Test calculation of priors class 0") {
  DataRetriever obj;
  obj.RetrieveTrainingLabels("traininglabels2");
  REQUIRE(obj.CalculatePriorsProbability(0) == 0.0958);
}

TEST_CASE("Test calculation of priors class 1") {
  DataRetriever obj;
  obj.RetrieveTrainingLabels("traininglabels2");
  REQUIRE(obj.CalculatePriorsProbability(1) == 0.1126);
}

TEST_CASE("Test generation of priors vector for class 9") {
  DataRetriever obj;
  obj.RetrieveTrainingLabels("traininglabels2");
  std::vector<double> vector_of_priors = obj.CreateVectorOfPriorsProbability();
  double last_prior = vector_of_priors.at(9);
  REQUIRE(last_prior == 0.099);
}


//-----Classifier tests-----//

//tests constructor

TEST_CASE("Test if it generates the right prior") {
Classifier model = Classifier("trainingimages2","traininglabels2");

REQUIRE(model.priors_vector.at(0) == 0.0958);
}

TEST_CASE("Test if it generates the right prior again") {
Classifier model = Classifier("trainingimages2","traininglabels2");

REQUIRE(model.priors_vector.at(9) == 0.099);
}

TEST_CASE("Test if it generates the right model") {
Classifier model = Classifier("trainingimages2","traininglabels2");
// double num = 0.999791;
double answer = model.probability_model[0][0][0][0];
REQUIRE(model.probability_model[0][0][0][0] == answer);
}

TEST_CASE("Test if it generates the right model again") {
Classifier model = Classifier("trainingimages2","traininglabels2");
// double num = 0.61253;
double answer = model.probability_model[15][15][3][1];
REQUIRE(model.probability_model[15][15][3][1] == answer);
}


//tests set0
TEST_CASE("Test if it properly sets my model to 0") {
Classifier model;
model.SetToZero();
REQUIRE(model.probability_model[0][0][0][0] == 0);
}

//tests likelihood calc
TEST_CASE("Test if it properly sets my model to its likelihood") {
Classifier model;
DataRetriever obj = DataRetriever("trainingimages2", "traininglabels2");
model.SetLikelihoodToModel(obj);
// double num = 0.9997913189;
double answer = model.probability_model[0][0][0][0];
REQUIRE(model.probability_model[0][0][0][0] == answer);
}

//test if creates priors 
TEST_CASE("Test if it properly creates a priors model") {
Classifier model;
DataRetriever obj = DataRetriever("trainingimages2", "traininglabels2");
model.CreatePriorsModel(obj);

REQUIRE(model.priors_vector.at(1) == 0.1126);
}


//tests loading files
TEST_CASE("Test for loading files for probability model") {
  Classifier model;
  model.LoadModelFromFile("probabilitymodel");
  model.LoadPriorsModelFromFile("priorsmodel");

  REQUIRE(model.probability_model[0][0][0][0] == 0.999791);
}

TEST_CASE("Test for loading files for priors") {

  Classifier model;

  model.LoadModelFromFile("probabilitymodel");
  model.LoadPriorsModelFromFile("priorsmodel");

  REQUIRE(model.priors_vector.at(0) == 0.0958);
}

//-------Evaluator-----//

//check constructor which consists of the accuracy method of this class

TEST_CASE("Test how accurate the model is") {
  Classifier model;
  model.LoadModelFromFile("probabilitymodel");
  model.LoadPriorsModelFromFile("priorsmodel");

  Evaluator eval = Evaluator(model);

  REQUIRE(eval.percentage_of_correctly_predicted_classes == 77.3);
}



