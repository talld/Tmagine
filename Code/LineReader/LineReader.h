#ifndef TMAGINE_LINEREADER_H
#define TMAGINE_LINEREADER_H

#include <LineReaderDefs.h>
#include <deque>
#include <memory>

typedef std::deque<uint64_t> ReturnStack_t;

std::shared_ptr<char*> LineReader_stripLine(const char** text);

ReturnStack_t LineReader_process(const char* line, char * * outString);

#endif //TMAGINE_LINEREADER_H
