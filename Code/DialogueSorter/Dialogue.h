#ifndef TMAGINE_DIALOGUE_H
#define TMAGINE_DIALOGUE_H

typedef struct _DialogueNode
{
	size_t dialogueIndex;
	size_t optionCount;
	size_t optionPairs[0]; // always a mul of two, org: [..., option, dest, ...]
}
DialogueNode;

DialogueNode* Dialogue_LoadNodeFromLine(char* nodeData);

#endif //TMAGINE_DIALOGUE_H
