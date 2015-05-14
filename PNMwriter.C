#include "PNMwriter.h"
#include <stdio.h>
#include <fstream>
#include <iostream>


void PNMwriter::Write(char *str){


	
	using namespace std;
	ofstream out;
	out.open(str, ios::binary | ios::out);


	out<<"P6\n"<<img->get_width()<<" "<<img->get_height()<<endl<<"255"<<endl;

	out.write((char *)img->get_data(), img->get_width()*3*img->get_height());

	out.close();


}

const char *PNMwriter::SinkName(){
	char *name = new char[9];
    strcpy(name, "PNMwriter");
    return name;

}