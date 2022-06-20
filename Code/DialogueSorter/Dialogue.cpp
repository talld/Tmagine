#include "Dialogue.h"

DialogueNode* Dialogue_LoadNodeFromLine(char *nodeData)
{
	DialogueNode* ret;
	size_t optionCount = 0;

	char* token = strtok(nodeData,",");

	size_t mainDialogue = atoi(token);
	while (token = strtok(nullptr, ","),token != nullptr)
	{
		GLOG_INFO("%s",token);

		char* brk;
		if(brk = strpbrk(token,">"), brk != nullptr)
		{
			optionCount += 2;
			*brk = 0;
			char* from = token;
			char* to   = brk+1;
		}
	}
}
