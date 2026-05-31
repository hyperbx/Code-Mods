#include "config.h"
#include "global.h"
#include "modding.h"
#include "recomputils.h"

static Player* g_pPlayer;

extern s32 sPlayerUseHeldItem;
extern s32 sPlayerHeldItemButtonIsHeldDown;

RECOMP_HOOK("Player_UpperAction_ChangeHeldItem") void UnsheatheSwordWithoutSlashing_Prefix(Player* this, PlayState* play)
{
    g_pPlayer = this;
}

RECOMP_HOOK_RETURN("Player_UpperAction_ChangeHeldItem") s32 UnsheatheSwordWithoutSlashing_Postfix()
{
    s32 result = recomphook_get_return_s32();

    if (g_pPlayer->heldItemId >= ITEM_SWORD_KOKIRI && g_pPlayer->heldItemId <= ITEM_SWORD_GILDED)
    {
        if ((g_pPlayer->actor.bgCheckFlags & BGCHECKFLAG_GROUND) == 0 &&
            CONFIG_FALLING_ATTACK_BEHAVIOUR == ATTACK_BEHAVIOUR_SLASH)
        {
            return result;
        }
        
        sPlayerUseHeldItem = sPlayerHeldItemButtonIsHeldDown = false;
    }

    return result;
}
