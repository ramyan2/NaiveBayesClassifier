//reads the images stored in a file 
#include "image_reader.h"
#include <istream>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>


using namespace std;


ImagesReader::ImagesReader() {}


//helper to check foreground value

istream & operator >> (istream &in,  ImagesReader &c) {
    //initialize the 2d array
    int image_with_pixel_values[c.kImageLength][c.kImageLength];
    for (int i = 0; i < c.kImageLength; i++) {
        for (int j = 0; j < c.kImageLength; j++) {
            image_with_pixel_values[i][j] = 0;
        }
    }

    int times_to_loop = c.kImageLength;

    //TRY WHILE

    //loop it through every line
    string image_data_line;
    for (int line = 0; line < times_to_loop; line++) {
        getline(in, image_data_line);
        if (image_data_line.empty()) {
            continue;
        }
        //loop through every charac of line to check if it is a foreground value
        for (unsigned long long character_in_line = 0; character_in_line < image_data_line.size(); character_in_line++) {
            if (image_data_line.at(character_in_line) == c.kGrayValue || image_data_line.at(character_in_line) == c.kBlackValue) {
                image_with_pixel_values[line][character_in_line] = 1;
            }
        }
    }

    //set actual image to this image with pixel values
    for (int i = 0; i < c.kImageLength; i++) {
        for (int j = 0; j < c.kImageLength; j++) {
            c.actual_image[i][j] = image_with_pixel_values[i][j];
        }
    }

    return in;
}


ostream &operator<<(ostream &out, const ImagesReader &c) {
  for (int i= 0; i < c.kImageLength; i++) {
    for (int j = 0; j < c.kImageLength; j++) {
      out << c.actual_image[i][j];
    }
    out << std::endl;
  }
  return out;
}