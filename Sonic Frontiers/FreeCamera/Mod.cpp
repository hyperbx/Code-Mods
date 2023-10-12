EXPORT void Init()
{
	Configuration::Load();

	Camera::Install();
	DearImGuiContext::Install();
}

EXPORT void OnFrame()
{
	Camera::Update();
}