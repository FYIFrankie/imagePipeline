#include "logging.h"
#include <stdio.h>

FILE *Logger::logger = NULL;

void Logger::LogEvent (char const *event){
	if (logger == NULL){
		logger = fopen("logger", "w");
	};
	fprintf(logger, "%s\n", event);

}
void Logger::Finalize(){
	fclose(logger);
}

DataFlowException::DataFlowException(const char *type, const char *error){
	sprintf(msg, "Throwing exception: (%s): %s", type, error);
	Logger::LogEvent(msg);  
}