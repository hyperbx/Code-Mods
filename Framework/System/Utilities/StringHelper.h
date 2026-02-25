#pragma once

#include <memory>
#include <string>
#include "../Hashing/IHashProvider.h"

namespace CMF::System::Utilities
{
	class StringHelper
	{
	public:
		static std::string ToLower(std::string in_str);
		static std::string Unquote(std::string in_str);
		static int GetDigits(std::string_view in_str);
		static bool ContainsNumbers(std::string_view in_str);
		static std::string RemoveSpaces(std::string in_str);
		static std::string RemoveLast(std::string in_str, const size_t in_count = 1);
		static std::string Join(const char* in_pDelimiter, std::vector<std::string>& in_rStrings);
		static std::vector<std::string> Split(std::string_view in_str, const std::string& in_rDelimiter, const char in_trimChar = ' ');
		static std::string Trim(std::string_view in_str, const char in_trimChar = ' ');
		static bool IsEmpty(const char* in_pStr);
		static bool TryTransformHexStringToByteArray(const char* in_pStr, std::unique_ptr<uint8_t[]>& out_rupBuffer, size_t& out_rLength);
		static std::string TransformByteArrayToHexString(const uint8_t* in_pBuffer, const size_t in_length);
		static std::string GetSubstringBeforeLastChar(std::string_view in_str, const char in_char, const int in_charIndex = 0);

		template <typename T>
		static bool TryParse(const std::string& in_rStr, T& out_rValue);

        template <typename THashType, typename THashProvider = CMF::System::Hashing::IHashProvider<THashType>>
		static THashType Hash(std::string_view in_str);
	};
}

#include "StringHelper.inl"
