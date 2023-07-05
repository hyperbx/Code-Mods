#pragma once

namespace app::player
{
	class alignas(16) BlackboardStatus : public BlackboardContent
	{
		inline static const char* ms_pBlackboardName = "BlackboardStatus";

	public:
		INSERT_PADDING(0x10);
		int64_t StateFlags;
		int64_t WorldFlags;
		INSERT_PADDING(0xF0);
		bool IsIslandSideView;
		INSERT_PADDING(0x4F);

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