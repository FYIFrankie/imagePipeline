#include "Sink.h"
#include <string.h>

#ifndef PNMWRITER
#define PNMWRITER
class PNMwriter : public Sink {

public:
	void Write(char *);

	virtual const char *SinkName();



};


#endif