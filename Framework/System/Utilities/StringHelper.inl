#include <iostream>
#include <iomanip>
#include <regex>
#include <sstream>

namespace CMF::System::Utilities
{
	inline std::string StringHelper::ToLower(std::string in_str)
	{
		if (!in_str.empty())
		{
			std::transform(in_str.begin(), in_str.end(), in_str.begin(),
				[](unsigned char in_c) { return std::tolower(in_c); });
		}

		return in_str;
	}
	
	inline std::string StringHelper::Unquote(std::string in_str)
	{
		if (!in_str.empty())
			in_str.erase(std::remove(in_str.begin(), in_str.end(), '\"'), in_str.end());
		
		return in_str;
	}

	inline int StringHelper::GetDigits(std::string_view in_str)
	{
		if (!ContainsNumbers(in_str))
			return 0;
		
		return std::stoi(std::regex_replace(std::string(in_str), std::regex("[^0-9]*([0-9]+).*"), std::string("$1")));
	}
	
	inline bool StringHelper::ContainsNumbers(std::string_view in_str)
	{
		return std::any_of(in_str.begin(), in_str.end(), ::isdigit);
	}
	
	inline std::string StringHelper::RemoveSpaces(std::string in_str)
	{
		if (!in_str.empty())
			in_str.erase(std::remove_if(in_str.begin(), in_str.end(), ::isspace), in_str.end());

		return in_str;
	}
	
	inline std::string StringHelper::RemoveLast(std::string in_str, const size_t in_count)
	{
		for (size_t i = 0; i < in_count; i++)
			in_str.pop_back();

		return in_str;
	}
	
    inline std::string StringHelper::Join(const char* in_pDelimiter, std::vector<std::string>& in_rStrings)
    {
        if (in_rStrings.empty())
            return "";

        std::stringstream result{};

		const auto length = in_rStrings.size();

        for (size_t i = 0; i < length; i++)
		{
			const auto& rStr = in_rStrings[i];
			
            result << rStr;

			if (i != length - 1)
				result << in_pDelimiter;
		}

        return result.str();
    }

	inline std::vector<std::string> StringHelper::Split(std::string_view in_str, const std::string& in_rDelimiter, const char in_trimChar)
	{
		std::vector<std::string> result{};
		size_t start{};

		while (true)
		{
			auto pos = in_str.find(in_rDelimiter, start);
			auto token = in_str.substr(start, pos == std::string_view::npos ? in_str.size() - start : pos - start);

			result.emplace_back(Trim(token, in_trimChar));

			if (pos == std::string_view::npos)
				break;

			start = pos + in_rDelimiter.size();
		}

		return result;
	}
	
	inline std::string StringHelper::Trim(std::string_view in_str, const char in_trimChar)
	{
		auto start = in_str.find_first_not_of(in_trimChar);
		
		if (start == std::string::npos)
			return "";
		
		auto end = in_str.find_last_not_of(in_trimChar);
		
		return std::string(in_str.substr(start, end - start + 1));
	}
	
	inline bool StringHelper::IsEmpty(const char* in_pStr)
	{
		if (!in_pStr || !in_pStr[0])
			return true;
		
		return false;
	}
	
	inline bool StringHelper::TryTransformHexStringToByteArray(const char* in_pStr, std::unique_ptr<uint8_t[]>& out_rupBuffer, size_t& out_rLength)
	{
		if (!in_pStr)
			return false;
		
		auto hexString = RemoveSpaces(in_pStr);

		if ((hexString.length() % 2) != 0)
			return false;

		out_rLength = hexString.length() / 2;
		out_rupBuffer = std::make_unique<uint8_t[]>(out_rLength);
		
		size_t i = 0;

		while (i < hexString.length())
		{
			char c = in_pStr[i];
			uint8_t value = 0;
			
			if (c >= '0' && c <= '9')
			{
				value = (c - '0');
			}
			else if (c >= 'A' && c <= 'F')
			{
				value = (10 + (c - 'A'));
			}
			else if (c >= 'a' && c <= 'f')
			{
				value = (10 + (c - 'a'));
			}
			else
			{
				return false;
			}
			
			out_rupBuffer[i / 2] += value << (((i + 1) % 2) * 4);
			
			i++;
		}
		
		return true;
	}
	
	inline std::string StringHelper::TransformByteArrayToHexString(const uint8_t* in_pBuffer, const size_t in_length)
	{
		std::stringstream result{};
		
		for (size_t i = 0; i < in_length; i++)
		{
			result << std::uppercase
				   << std::hex
				   << std::setw(2)
				   << std::setfill('0')
				   << static_cast<uint32_t>(static_cast<uint8_t>(in_pBuffer[i]));
		}
		
		return result.str();
	}
	
	inline std::string StringHelper::GetSubstringBeforeLastChar(std::string_view in_str, const char in_char, const int in_charIndex)
	{
		std::string result{};
		const size_t index = in_str.rfind(in_char);
		
		if (index != std::string_view::npos)
			result = in_str.substr(0, index);
		
		for (int i = 0; i < in_charIndex; i++)
			return GetSubstringBeforeLastChar(result, in_char, i);
		
		return result;
	}

	template <typename T>
	inline bool StringHelper::TryParse(const std::string& in_rStr, T& out_rValue)
	{
		if constexpr (std::is_same_v<T, bool>)
		{
			out_rValue = StringHelper::ToLower(in_rStr) == "true" || in_rStr == "1";
			return true;
		}
		else if constexpr (std::is_same_v<T, float> || std::is_same_v<T, double>)
		{
			out_rValue = static_cast<T>(std::stod(in_rStr));
			return true;
		}
		else if constexpr (std::is_integral_v<T> || std::is_enum_v<T>)
		{
			out_rValue = static_cast<T>(std::atoll(in_rStr.c_str()));
			return true;
		}

		return false;
	}

	template <typename THashType, typename THashProvider>
	inline uint64_t Hash(std::string_view in_str)
	{
		THashProvider hashProvider{};
		
		hashProvider.Update(in_str.data(), in_str.size());

		return hashProvider.Digest();
	}
}
