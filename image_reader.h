#ifndef IMAGES_H
#define IMAGES_H

#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class ImagesReader { 
    //  private:
        
    public:
        int actual_image[28][28];
        static const int kImageLength = 28;
        static const char kGrayValue = '+';
        static const char kBlackValue = '#';
        ImagesReader();
        friend ostream & operator << (ostream &out, const ImagesReader &c); 
        friend istream & operator >> (istream &in,  ImagesReader &c);
        
};
#endif