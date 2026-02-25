#include "../../Dependencies/curl/include/curl/curl.h"

namespace CMF::System::Net::Http
{
	inline size_t CurlWriteCallback(char* in_pData, size_t in_size, size_t in_count, void* in_pUserData)
	{
		auto response = static_cast<std::string*>(in_pUserData);

        response->append(in_pData, in_size * in_count);

		return in_size * in_count;
	}

	inline long GetResponse(const std::string& in_rUrl)
	{
		auto result = -1L;
		auto curl = curl_easy_init();

		if (!curl)
			return result;

		curl_easy_setopt(curl, CURLOPT_URL, in_rUrl.c_str());
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteCallback);

		auto res = curl_easy_perform(curl);

		if (res == CURLE_OK)
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &result);

		curl_easy_cleanup(curl);

		return result;
	}
    
	inline bool TryGetString(const std::string& in_rUrl, std::string& out_rValue)
	{
        auto result = true;
		auto curl = curl_easy_init();

		if (!curl)
            return false;

        curl_easy_setopt(curl, CURLOPT_URL, in_rUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, out_rValue);

        auto res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            result = false;

        curl_easy_cleanup(curl);

		return result;
	}
}
