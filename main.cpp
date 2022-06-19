#define GLOG_LOGGING_ENABLED 1

#include <vector>
#include <iostream>

#include <LineReader.h>
#include <FlagKeeper.h>

int main()
{
	char* t;
	int d;
	LineReader_process("[ +F A_REALLY_BIG_HAT ]you got a hat!", &t);
    d = FlagKeeper_check("A_REALLY_BIG_HAT");
	GLOG_INFO("%s", t);
	GLOG_INFO("A_REALLY_BIG_HAT: %d", d);
}
