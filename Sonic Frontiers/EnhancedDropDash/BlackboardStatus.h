#pragma once

namespace app::player
{
	class alignas(16) BlackboardStatus : public BlackboardContent
	{
		inline static const char* ms_pBlackboardName = "BlackboardStatus";

	public:
		INSERT_PADDING(16);
		int64_t field_30;
		int64_t StateParameter;
		INSERT_PADDING(319);

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