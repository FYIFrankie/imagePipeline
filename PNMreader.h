#include "Source.h"
#include <string.h>
#ifndef PNMREADER
#define PNMREADER

class PNMreader : public Source{

private:


public:


	char *str;
	PNMreader(char *);
	~PNMreader(void);



	virtual const char *SourceName() { return "PNMReader";};
	virtual void Execute();
	virtual void Update();
};


#endif