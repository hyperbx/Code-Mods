#include "Patches.h"
#include "Mod.h"
#include "MemoryHelper.h"

void Patches::Install()
{
	// Freeze lives.
	WRITE_NOP(0xD59A67, 6);

	// Disable 1-UP from rings.
	WRITE_NOP(0xE68562, 5);

	// Remove 1-UP object.
	WRITE_MEMORY(0x166463C, uint8_t, 0x00);

	// Remove 1-UP item box.
	WRITE_MEMORY(0x167DDE4, uint8_t, 0x00);

	// Always active homing reticle.
	// TODO: make this update in real-time.
	// WRITE_JUMP(0xDEBC5B, (void*)0xDEBC8C);

	// Disable boost energy particles.
	// TODO: make this instantly add boost energy to the gauge.
	WRITE_JUMP(0x112435C, (void*)0x112440C);

	// Disable trick combo counter.
	WRITE_JUMP(0x52EC7D, (void*)0x52EF8D);

	// Disable title loading video (fixes hang on title screen).
	WRITE_MEMORY(0xD6966E, uint8_t, 0xE9, 0x14, 0x01, 0x00, 0x00);

	// Disable loading hints (fixes mission text appearing on the loading screen).
	WRITE_MEMORY(0x448959, uint8_t, 0xE9, 0x12, 0x01, 0x00, 0x00);

	// Force enable the boost button prompt (in case of patch conflicts).
	WRITE_MEMORY(0x109BC7C, uint8_t, 0x8B, 0x8D, 0x5C, 0x02, 0x00, 0x00);

	if (!Mod::homingReticle)
	{
		// Switch to Generations' homing reticles.
		MemoryHelper::WriteProtected((void*)0x15E36E4, "_b", 2);
		MemoryHelper::WriteProtected((void*)0x155E5E8, "_b", 2);

#if _DEBUG
		printf("[Forces HUD] Homing reticle is disabled!\n");
#endif
	}
}