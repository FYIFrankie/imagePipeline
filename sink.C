#include "Sink.h"
#include <stdio.h>


void Sink::SetInput(Image *img_1){

	this->img = img_1;

};

void Sink::SetInput2(Image *img_2){

	this->img2 = img_2;
}

Sink::Sink(){
	img = NULL;
	img2 = NULL;
}


