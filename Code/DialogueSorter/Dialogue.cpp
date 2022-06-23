#include "Dialogue.h"
#include <vector>

DialogueNode_t* Dialogue_LoadNodeFromLine(char *nodeData)
{
	DialogueNode_t* ret;
	std::vector< std::pair<uint32_t,uint32_t> > options;

	char* token = strtok(nodeData,","); // first numeric token is the top dialogue
	size_t mainDialogue = atoi(token);

	while (token = strtok(nullptr, ","),token != nullptr)
	{
		char* brk;
		if(brk = strpbrk(token,">"), brk != nullptr)
		{
			*brk = 0;
			char* fromString = token;
			char* toString   = brk+1;

			uint32_t from = atoi(fromString);
			uint32_t to   = atoi(toString);

			options.emplace_back(from,to);
		}
	}

	// option arr is uint32[0] so there need to be two slots per entry
	size_t retSize = sizeof(DialogueNode_t) + ( options.size() * ( sizeof(uint32_t) * 2) );
	ret = (DialogueNode_t*) malloc(retSize);
	ret->dialogueIndex = mainDialogue;
	ret->optionCount   = options.size();

	for ( size_t i = 0; i < ret->optionCount; i++ )
	{
		ret->optionPairs[(i*2)  ] = options[i].first;
		ret->optionPairs[(i*2)+1] = options[i].second;
	}

	return ret;
}
