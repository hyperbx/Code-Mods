#pragma once

namespace app::player
{
	class alignas(8) MsgPlayAnimation : public hh::fnd::MessageAsyncHandlerInplace<MsgPlayAnimation>, public fnd::AppMessage<MsgPlayAnimation>
	{
	private:
		inline static uint32_t MessageID = 0x222E;

	public:
		const char* pAnimationName{};
		float Duration{};

		MsgPlayAnimation() : fnd::AppMessage<MsgPlayAnimation>(MessageID) { }

		MsgPlayAnimation(const char* in_pAnimationName, float in_duration) : MsgPlayAnimation()
		{
			pAnimationName = in_pAnimationName;
			Duration = in_duration;
		}
	};
}