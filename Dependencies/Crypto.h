#pragma once

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <wincrypt.h>

class Crypto
{
public:
	/// <summary>
	/// Computes an MD5 hash using the specified data.
	/// </summary>
	/// <param name="pHash">Output hash buffer (must be 16 bytes).</param>
	/// <param name="pData">Input data.</param>
	/// <param name="len">Data length.</param>
	static bool ComputeMD5(uint8_t* pHash, const void* pData, size_t len)
	{
		/*
			References:
			- https://docs.microsoft.com/en-us/windows/win32/seccrypto/example-c-program--creating-an-md-5-hash-from-file-content
			- https://github.com/GerbilSoft/rom-properties/blob/master/src/librpbase/crypto/MD5HashCAPI.cpp
		*/

		HCRYPTPROV hProvider;
		HCRYPTHASH hHash;

		assert(pHash != nullptr);
		assert(pData != nullptr);

		if (!pHash || !pData)
		{
			// Invalid parameters.
			return -EINVAL;
		}

		// Get handle to the crypto provider.
		if (!CryptAcquireContext(&hProvider, nullptr, nullptr, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT))
		{
			// Failed to get a handle to the crypto provider.
			return GetLastError();
		}

		// Create an MD5 hash object.
		if (!CryptCreateHash(hProvider, CALG_MD5, 0, 0, &hHash))
		{
			// Error creating the MD5 hash object.
			int ret = GetLastError();
			CryptReleaseContext(hProvider, 0);
			return ret;
		}

		// Hash the data.
		if (!CryptHashData(hHash, static_cast<const BYTE*>(pData), len, 0))
		{
			// Error hashing the data.
			int ret = GetLastError();
			CryptDestroyHash(hHash);
			CryptReleaseContext(hProvider, 0);
			return ret;
		}

		// Get the hash data.
		int ret = 0;
		DWORD cbHash = 16;
		if (!CryptGetHashParam(hHash, HP_HASHVAL, pHash, &cbHash, 0))
		{
			// Error getting the hash.
			ret = GetLastError();
		}
		else if (cbHash != 16)
		{
			// Wrong hash length.
			ret = -EINVAL;
		}

		return ret;
	}
};