#pragma once

class Camera
{
public:
	static void Install();
	static void Shake(float amount = 1.0f, float duration = 1.0f, float speed = 1.0f);
};

