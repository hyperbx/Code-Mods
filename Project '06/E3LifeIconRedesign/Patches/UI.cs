using HarmonyLib;
using MelonLoader;
using System.Collections.Generic;
using System.IO;
using UncappedFramerate.Extensions;
using UnityEngine;

namespace E3LifeIconRedesign.Patches
{
    class UI
    {
        public const int CMN_TEXTURE_WIDTH  = 834;
        public const int CMN_TEXTURE_HEIGHT = 834;
        public const int SSN_TEXTURE_WIDTH  = 994;
        public const int SSN_TEXTURE_HEIGHT = 1082;

        public static bool IsCharacterIconsLoaded = false;

        public static Dictionary<string, Texture2D> CharacterIcons = new Dictionary<string, Texture2D>()
        {
            { "Sonic",       new Texture2D(CMN_TEXTURE_WIDTH, CMN_TEXTURE_HEIGHT) },
            { "Shadow",      new Texture2D(CMN_TEXTURE_WIDTH, CMN_TEXTURE_HEIGHT) },
            { "Silver",      new Texture2D(CMN_TEXTURE_WIDTH, CMN_TEXTURE_HEIGHT) },
            { "Tails",       new Texture2D(CMN_TEXTURE_WIDTH, CMN_TEXTURE_HEIGHT) },
            { "Amy",         new Texture2D(CMN_TEXTURE_WIDTH, CMN_TEXTURE_HEIGHT) },
            { "Knuckles",    new Texture2D(CMN_TEXTURE_WIDTH, CMN_TEXTURE_HEIGHT) },
            { "Blaze",       new Texture2D(CMN_TEXTURE_WIDTH, CMN_TEXTURE_HEIGHT) },
            { "Rouge",       new Texture2D(CMN_TEXTURE_WIDTH, CMN_TEXTURE_HEIGHT) },
            { "Omega",       new Texture2D(CMN_TEXTURE_WIDTH, CMN_TEXTURE_HEIGHT) },
            { "Super Sonic", new Texture2D(SSN_TEXTURE_WIDTH, SSN_TEXTURE_HEIGHT) },
        };

        public static List<Sprite> CharacterSprites { get; set; } = new List<Sprite>();

        public static Sprite SuperSonicSprite { get; set; }

        [HarmonyPatch(typeof(global::UI), "Start")]
        class Start
        {
            public static void Postfix()
            {
                if (IsCharacterIconsLoaded)
                    return;

                string textureDir = Path.Combine(MelonHandler.ModsDirectory, "E3LifeIconRedesign", "Resources");

                CharacterSprites.Clear();

                if (!Directory.Exists(textureDir))
                    return;

                foreach (var key in CharacterIcons.Keys)
                {
                    string texturePath = Path.Combine(textureDir, $"{key}.png");

                    if (!File.Exists(texturePath))
                        continue;

                    if (!ImageConversion.LoadImage(CharacterIcons[key], File.ReadAllBytes(texturePath)))
                        continue;

                    if (CharacterIcons[key] == null)
                        continue;

                    int width = key == "Super Sonic"
                        ? SSN_TEXTURE_WIDTH
                        : CMN_TEXTURE_WIDTH;

                    int height = key == "Super Sonic"
                        ? SSN_TEXTURE_HEIGHT
                        : CMN_TEXTURE_HEIGHT;

                    var sprite = Sprite.Create(CharacterIcons[key], new Rect(0, 0, width, height), new Vector2(width / 2, height / 2));

                    if (sprite == null)
                        continue;

                    if (key == "Super Sonic")
                    {
                        SuperSonicSprite = sprite;
                        continue;
                    }

                    CharacterSprites.Add(sprite);
                }

                IsCharacterIconsLoaded = true;
            }
        }

        [HarmonyPatch(typeof(global::UI), "Update")]
        class Update
        {
            public static void Postfix(global::UI __instance)
            {
                // Don't apply for retail HUD.
                if (global::Singleton<global::Settings>.Instance.settings.DisplayType == 0)
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
                        case global::StageManager.PlayerName.Sonic_New:
                        case global::StageManager.PlayerName.Sonic_Fast:
                        case global::StageManager.PlayerName.Princess:
                        case global::StageManager.PlayerName.Snow_Board:
                        case global::StageManager.PlayerName.Metal_Sonic:
                        {
                            if (isSuper)
                            {
                                __instance.LifeHolders[i].sprite = SuperSonicSprite;
                                break;
                            }

                            __instance.LifeHolders[i].sprite = CharacterSprites[0];
                            break;
                        }

                        case global::StageManager.PlayerName.Shadow:
                            __instance.LifeHolders[i].sprite = CharacterSprites[1];
                            break;

                        case global::StageManager.PlayerName.Silver:
                            __instance.LifeHolders[i].sprite = CharacterSprites[2];
                            break;

                        case global::StageManager.PlayerName.Tails:
                            __instance.LifeHolders[i].sprite = CharacterSprites[3];
                            break;

                        case global::StageManager.PlayerName.Amy:
                            __instance.LifeHolders[i].sprite = CharacterSprites[4];
                            break;

                        case global::StageManager.PlayerName.Knuckles:
                            __instance.LifeHolders[i].sprite = CharacterSprites[5];
                            break;

                        case global::StageManager.PlayerName.Blaze:
                            __instance.LifeHolders[i].sprite = CharacterSprites[6];
                            break;

                        case global::StageManager.PlayerName.Rouge:
                            __instance.LifeHolders[i].sprite = CharacterSprites[7];
                            break;

                        case global::StageManager.PlayerName.Omega:
                            __instance.LifeHolders[i].sprite = CharacterSprites[8];
                            break;
                    }
                }
            }
        }
    }
}
