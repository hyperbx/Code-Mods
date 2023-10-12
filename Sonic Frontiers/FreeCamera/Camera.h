#pragma once

class Camera
{
public:
	static void UpdateImGui();
	static void Update();
	static void Install();
};

CL_SCAN_SIGNATURE(m_SigPhotoModeServiceClass, "\x45\x33\xC9\x4C\x8D\x05\xCC\xCC\xCC\xCC\x48\x8D\x15\xCC\xCC\xCC\xCC\x48\x8D\x0D\xCC\xCC\xCC\xCC\xE9\x73\x3D\xB9\x00", "xxxxxx????xxx????xxx????xxxxx");