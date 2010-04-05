#include "Defaults.h"

#include "MusicCoderManager.h"

using namespace std;

namespace EACRipper
{
	MusicCoderManager::~MusicCoderManager()
	{
	}

	const vector<pair<wstring, MusicCoderManager::CoderType> > MusicCoderManager::coders() const
	{
		vector<pair<wstring, CoderType> > v;
		for(map<wstring, pair<CoderType, IERAllocator *> >::const_iterator it = coderMap.begin(); it != coderMap.end(); ++ it)
		{
			v.push_back(make_pair(it->first, it->second.first));
		}

		return v;
	}

	bool MusicCoderManager::addCoder(const wstring &name, CoderType type, IERAllocator *alloc)
	{
		return coderMap.insert(map<wstring, pair<CoderType, IERAllocator *> >::value_type(name, make_pair(type, alloc))).second;
	}

	IERAllocator *MusicCoderManager::getCoder(const wstring &name)
	{
		map<wstring, pair<CoderType, IERAllocator *> >::iterator it = coderMap.find(name);
		if(it == coderMap.end())
			throw(runtime_error("The coder does not exist."));
		return it->second.second;
	}
}
