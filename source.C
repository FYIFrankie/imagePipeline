#include "Source.h"
#include <stdio.h>
#include <iostream>

Source::Source(void){
	img_src.SetSource(this);

};


Image *Source::GetOutput(void){
	img_src.SetSource(this);
	return &this->img_src;
};









