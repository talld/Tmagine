#ifndef TMAGINE_LINEREADERDEFS_H
#define TMAGINE_LINEREADERDEFS_H

#include <vector>
#include <deque>

typedef std::deque<uint64_t> ReturnStack_t;

typedef enum _TokenType
{
	// operations
	TOKEN_QUERY,
	TOKEN_ADD,
	TOKEN_REMOVE,

	// types
	TOKEN_FLAG,
	TOKEN_ITEM,
	TOKEN_XP,

	// idents
	TOKEN_WORD,
	TOKEN_NUMBER,

	TOKEN_END,
	TOKEN_BAD
}
TokenType_t;

typedef struct _Token
{
	TokenType_t type;
	const char* str;
}
Token_t;

typedef std::deque<Token_t> TokenStack_t;

typedef struct _Parse
{
	size_t offset;
	const char*  buffer;
}
Parse_t;

inline void Parse_creep(Parse_t* parse)
{
	parse->offset++;
}

inline char Parse_peek(Parse_t* parse, size_t offset)
{
	return parse->buffer[ parse->offset + offset ];
}

inline void Parse_skipWS(Parse_t* parse)
{
	char c;
	while
	(
		c = Parse_peek(parse, 0), (c == '\t')
		|| (c == '\n')
		|| (c == '\r')
		|| (c == ' ' )
		|| isspace(c)
	)
	{
		Parse_creep(parse);
	}
}

void LineReader_processCommand(Parse_t* parse, TokenStack_t* tokenStack);

void LineReader_enactCommand(TokenStack_t* tokenStack,
							 ReturnStack_t * returnStack);

#endif //TMAGINE_LINEREADERDEFS_H
