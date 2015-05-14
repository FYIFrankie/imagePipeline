#include "filters.h"
#include "Image.h"
#include <stdio.h>
#include <fstream>
#include <logging.h>
#include <iostream>
#include <string.h>

using namespace std;
void Filter::Update(){
    char msg[128];

    if (img != NULL){ 
        sprintf(msg, "%s: about to update input1", SourceName());
        Logger::LogEvent(msg);
        img->Update();
        sprintf(msg, "%s: done updating input1", SourceName());
        Logger::LogEvent(msg);   
    }
    if (img2 != NULL){
        sprintf(msg, "%s: about to update input2", SourceName());
        Logger::LogEvent(msg);
        img2->Update();
        sprintf(msg, "%s: done updating input2", SourceName());
        Logger::LogEvent(msg); 
    }

    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);


}

const char *Filter::SourceName(){
    return FilterName();
}

const char *Filter::SinkName(){
    return FilterName();
}

void Invert::Execute(void){

    this->OneInputCheck();


    int width = this->img->get_width();
    int height = this->img->get_height();
    unsigned char val = 255;


    img_src.set_size(width, height);

    Pixel *buffer = img_src.get_data();
    Pixel *buffer1 = img->get_data();

    for (int i = 0; i<width*height; i++){
        for (int j = 0; j<3; j++){
            buffer[i].rgb[j]=val - buffer1[i].rgb[j];
        }
    }
}

void Moasic::Execute(void){

    this->OneInputCheck();


    int width = this->img->get_width();
    int height = this->img->get_height();
    int val;


    img_src.set_size(width, height);

    Pixel *buffer = img_src.get_data();
    Pixel *buffer1 = img->get_data();

    FILE *out = fopen("Moasic_out.txt", "w");

    for (int i = 0; i<(width*height)/25; i++){

    }
}


void Transpose::Execute(void){

    this->OneInputCheck();

    int width = img->get_width();
    int height = img->get_height();

    img_src.set_size(height, width);

    Pixel *buffer = img->get_data();
    Pixel *buffer1 = img_src.get_data();



    for (int i = 0; i<height; i++){
        for (int j = 0; j<width; j++){
            buffer1[j*height+i] = buffer[i*width+j];
        }
    }


}

void Crop::Execute(void)
{
    
    this->OneInputCheck();
    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istart >= img->get_width() || Istop >= img->get_width())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Jstart >= img->get_height() || Jstop >= img->get_height())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }

    int height = Jstop-Jstart+1;
    int width  = Istop-Istart+1;
    int inputWidth = img->get_width();
    img_src.set_size(width, height);
    Pixel *buffer = img_src.get_data();
    const Pixel *buffer1 = img->get_data();
    for (int i = Istart ; i <= Istop ; i++)
        for (int j = Jstart ; j <= Jstop ; j++)
        {

            int idx1 = j*inputWidth+i;
            int idx  = (j-Jstart)*width+(i-Istart);
            buffer[idx]   = buffer1[idx1];
            buffer[idx+1] = buffer1[idx1+1];
            buffer[idx+2] = buffer1[idx1+2];
        }
}


int Shrinker::ConvertTo1d(int i, int j, int width){
    return (i*width)+j;

}


void Shrinker::Execute(){

    this->OneInputCheck();

    img_src.set_size((this->img->get_width())/2, (this->img->get_height())/2);

    Pixel *buffer = img_src.get_data();
    Pixel *buffer1 = img->get_data();

    int width_src = img_src.get_width();
    int height = img_src.get_height();
    int width_input = img->get_width();


    for (int i = 0; i <height; i++){
        for (int j = 0; j<width_src; j++){
            buffer[i*width_src + j] = buffer1[2*i*width_input + 2*j];
        }
    }

}





void LRConcat::Execute(){
    this->OneInputCheck();
    this->TwoInputCheck();

	if (img->get_height() != img2->get_height()){
    	char msg[1024];
        sprintf(msg, "%s: heights must match: %d, %d",SinkName(),img->get_height(), img2->get_height());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    int img1width = img->get_width();
    int img2width = img2->get_width();
    int height = img->get_height();
    int img_out_width = (img1width+img2width);


    img_src.set_size(img1width+img2width, height);

    Pixel *buffer = img_src.get_data();
    Pixel *buffer1 = img->get_data();
    Pixel *buffer2 = img2->get_data();

    for (int i = 0; i<height; i++ ){
        for (int j = 0; j<img1width; j++ ){
            buffer[i*img_out_width+ j] = buffer1[i*img1width + j];
        }

    }
    for (int i = 0; i <height; i++){
        for (int j = 0; j<img2width; j++){
            buffer[i*img_out_width+j+img1width] = buffer2[i*img2width+j];
        }
    }

}





void TBConcat::Execute(){

    this->OneInputCheck();
    this->TwoInputCheck();


	if (img->get_width() != img2->get_width()){
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d",SinkName(),img->get_width(), img2->get_width());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    Pixel *tdata = img->get_data();
    Pixel *bdata = img2->get_data();

    int width = img->get_width();
    int height_src = img->get_height() + img2->get_height();
    int end = img->get_height()*img->get_width();

    int t_counter = 0;
    int b_counter = 0;
    int cur_int = 0;
    Pixel *cur_data = tdata;

    img_src.set_size(img->get_width(), img->get_height()+img2->get_height());
    Pixel *buffer = img_src.get_data();


    for (int i=0; i<(height_src)*(width); i++){
        if (i == end){
            cur_int = 0;
            cur_data=bdata;
        }
        buffer[i] = cur_data[cur_int]; 

        cur_int = cur_int +1;

    }
}


void Blender::Execute(){

    this->OneInputCheck();
    this->TwoInputCheck();

    if (img->get_width() != img2->get_width()){
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d",SinkName(),img->get_width(), img2->get_width());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if (img->get_height() != img2->get_height()){
        char msg[1024];
        sprintf(msg, "%s: heights must match: %d, %d",SinkName(),img->get_height(), img2->get_height());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

	float factor_first = this->factor;
    float factor_two = 1-(this->factor);

    if (factor_first > 1){
        char msg[1024];
        sprintf(msg, "Invalid factor for Blender: %f", factor_first);
        DataFlowException e(SinkName(), msg);
        throw e;
    }



    Pixel *data1 = img->get_data();
    Pixel *data2 = img2->get_data();

    int total = img->get_width() * img->get_height();

    img_src.set_size(this->img->get_width(),this->img2->get_height());

    Pixel *buffer = img_src.get_data();
    Pixel *buffer1 = img->get_data();
    Pixel *buffer2 = img2->get_data();

    for (int i=0; i<total; i++){
        for (int j=0; j<3; j++){
            buffer[i].rgb[j] = factor_first*buffer1[i].rgb[j] + factor_two*buffer2[i].rgb[j];
        }
    }


};


void Blender::SetFactor(float factor){
	this->factor = factor;

};


Color::Color(int width, int height, unsigned char r, unsigned char g, unsigned char b){

    char msg[128];
    sprintf(msg, "%s: about to create Image", SourceName());
    Logger::LogEvent(msg);


    img_src.set_size(width,height);
    Pixel *buffer = img_src.get_data();

    for (int i = 0; i<width*height; i++){
        buffer[i].rgb[0] = r;
        buffer[i].rgb[1] = g;
        buffer[i].rgb[2] = b;

    }
    sprintf(msg, "%s: done creating Image", SourceName());
    Logger::LogEvent(msg);


}

void CheckSum::OutputCheckSum(const char *arg){




    if (img == NULL){
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    char msg[128];

    sprintf(msg, "%s: about to OutputCheckSum", SinkName());
    Logger::LogEvent(msg);

    Pixel *buffer = img->get_data();

    ofstream myfile;
    myfile.open (arg);

    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    int width = img->get_width();
    int height = img->get_height();
    for (int i = 0; i<width*height; i++){
        r = r + buffer[i].rgb[0];
        g = g + buffer[i].rgb[1];
        b = b + buffer[i].rgb[2];
    }

    myfile<<"CHECKSUM: "<<(int )r<<", "<<(int )g<<", "<<(int )b<<endl;
    myfile.close();

    sprintf(msg, "%s: done executing", SinkName());
    Logger::LogEvent(msg);


}