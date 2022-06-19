#ifndef TMAGINE_LINEREADER_H
#define TMAGINE_LINEREADER_H

#include <LineReaderDefs.h>
#include <deque>

typedef std::deque<uint64_t> ReturnStack_t;

ReturnStack_t LineReader_process(const char* line, char * * outString);

#endif //TMAGINE_LINEREADER_H
