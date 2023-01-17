#pragma once

#include <curl/include/curl/curl.h>
#include <iostream>
#include <json.h>

using json = nlohmann::json;

class HttpHelper
{
	static inline size_t WriteCallback(char* ptr, size_t size, size_t nmemb, void* userdata)
	{
		std::string* response = static_cast<std::string*>(userdata);
		{
			response->append(ptr, size * nmemb);
		}

		return size * nmemb;
	}

public:
	static std::string ReadStringFromUrl(const std::string& url)
	{
		std::string result;

		CURL* curl = curl_easy_init();

		if (curl)
		{
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

			CURLcode res = curl_easy_perform(curl);
			{
				if (res != CURLE_OK)
					std::cerr << "[HttpHelper] curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
			}

			curl_easy_cleanup(curl);
		}

		return result;
	}

	static std::string GetPublicIp()
	{
		return ReadStringFromUrl("https://api.ipify.org");
	}

	struct IpInfo
	{
		std::string m_Query;
		std::string m_Status;
		std::string m_Continent;
		std::string m_ContinentCode;
		std::string m_Country;
		std::string m_CountryCode;
		std::string m_Region;
		std::string m_RegionName;
		std::string m_City;
		std::string m_District;
		std::string m_Zip;
		double m_Latitude;
		double m_Longitude;
		std::string m_TimeZone;
		int m_Offset;
		std::string m_Currency;
		std::string m_Isp;
		std::string m_Organisation;
		std::string m_Asn;
		std::string m_AsnName;
		bool m_IsMobile;
		bool m_IsProxy;
		bool m_IsHosting;

		std::string ToString()
		{
			return std::format
			(
				"IP information;\n"
				"\tQuery:          {}\n"
				"\tStatus:         {}\n"
				"\tContinent:      {}\n"
				"\tContinent Code: {}\n"
				"\tCountry:        {}\n"
				"\tCountry Code:   {}\n"
				"\tRegion:         {}\n"
				"\tRegion Name:    {}\n"
				"\tCity:           {}\n"
				"\tDistrict:       {}\n"
				"\tZip:            {}\n"
				"\tLatitude:       {}\n"
				"\tLongitude:      {}\n"
				"\tTime Zone:      {}\n"
				"\tOffset:         {}\n"
				"\tCurrency:       {}\n"
				"\tISP:            {}\n"
				"\tOrganisation:   {}\n"
				"\tASN:            {}\n"
				"\tASN Name:       {}\n"
				"\tIs Mobile?      {}\n"
				"\tIs Proxy?       {}\n"
				"\tIs Hosting?     {}",

				m_Query,
				m_Status,
				m_Continent,
				m_ContinentCode,
				m_Country,
				m_CountryCode,
				m_Region,
				m_RegionName,
				m_City,
				m_District,
				m_Zip,
				m_Latitude,
				m_Longitude,
				m_TimeZone,
				m_Offset,
				m_Currency,
				m_Isp,
				m_Organisation,
				m_Asn,
				m_AsnName,
				m_IsMobile,
				m_IsProxy,
				m_IsHosting
			);
		}

		IpInfo() { }

		IpInfo(std::string in_json)
		{
#if !_DEBUG
			try
			{
#endif
				json j = json::parse(in_json);
				{
					m_Query         = j["query"];
					m_Status        = j["status"];
					m_Continent     = j["continent"];
					m_ContinentCode = j["continentCode"];
					m_Country       = j["country"];
					m_CountryCode   = j["countryCode"];
					m_Region        = j["region"];
					m_RegionName    = j["regionName"];
					m_City          = j["city"];
					m_District      = j["district"];
					m_Zip           = j["zip"];
					m_Latitude      = j["lat"];
					m_Longitude     = j["lon"];
					m_TimeZone      = j["timezone"];
					m_Offset        = j["offset"];
					m_Currency      = j["currency"];
					m_Isp           = j["isp"];
					m_Organisation  = j["org"];
					m_Asn           = j["as"];
					m_AsnName       = j["asname"];
					m_IsMobile      = j["mobile"];
					m_IsProxy       = j["proxy"];
					m_IsHosting     = j["hosting"];
				}
#if !_DEBUG
			}
			catch (...)
			{
				printf("[HttpHelper] Failed to parse JSON response.\n");
			}
#endif
		}
	};

	static IpInfo GetIpInfo(std::string ip)
	{
		std::string response = ReadStringFromUrl("http://ip-api.com/json/" + ip + "?fields=66846719");

		if (response.empty())
			return IpInfo();

		return IpInfo(response);
	}
};