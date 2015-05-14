#include "Source.h"
#include "Sink.h"
#include <stdlib.h>
#include <stdio.h>
#include "logging.h"

#ifndef FILTER
#define FILTER

class Filter : public Source, public Sink{

public:

	virtual void Update();
	virtual const char *SourceName();
	virtual const char *SinkName();
	virtual const char *FilterName() = 0;


	void OneInputCheck(){    
		if (img == NULL){
        char msg[1024];
        sprintf(msg, "%s: no input1!", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }};
    void TwoInputCheck(){ 
		if (img2 == NULL){
        char msg[1024];
        sprintf(msg, "%s: no input2!", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }};


};



#endif
#ifndef TRANSPOSE
#define TRANSPOSE

#ifndef MOSAIC
#define MOSAIC


class Moasic : public Filter {

public:

	virtual const char* FilterName() {return "Moasic";};
	virtual void Execute();

};

#endif


#ifndef INVERT
#define INVERT

class Invert : public Filter{


public:

	virtual const char* FilterName() {return "Invert"; };
	virtual void Execute();

};


#endif

class Transpose : public Filter {

public:

	virtual const char* FilterName() {return "Transpose"; };
	virtual void Execute();


};





#endif

#ifndef CROP
#define CROP
class Crop : public Filter
{
  public:
                   Crop()  { Istart = Istop = Jstart = Jstop = -1; };

    virtual const char *FilterName() { return "Crop"; };
    virtual void   Execute();
    void           SetRegion(int Istart_, int Istop_, int Jstart_, int Jstop_)
                      {
                        Istart = Istart_;
                        Istop  = Istop_;
                        Jstart = Jstart_;
                        Jstop  = Jstop_;
                      }

  private:
    int Istart, Istop, Jstart, Jstop;
};

#endif


#ifndef SHRINKER
#define SHRINKER

class Shrinker : public Filter
{

public:


	int ConvertTo1d(int, int, int);
	void virtual Execute();
	virtual const char *FilterName() {return "Shrinker";};
	/* data */
};


#endif


#ifndef LRCONCAT
#define LRCONCAT

class LRConcat : public Filter
{

public:

	void virtual Execute();
	virtual const char *FilterName() {return "LRConcat";};
	/* data */
};


#endif

#ifndef TBconcat
#define TBconcat


class TBConcat : public Filter
{
public:


	void virtual Execute();
	virtual const char *FilterName() { return "TBConcat";};
	/* data */
};


#endif

#ifndef BLENDER
#define BLENDER


class Blender : public Filter
{

	float factor;
public:

	Blender() {this->factor = 0.0;};
	void virtual Execute();
	void SetFactor(float);
	virtual const char *FilterName() {return "Blender";} ;
	/* data */
};

#endif


#ifndef CONSTANTCOLOR
#define CONSTANTCOLOR

class Color : public Source{


public:
	virtual const char *SourceName(){ return "Color";};
	Color(int, int, unsigned char, unsigned char, unsigned char);

	virtual void Execute() {};
	virtual void Update(){};


};




#endif

#ifndef CHECKSUM
#define CHECKSUM

class CheckSum : public Sink {

public:

	virtual const char* SinkName() {return "Checksum"; };

	void OutputCheckSum(const char *arg);

};


#endif