#pragma once

class RegistryHelper
{
public:
    static bool ReadString(HKEY hKey, const std::string& subKey, const std::string& valueName, std::string& data)
    {
        HKEY hkResult;

        LONG lResult = RegOpenKeyEx(hKey, subKey.c_str(), 0, KEY_QUERY_VALUE, &hkResult);
        {
            if (lResult != ERROR_SUCCESS)
                return false;
        }

        DWORD dwType;
        DWORD dwSize = 0;

        lResult = RegQueryValueExA(hkResult, valueName.c_str(), NULL, &dwType, NULL, &dwSize);
        {
            if (lResult != ERROR_SUCCESS)
            {
                RegCloseKey(hkResult);
                return false;
            }
        }

        std::vector<char> buffer(dwSize);

        lResult = RegQueryValueExA(hkResult, valueName.c_str(), NULL, &dwType, reinterpret_cast<LPBYTE>(buffer.data()), &dwSize);
        {
            RegCloseKey(hkResult);

            if (lResult != ERROR_SUCCESS)
                return false;
        }

        data.assign(buffer.data(), buffer.size());

        return true;
    }
};