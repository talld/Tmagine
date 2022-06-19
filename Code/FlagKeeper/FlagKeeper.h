#ifndef TMAGINE_FLAGKEEPER_H
#define TMAGINE_FLAGKEEPER_H

#include <vector>
#include <string>

static std::vector<std::string> flags;

void FlagKeeper_wipe   ();

bool FlagKeeper_check  (const char* flag);

bool FlagKeeper_add    (const char* flag);

bool FlagKeeper_remove (const char* flag);

#endif //TMAGINE_FLAGKEEPER_H
