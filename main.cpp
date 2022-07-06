#define GLOG_LOGGING_ENABLED 1

#include <vector>
#include <iostream>
#include <curses.h>

#include <LineReader.h>
#include <FlagKeeper.h>
#include <Dialogue.h>

int main()
{
	char* t;
	int d;
	LineReader_process("you got a hat![ +F A_REALLY_BIG_HAT ]", &t);
    d = FlagKeeper_check("A_REALLY_BIG_HAT");
	GLOG_INFO("%s", t);
	GLOG_INFO("A_REALLY_BIG_HAT: %d", d);

	char test[] = "0,100>24,3>-1,47>59";
	DialogueNode_t* node = Dialogue_LoadNodeFromLine(test);
	char* test2 = Dialogue_LoadNodeToLine(node);

	char* test3 = " a string \n with multiple lines";
	LineReader_stripLine(&test3);
}
