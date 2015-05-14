#include "Image.h"

#ifndef SOURCE
#define SOURCE

class Source{

protected:

	Image img_src;



public:
	virtual const char *SourceName() = 0;
	Source(void);


	virtual void Update() = 0;
	virtual void Execute() = 0;
	Image *GetOutput(void);
};


#endif

