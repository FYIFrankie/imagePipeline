#include "Image.h"
#ifndef SINK
#define SINK


class Sink{

public:
	
	virtual const char *SinkName() = 0;

	Sink();
	void SetInput(Image *);
	void SetInput2(Image *);

protected:
	const Image *img;
	const Image *img2;

};


#endif
