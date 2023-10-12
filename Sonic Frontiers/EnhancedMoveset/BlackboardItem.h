#pragma once

namespace app::player
{
	class alignas(16) BlackboardItem : public BlackboardContent
	{
		inline static const char* ms_pBlackboardName = "BlackboardItem";

	public:
		int32_t Rings{};
		int8_t Unk1{};
		int8_t Unk2{};
		int8_t Unk3{};
		int8_t Unk4{};
		int8_t Unk5{};
		int8_t Unk6{};
		int8_t Unk7{};
		int8_t Unk8{};
		int8_t Unk9{};
		int8_t Unk10{};
		int8_t Unk11{};
		int8_t Unk12{};

		size_t GetNameHash() override
		{
			return csl::ut::StringMapOperation::hash(ms_pBlackboardName);
		}

		static const char* GetBlackboardName()
		{
			return ms_pBlackboardName;
		}
	};
}