#pragma once

#include "..\..\Dependencies\xxHash\xxh3.h"
#include "IHashProvider.h"

namespace CMF::System::Hashing
{
	class XXHash64Provider : public IHashProvider<uint64_t>
	{
		XXH3_state_t m_State{};

	public:
		bool Reset() override;
		bool Update(const uint8_t* in_pData, const size_t in_length) override;
		uint64_t Digest() override;
	};
}

#include "XXHash64Provider.inl"
