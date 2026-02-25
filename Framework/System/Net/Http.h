#pragma once

namespace CMF::System::Net::Http
{
	static size_t CurlWriteCallback(char* in_pData, size_t in_size, size_t in_count, void* in_pUserData);
	static long GetResponse(const std::string& in_rUrl);
	static bool TryGetString(const std::string& in_rUrl, std::string& out_rValue);
}

#include "Http.inl"
