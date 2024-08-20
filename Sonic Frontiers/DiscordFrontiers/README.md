# [Discord Frontiers](https://gamebanana.com/mods/423887)
A mod for Sonic Frontiers that adds Discord rich presence support.

## Mod Integration
If you have a custom stage mod, Discord Frontiers will automatically detect it if the `cyber_name` field in `stagedata.lua` does not follow the `#-#` naming convention of other existing Cyber Space stages.

To provide a custom thumbnail for your stage, create a `DiscordFrontiers.ini` file in your mod's directory and enter the following;
```ini
[Images]
wxdxx=""
```

Replace `wxdxx` with the value of the `name` field in `stagedata.lua` for your custom stage. The value of this field must be a valid URL to an image hosted publicly. You can host your thumbnail on GitHub and copy the raw image link to it into here.

The `Images` section in `DiscordFrontiers.ini` allows you to redirect any Discord image asset. You can find a list of keys [here](https://github.com/hyperbx/Code-Mods/tree/main/Sonic%20Frontiers/DiscordFrontiers/Resources/Images) (minus the `*.png` extension), these can be redirected to a valid URL.

If you need to replace any strings, say if you have a custom character, you can copy `en-GB.json` (for English) from `./Discord Frontiers/Languages/` into your mod's directory and rename it to `DiscordFrontiers.json` (or `DiscordFrontiers.en-GB.json`, if you plan to localise these strings).

You can then remove all strings that you don't intend to modify from the JSON and modify only the strings you need, for example;
```json
{
  "PlayerSonic":       "Shadow",
  "PlayerSuperSonic":  "Super Shadow"
}
```

## Credits
- [Hyper](https://github.com/hyperbx) - programming and reverse-engineering
- [acro](https://github.com/acrolo) - testing and Training Simulator image
- [benhoyt](https://github.com/benhoyt) - [inih](https://github.com/benhoyt/inih)

## Translators
- [LJSTAR](https://twitter.com/LJSTAR_), [Sora](https://github.com/Sora-yx) - Français (France)
- [NextinHKRY](https://github.com/NextinMono) - Italiano (Italy)
- [Lady Lunanova](https://twitter.com/LadyLunanova) - Dutch (Netherlands)
- [Kitzu](https://twitter.com/AsuKitzu) - Deutsch (German)
- [ChaosX](https://twitter.com/ChaosX2006), [Darío](https://github.com/DarioSamo) - Español (Argentina)
- Đo - Nynorsk (Norwegian)
- [Kwasior](https://github.com/ThisKwasior) - Polski (Polish)
- [PTKay](https://github.com/PTKay) - Português (Portugal)
- [Tio Illuminati](https://twitter.com/ImTioIlluminati), [PTKay](https://github.com/PTKay) - Português (Brazil)
- [Nonami](https://gamebanana.com/members/1696613), [ik-01](https://github.com/ik-01) - Русский (Russian)
- [Dunker961](https://github.com/Dunker961) - Українська (Ukrainian)
- [JoeyLaw](https://www.youtube.com/@joeylaw123), [brianuuu](https://github.com/brianuuu) - 日本語 (Japanese)
- [JoeyLaw](https://www.youtube.com/@joeylaw123), [brianuuu](https://github.com/brianuuu) - 中文繁體 (Chinese Traditional)
- [JoeyLaw](https://www.youtube.com/@joeylaw123), [brianuuu](https://github.com/brianuuu) - 中文简体 (Chinese Simplified)
- [Trepe Serafin](https://gamebanana.com/members/2351910) - 한국어 (Korean)
