#include "Defaults.h"

#include "IERComponentMusic.h"

#include "CoderManager.h"
#include "Utility.h"

using namespace std;

namespace EACRipper
{
	ArchiveCoderManager::~ArchiveCoderManager()
	{
	}

	MusicCoderManager::~MusicCoderManager()
	{
	}

	bool MusicCoderManager::addCoder(const std::pair<std::wstring, int_fast32_t> &key, IERAllocator *alloc)
	{
		if(key.second == InCueDecoder)
		{
			addCoder(make_pair(key.first, Decoder), alloc);
		}

		switch(key.second)
		{
		case Decoder:
		case InCueDecoder:
			{
				IERComponentMusicDecoder *dec = static_cast<IERComponentMusicDecoder *>(alloc->alloc());
				DecoderInformation info = dec->getInfo();
				alloc->free(dec);

				vector<wstring> exts = move(split(info.extension, L";")), mimes = move(split(info.mime, L";"));

				for_each(exts.begin(), exts.end(), [this, &key](const wstring &ext) { extMap.insert(make_pair(make_pair(ext, key.second), key.first)); });
				for_each(mimes.begin(), mimes.end(), [this, &key](const wstring &mime) { mimeMap.insert(make_pair(make_pair(mime, key.second), key.first)); });
			}
			break;

		case Encoder:
			{
				IERComponentMusicEncoder *enc = static_cast<IERComponentMusicEncoder *>(alloc->alloc());
				EncoderInformation info = enc->getInfo();
				alloc->free(enc);

				extMap.insert(make_pair(make_pair(wstring(info.extension), key.second), key.first));
				mimeMap.insert(make_pair(make_pair(wstring(info.mime), key.second), key.first));
			}
			break;
		}
		return CoderManager::addCoder(key, alloc);
	}

	wstring MusicCoderManager::getCoderByExtension(const wstring &ext, int_fast32_t type)
	{
		auto it = extMap.find(make_pair(ext, type));
		if(it == extMap.end())
			return wstring();
		return it->second;
	}

	wstring MusicCoderManager::getCoderByMime(const wstring &ext, int_fast32_t type)
	{
		auto it = mimeMap.find(make_pair(ext, type));
		if(it == mimeMap.end())
			return wstring();
		return it->second;
	}

	vector<pair<wstring, int_fast32_t>> MusicCoderManager::extensions()
	{
		vector<pair<wstring, int_fast32_t>> ve;
		for_each(extMap.begin(), extMap.end(), [&ve](const pair<pair<wstring, int_fast32_t>, wstring> &elem) { ve.push_back(elem.first); });
		return move(ve);
	}

	vector<pair<wstring, int_fast32_t>> MusicCoderManager::mimes()
	{
		vector<pair<wstring, int_fast32_t>> ve;
		for_each(mimeMap.begin(), mimeMap.end(), [&ve](const pair<pair<wstring, int_fast32_t>, wstring> &elem) { ve.push_back(elem.first); });
		return move(ve);
	}
}
