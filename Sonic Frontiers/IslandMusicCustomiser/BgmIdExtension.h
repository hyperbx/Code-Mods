#pragma once

namespace app::snd
{
	class BgmIdExtension
	{
	public:
		INSERT_PADDING(0x9C);
		int TrackIndex;
		INSERT_PADDING(0x30);

		virtual ~BgmIdExtension() = default;
	};
}