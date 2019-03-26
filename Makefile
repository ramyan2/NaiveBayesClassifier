all:
	g++ -std=c++11 -o naivebayes image_reader.cpp data_retriever.cpp classifier.cpp evaluator.cpp main.cpp
	g++ -g -std=c++11 -o tests naive_bayes_tests.cpp image_reader.cpp data_retriever.cpp classifier.cpp evaluator.cpp
	./tests