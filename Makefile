all:
	g++ -std=c++14 -o naivebayes image_reader.cpp data_retriever.cpp evaluator.cpp main.cpp