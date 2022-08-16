#include "LineReaderDefs.h"
#include "LineReader.h"

#include <FlagKeeper.h>

void LineReader_processCommand(Parse_t* parse, TokenStack_t* tokenStack)
{
	while (Parse_peek(parse,0) != '\0')
	{
		Parse_skipWS(parse);
		char c = Parse_peek(parse,0);

		switch (c)
		{
			case ']':
			{
				Parse_creep(parse);
				tokenStack->push_back({TOKEN_END, nullptr});
				goto fin;
			}
			break;

			case '?':
			{
				Parse_creep(parse);
				tokenStack->push_back({TOKEN_QUERY, nullptr});
			}
			break;

			case '+':
			{
				Parse_creep(parse);
				tokenStack->push_back({TOKEN_ADD, nullptr});
			}
			break;

			case '-':
			{
				Parse_creep(parse);
				tokenStack->push_back({TOKEN_REMOVE, nullptr});
			}
			break;

			case 'F':
			case 'f':
			{
				Parse_creep(parse);
				tokenStack->push_back({TOKEN_FLAG, nullptr});
			}
			break;

			case 'i':
			case 'I':
			{
				Parse_creep(parse);
				tokenStack->push_back({TOKEN_ITEM, nullptr});
			}
			break;

			case 'x':
			case 'X':
			{
				Parse_creep(parse);
				tokenStack->push_back({TOKEN_XP, nullptr});
			}
			break;

			default:
			{
				TokenType_t type = TOKEN_BAD;
				if ( isalpha(c) )
				{
					type = TOKEN_WORD;
				}
				else if ( isdigit(c) )
				{
					type = TOKEN_NUMBER;
				}

				if(type < TOKEN_BAD)
				{
					// flat 255 is simpler than growing str
					// imposes a hard limit for items but eh
					char *str = (char *) calloc(1, 255);
					size_t i = 0;
					// assuming that a digit is all digit
					// TODO: error on alpha in numeral vals
					while
					(
						isalnum(c=Parse_peek(parse, 0))
						|| c == '_'
					)
					{
						str[i++] = c;
						Parse_creep(parse);
					}
					tokenStack->push_back( {type, str} );
				}
			}
			break;
		}
	}

fin:
	return;
}

void LineReader_enactCommand(TokenStack_t* tokenStack,
	       	ReturnStack_t * returnStack)
{

	// confirm that we have a valid command on the stack
	const TokenType_t end = tokenStack->back().type;
	tokenStack->pop_back();

	if(end != TOKEN_END)
	{
		GLOG_ERR("Invalid command: command not terminated!");
	}

	// from this point arg should not change
	// and the name of the thing should always be first on the stack
	const char * const arg = tokenStack->back().str;
	tokenStack->pop_back();

	const TokenType_t argDest = tokenStack->back().type;
	tokenStack->pop_back();

	const TokenType_t argMod = tokenStack->back().type;
	tokenStack->pop_back();

	// despite add and remove returning values on queries are returned
	// this is so that strings only return 1 ( usable ) or 0 ( unusable )
	if ( argDest == TOKEN_FLAG )
	{
		switch(argMod)
		{
			case TOKEN_QUERY:
				returnStack->push_back(FlagKeeper_check(arg));
				break;
			case TOKEN_ADD:
				FlagKeeper_add(arg);
				break;
			case TOKEN_REMOVE:
				FlagKeeper_remove(arg);
				break;
			default:
				break;
		}
	}
	else if ( argDest == TOKEN_ITEM )
	{

	}
	else if ( argDest == TOKEN_XP )
	{

	}
}

/***
 * Grab a line from a string, 
 * setting text to point at the end of the grabbed line.
 * & returning a shared point to the grabbed line
 */
std::shared_ptr<char*> LineReader_stripLine(const char** text) {

	// strtok with extra steps?.
	// TODO: improve?

	using Line = std::shared_ptr<char*>;
	Line ret;

	const char* start = *text;
	const char* end   = start;

	while ( *end++ != '\n' ) ;

	ptrdiff_t diff = end - start;
	*text = end;

	char * lineOfText = (char*) malloc (diff);
	strncpy(lineOfText, start, diff);
	lineOfText[diff-1] = '\0'; // replace delim with 0

	ret = std::make_shared<char*>(lineOfText);

	return ret;
}

ReturnStack_t LineReader_process(const char *line, char * * const outString)
{

	ReturnStack_t returnStack = {};

	Parse_t *p = (Parse_t*) alloca( sizeof(Parse_t) );
	p->offset = 0;
	p->buffer = line;

	TokenStack_t tokenStack;

	std::vector<char> outLine;

	while (Parse_peek(p,0) != '\0')
	{
		if(Parse_peek(p,0) == '[' )
		{
			Parse_creep(p); // skip '['
			LineReader_processCommand(p, &tokenStack);
			LineReader_enactCommand(&tokenStack, &returnStack);
		}
		else
		{
			outLine.push_back(Parse_peek(p,0));
			Parse_creep(p);
		}
	}

	outLine.push_back('\0');
	*outString = (char*) malloc(outLine.size());
	strncpy(*outString, outLine.data(), outLine.size());
	return returnStack;
}
