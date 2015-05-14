#include "PNMreader.h"
#include "Image.h"
#include <fstream>
#include <iostream>
#include "logging.h"

    using namespace std;
PNMreader::PNMreader(char *str){

	this->str = new char[strlen(str)+1];
    strcpy(this->str, str);
}

PNMreader::~PNMreader(void){

    delete [] this->str;
}

void PNMreader::Update(){
    Execute();
}

void PNMreader::Execute(){
    char msg[128];
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);   


    ifstream in;
    in.open(this->str, ios::binary | ios::in);

    char magicNum[128];
    int  width, height, maxval, rgb_comp_color;
    char nl;

    if (!in.is_open()){
        char msg[1024];
        sprintf(msg, "%s: Unable to open file %s\n", SourceName(), this->str);
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    in>>magicNum>>width>>height>>maxval;
    in.seekg(1, ios::cur);

    img_src.set_size(width, height);


    if (strcmp(magicNum, "P6") != 0){
        char msg[1024];
        sprintf(msg, "%s: Unable to read from file %s, because it is not a PNM file of type P6", SourceName(), this->str);
        DataFlowException e(SourceName(), msg);
        throw e;
    }

    in.read((char *)img_src.get_data(), img_src.get_width()*3*img_src.get_height());


    in.close();

    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg); 

};



