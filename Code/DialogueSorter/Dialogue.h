#ifndef TMAGINE_DIALOGUE_H
#define TMAGINE_DIALOGUE_H

typedef struct _DialogueNode
{
	size_t   dialogueIndex;
	size_t   optionCount;
	// always a mul of two, org: [..., option, dest, ...]
	uint32_t optionPairs[0];
}
DialogueNode_t;

DialogueNode_t* Dialogue_LoadNodeFromLine(char* nodeData);

char* Dialogue_LoadNodeToLine(DialogueNode_t* toConvert);

#endif //TMAGINE_DIALOGUE_H
