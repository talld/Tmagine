#include "FlagKeeper.h"

#include <algorithm>
#include <cstring>

void FlagKeeper_wipe()
{
	flags.clear();
}

bool FlagKeeper_check(const char *flag)
{
	auto val = std::find(flags.begin(), flags.end(), flag);
	return val != std::end(flags);
}

bool FlagKeeper_add(const char *flag)
{
	bool alreadyExists = FlagKeeper_check(flag);

	if(!alreadyExists)
	{
		flags.emplace_back(flag);
	}

	return alreadyExists;
}

bool FlagKeeper_remove(const char *flag)
{
	bool exists = FlagKeeper_check(flag);

	if(exists)
	{
		auto removals =	std::remove(std::begin(flags),
				            std::end(flags), flag);

		flags.erase( removals, std::end(flags) );
	}

	return exists;
}
