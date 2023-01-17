#pragma once

class StageListener
{
public:
	enum EIslandType
	{
		Kronos,
		Ares,
		Chaos,
		Rhea,
		Ouranos
	};

	static inline EIslandType m_IslandType = Kronos;

	static void Install();
};

