#pragma once

#define CMN_LOADER_API __cdecl
#define CMN_LOADER_API_VERSION 1
#define CMN_LOADER_API_EXPORT_NAME CommonLoader_GetAPIPointer
#define CMN_LOADER_STRINGIFY(X) #X
#define CMN_LOADER_XSTRINGIFY(X) CMN_LOADER_STRINGIFY(X)

#ifndef CMN_LOADER_HOST_MODULES
#define CMN_LOADER_HOST_MODULES "d3d9.dll", "d3d11.dll"
#endif

#define CMN_LOADER_STATE_SKIP_SIG_VALIDATION 0
#define CMN_LOADER_STATE_MAX 1
#define CMN_LOADER_STATE_INVALID -1

#define DECLARE_API_FUNC(RETURN_TYPE, NAME, ...) RETURN_TYPE (CMN_LOADER_API *NAME)(__VA_ARGS__) = nullptr;

struct AssemblerResult
{
	size_t instruction_count{};
	size_t length{};
	unsigned char* data{};
	const char* error_string{};

	// Private data
#ifdef CMN_LOADER_IMPL
	~AssemblerResult();
#endif
};

struct CommonLoaderAPI
{
	DECLARE_API_FUNC(int, GetVersion);
	DECLARE_API_FUNC(void*, ScanSignature, const char* pattern, const char* mask);
	DECLARE_API_FUNC(void*, ScanSignatureEx, const char* pattern, const char* mask, void* begin, size_t size);
	DECLARE_API_FUNC(int, GetApplicationOption, const char* key, char* out, size_t out_size);
	DECLARE_API_FUNC(int, GetApplicationOptionEx, const char* section, const char* key, char* out, size_t out_size);
	DECLARE_API_FUNC(void, SaveApplicationOptions);
	DECLARE_API_FUNC(AssemblerResult*, CompileAssembly, const char* code);
	DECLARE_API_FUNC(void, FreeAssemblerObject, AssemblerResult*);
	DECLARE_API_FUNC(void, SetAssemblerSymbol, const char* name, uint64_t value);
	DECLARE_API_FUNC(bool, GetAssemblerSymbol, const char* name, uint64_t* out);
	DECLARE_API_FUNC(bool, RemoveAssemblerSymbol, const char* name);
	DECLARE_API_FUNC(void, SetState, size_t state, size_t value);
	DECLARE_API_FUNC(void, SetStateFlag, size_t state, size_t flag, bool set);
	DECLARE_API_FUNC(size_t, GetState, size_t state);
};

typedef const CommonLoaderAPI* (CommonLoader_GetAPI_t)();
inline const CommonLoaderAPI* CommonLoader_GetAPI()
{
	static const CommonLoaderAPI* api = nullptr;
	if (api != nullptr)
	{
		return api;
	}

	const char* hosts[] = { CMN_LOADER_HOST_MODULES };

	for (int i = 0; i < sizeof(hosts) / sizeof(hosts[0]); i++)
	{
		HMODULE module = GetModuleHandleA(hosts[i]);
		if (module == nullptr)
		{
			continue;
		}

		CommonLoader_GetAPI_t* getAPI = (CommonLoader_GetAPI_t*)GetProcAddress(module, CMN_LOADER_XSTRINGIFY(CMN_LOADER_API_EXPORT_NAME));
		if (getAPI)
		{
			return api = getAPI();
		}
	}

	return api;
};

#undef DECLARE_API_FUNC