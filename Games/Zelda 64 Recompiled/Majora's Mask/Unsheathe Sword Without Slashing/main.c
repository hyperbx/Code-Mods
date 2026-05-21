#include "config.h"
#include "global.h"
#include "modding.h"
#include "recomputils.h"

extern s32 sPlayerUseHeldItem;
extern s32 sPlayerHeldItemButtonIsHeldDown;

RECOMP_HOOK_RETURN("Player_UpperAction_ChangeHeldItem") s32 UnsheatheSwordWithoutSlashing(Player* this, PlayState* play)
{
    if (this->heldItemId >= ITEM_SWORD_KOKIRI && this->heldItemId <= ITEM_SWORD_GILDED)
    {
        if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) == 0 &&
            CONFIG_FALLING_ATTACK_BEHAVIOUR == ATTACK_BEHAVIOUR_SLASH)
        {
            return recomphook_get_return_s32();
        }
        
        sPlayerUseHeldItem = sPlayerHeldItemButtonIsHeldDown = false;

        return true;
    }

    return recomphook_get_return_s32();
}
