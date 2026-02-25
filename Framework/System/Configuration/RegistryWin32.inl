#include <assert.h>
#include <Windows.h>

#define REG_MAX_SUBKEY_PATH_LENGTH MAX_PATH
#define REG_MAX_VALUE_NAME_LENGTH  0x3FFF

namespace CMF::System::Configuration::Registry
{
    inline bool Init()
    {
        return true;
    }

    inline bool TryParseRegistryPath(const std::filesystem::path& in_rPath, HKEY& out_rHKey, wchar_t* out_pSubKey, wchar_t* out_pValueName)
    {
        auto root = in_rPath.root_directory().string();

        if (root == "HKEY_CLASSES_ROOT")
        {
            out_rHKey = HKEY_CLASSES_ROOT;
            return true;
        }
        else if (root == "HKEY_CURRENT_CONFIG")
        {
            out_rHKey = HKEY_CURRENT_CONFIG;
            return true;
        }
        else if (root == "HKEY_CURRENT_USER")
        {
            out_rHKey = HKEY_CURRENT_USER;
            return true;
        }
        else if (root == "HKEY_LOCAL_MACHINE")
        {
            out_rHKey = HKEY_LOCAL_MACHINE;
            return true;
        }
        else if (root == "HKEY_USERS")
        {
            out_rHKey = HKEY_USERS;
            return true;
        }

        auto subKeyPath = in_rPath.relative_path().remove_filename();
        auto subKeyPathU16 = subKeyPath.wstring();
        auto valueName = in_rPath.filename();
        auto valueNameU16 = valueName.wstring();
        
        assert(subKeyPathU16.length() < REG_MAX_SUBKEY_PATH_LENGTH);
        assert(valueNameU16.length() < REG_MAX_VALUE_NAME_LENGTH);

        wcscpy(out_pSubKey, subKeyPathU16.data());
        wcscpy(out_pValueName, valueNameU16.data());

        return false;
    }

    template <typename T>
    inline bool Read(const std::filesystem::path& in_rPath, T& out_rData)
    {
        HKEY hRootKey{};
        wchar_t subKey[REG_MAX_SUBKEY_PATH_LENGTH]{};
        wchar_t valueName[REG_MAX_VALUE_NAME_LENGTH]{};

        if (!TryParseRegistryPath(in_rPath, hRootKey, subKey, valueName))
            return false;

        HKEY hKey{};

        if (RegOpenKeyExW(hRootKey, subKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
            return false;

        DWORD bufferSize{};
        DWORD dataType{};

        auto result = RegGetValueW(hKey, nullptr, valueName, RRF_RT_ANY, &dataType, nullptr, &bufferSize);

        if (result != ERROR_SUCCESS)
        {
            RegCloseKey(hKey);
            return false;
        }

        result = ERROR_INVALID_FUNCTION;

        if constexpr (std::is_same_v<T, std::string>)
        {
            if (dataType == REG_SZ)
            {
                std::vector<uint8_t> buffer{};
                buffer.reserve(bufferSize);

                result = RegGetValueW(hKey, nullptr, valueName, RRF_RT_REG_SZ, nullptr, buffer.data(), &bufferSize);

                if (result == ERROR_SUCCESS)
                {
                    auto valueSize = WideCharToMultiByte(CP_UTF8, 0, (wchar_t*)buffer.data(), (bufferSize / sizeof(wchar_t)) - 1, nullptr, 0, nullptr, nullptr);
                    out_rData.resize(valueSize);
                    WideCharToMultiByte(CP_UTF8, 0, (wchar_t*)buffer.data(), (bufferSize / sizeof(wchar_t)) - 1, out_rData.data(), valueSize, nullptr, nullptr);
                }
            }
        }
        else if constexpr (std::is_same_v<T, std::filesystem::path>)
        {
            if (dataType == REG_SZ)
            {
                std::vector<uint8_t> buffer{};
                buffer.reserve(bufferSize);

                result = RegGetValueW(hKey, nullptr, valueName, RRF_RT_REG_SZ, nullptr, buffer.data(), &bufferSize);

                if (result == ERROR_SUCCESS)
                    out_rData = reinterpret_cast<wchar_t*>(buffer.data());
            }
        }
        else if constexpr (std::is_same_v<T, uint32_t>)
        {
            result = RegGetValueW(hKey, nullptr, valueName, RRF_RT_DWORD, nullptr, (BYTE*)&out_rData, &bufferSize);
        }
        else if constexpr (std::is_same_v<T, uint64_t>)
        {
            result = RegGetValueW(hKey, nullptr, valueName, RRF_RT_QWORD, nullptr, (BYTE*)&out_rData, &bufferSize);
        }
        else
        {
            static_assert(false, "Unsupported data type.");
        }

        RegCloseKey(hKey);

        return result == ERROR_SUCCESS;
    }

    template <typename T>
    inline bool Write(const std::filesystem::path& in_rPath, const T& out_rData)
    {
        HKEY hRootKey{};
        wchar_t subKey[REG_MAX_SUBKEY_PATH_LENGTH]{};
        wchar_t valueName[REG_MAX_VALUE_NAME_LENGTH]{};

        if (!TryParseRegistryPath(in_rPath, hRootKey, subKey, valueName))
            return false;

        HKEY hKey{};

        if (RegCreateKeyExW(hRootKey, subKey, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS)
            return false;

        BYTE* pData{};
        DWORD dataSize{};
        DWORD dataType{};

        auto isWideString = false;

        if constexpr (std::is_same_v<T, std::string>)
        {
            pData = (BYTE*)out_rData.c_str();
            dataSize = out_rData.size() + 1;
            dataType = REG_SZ;
        }
        else if constexpr (std::is_same_v<T, uint32_t>)
        {
            pData = &out_rData;
            dataSize = sizeof(T);
            dataType = REG_DWORD;
        }
        else if constexpr (std::is_same_v<T, uint64_t>)
        {
            pData = &out_rData;
            dataSize = sizeof(T);
            dataType = REG_QWORD;
        }
        else if constexpr (std::is_same_v<T, std::filesystem::path>)
        {
            pData = (BYTE*)out_rData.c_str();
            dataSize = (wcslen((const wchar_t*)pData) + 1) * sizeof(wchar_t);
            dataType = REG_SZ;
            isWideString = true;
        }
        else
        {
            static_assert(false, "Unsupported data type.");
        }

        auto result = ERROR_INVALID_FUNCTION;

        if (isWideString)
        {
            auto path = in_rPath.wstring();
            result = RegSetValueExW(hKey, path.c_str(), 0, dataType, pData, dataSize);
        }
        else
        {
            auto path = in_rPath.string();
            result = RegSetValueExA(hKey, path.c_str(), 0, dataType, pData, dataSize);
        }

        RegCloseKey(hKey);

        if (result != ERROR_SUCCESS)
            return false;

        return true;
    }
}