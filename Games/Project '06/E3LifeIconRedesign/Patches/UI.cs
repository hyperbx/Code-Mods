using HarmonyLib;
using MelonLoader.Utils;
using System.Collections.Generic;
using System.IO;
using UncappedFramerate.Extensions;
using UnityEngine;

namespace E3LifeIconRedesign.Patches
{
    class UI
    {
        private const int _kTextureWidthCommon = 834;
        private const int _kTextureHeightCommon = 834;
        private const int _kTextureWidthSuperSonic = 994;
        private const int _kTextureHeightSuperSonic = 1082;

        private static bool _isCharacterIconsLoaded = false;

        private static Dictionary<string, Texture2D> _characterIcons = new Dictionary<string, Texture2D>()
        {
            { "Sonic",       new Texture2D(_kTextureWidthCommon, _kTextureHeightCommon) },
            { "Shadow",      new Texture2D(_kTextureWidthCommon, _kTextureHeightCommon) },
            { "Silver",      new Texture2D(_kTextureWidthCommon, _kTextureHeightCommon) },
            { "Tails",       new Texture2D(_kTextureWidthCommon, _kTextureHeightCommon) },
            { "Amy",         new Texture2D(_kTextureWidthCommon, _kTextureHeightCommon) },
            { "Knuckles",    new Texture2D(_kTextureWidthCommon, _kTextureHeightCommon) },
            { "Blaze",       new Texture2D(_kTextureWidthCommon, _kTextureHeightCommon) },
            { "Rouge",       new Texture2D(_kTextureWidthCommon, _kTextureHeightCommon) },
            { "Omega",       new Texture2D(_kTextureWidthCommon, _kTextureHeightCommon) },
            { "Super Sonic", new Texture2D(_kTextureWidthSuperSonic, _kTextureHeightSuperSonic) },
        };

        private static List<Sprite> _characterSprites { get; set; } = new List<Sprite>();

        private static Sprite _superSonicSprite { get; set; }

        [HarmonyPatch(typeof(global::UI), "Start")]
        class Start
        {
            public static void Postfix()
            {
                if (_isCharacterIconsLoaded)
                    return;

                string textureDir = Path.Combine(MelonEnvironment.ModsDirectory, "E3LifeIconRedesign", "Resources");

                _characterSprites.Clear();

                if (!Directory.Exists(textureDir))
                    return;

                foreach (var key in _characterIcons.Keys)
                {
                    string texturePath = Path.Combine(textureDir, $"{key}.png");

                    if (!File.Exists(texturePath))
                        continue;

                    if (!ImageConversion.LoadImage(_characterIcons[key], File.ReadAllBytes(texturePath)))
                        continue;

                    if (_characterIcons[key] == null)
                        continue;

                    var width = key == "Super Sonic"
                        ? _kTextureWidthSuperSonic
                        : _kTextureWidthCommon;

                    var height = key == "Super Sonic"
                        ? _kTextureHeightSuperSonic
                        : _kTextureHeightCommon;

                    var sprite = Sprite.Create(_characterIcons[key], new Rect(0, 0, width, height), new Vector2(width / 2, height / 2));

                    if (sprite == null)
                        continue;

                    if (key == "Super Sonic")
                    {
                        _superSonicSprite = sprite;
                        continue;
                    }

                    _characterSprites.Add(sprite);
                }

                _isCharacterIconsLoaded = true;
            }
        }

        [HarmonyPatch(typeof(global::UI), "Update")]
        class Update
        {
            public static void Postfix(global::UI __instance)
            {
                // Don't apply for retail HUD.
                if (Singleton<Settings>.Instance.settings.DisplayType == 0)
                    return;

                var playerType = __instance.GetFieldValue<global::StageManager>("StageManager")
                                           .GetFieldValue<global::StageManager.PlayerName>("Player");

                var playerManager = __instance.GetFieldValue<global::PlayerManager>("PM");

                bool isSuper = playerManager.sonic != null && playerManager.sonic.GetFieldValue<bool>("IsSuper") ||
                    playerManager.sonic_fast != null && playerManager.sonic_fast.GetFieldValue<bool>("IsSuper");

                for (int i = 0; i < __instance.LifeHolders.Length; i++)
                {
                    __instance.LifeHolders[i].gameObject.transform.localScale = isSuper
                        ? new Vector3(0.98f, 1.0f, 1.0f)
                        : new Vector3(0.78f, 0.8f, 0.8f);

                    switch (playerType)
                    {
                        case StageManager.PlayerName.Sonic_New:
                        case StageManager.PlayerName.Sonic_Fast:
                        case StageManager.PlayerName.Princess:
                        case StageManager.PlayerName.Snow_Board:
                        case StageManager.PlayerName.Metal_Sonic:
                        {
                            if (isSuper)
                            {
                                __instance.LifeHolders[i].sprite = _superSonicSprite;
                                break;
                            }

                            __instance.LifeHolders[i].sprite = _characterSprites[0];
                            break;
                        }

                        case StageManager.PlayerName.Shadow:
                            __instance.LifeHolders[i].sprite = _characterSprites[1];
                            break;

                        case StageManager.PlayerName.Silver:
                            __instance.LifeHolders[i].sprite = _characterSprites[2];
                            break;

                        case StageManager.PlayerName.Tails:
                            __instance.LifeHolders[i].sprite = _characterSprites[3];
                            break;

                        case StageManager.PlayerName.Amy:
                            __instance.LifeHolders[i].sprite = _characterSprites[4];
                            break;

                        case StageManager.PlayerName.Knuckles:
                            __instance.LifeHolders[i].sprite = _characterSprites[5];
                            break;

                        case StageManager.PlayerName.Blaze:
                            __instance.LifeHolders[i].sprite = _characterSprites[6];
                            break;

                        case StageManager.PlayerName.Rouge:
                            __instance.LifeHolders[i].sprite = _characterSprites[7];
                            break;

                        case StageManager.PlayerName.Omega:
                            __instance.LifeHolders[i].sprite = _characterSprites[8];
                            break;
                    }
                }
            }
        }
    }
}
