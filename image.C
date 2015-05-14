#include "Image.h"
#include "Source.h"
#include <stdlib.h>
#include <stdio.h>
#include "logging.h"
#include <iostream>

using namespace std;

Image::Image(void){
    mySource = NULL;

}



Image::Image(int width, int height){
    mySource = NULL;
    this->width = width;
    this->height = height;
    data = (Pixel *)malloc(this->width * this->height * sizeof(Pixel));
    
};

Image::Image(Image &img){
    mySource = NULL;
    this->width = img.width;
    this->height = img.height;
    data = (Pixel *)malloc(this->width * this->height * sizeof(Pixel));
    
};

void Image::Update() const {
    if (mySource != NULL){
        mySource->Update();
    }
    else{
        cerr<<"My source is NULL"<<endl;
    }

}

Pixel *Image::get_data() const {
    return data;
    };

int Image::get_width() const {
    return this->width;
}

int Image::get_height() const {
    return this->height;
}

void Image::set_size(int width, int height){
    this->width = width;
	this->height= height;

    data = new Pixel[width*height];
}

void Image::SetSource(Source *s){
    mySource = s;
}
