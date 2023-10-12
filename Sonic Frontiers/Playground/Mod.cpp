#include "ScriptSequenceHelper.h"

EXPORT void OnFrame()
{
	if (!((GetAsyncKeyState(VK_F1) & 0x8000) != 0))
		return;

	int lv = ScriptSequenceHelper::LuaCallT<int>("GetGuardLevel");

	printf("%d\n", lv);
}