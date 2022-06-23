#ifndef TMAGINE_DIALOGUE_H
#define TMAGINE_DIALOGUE_H

typedef struct _DialogueNode
{
	size_t   dialogueIndex;
	size_t   optionCount;
	uint32_t optionPairs[0]; // always a mul of two, org: [..., option, dest, ...]
}
DialogueNode_t;

DialogueNode_t* Dialogue_LoadNodeFromLine(char* nodeData);

#endif //TMAGINE_DIALOGUE_H
