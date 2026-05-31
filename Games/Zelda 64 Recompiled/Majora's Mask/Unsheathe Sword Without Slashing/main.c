#include "config.h"
#include <Framework.h>
#include <global.h>

extern s32 sPlayerUseHeldItem;
extern s32 sPlayerHeldItemButtonIsHeldDown;

DECLARE_POSTFIX_HOOK(s32, UnsheatheSwordWithoutSlashing, "Player_UpperAction_ChangeHeldItem", ((Player*, this)) ((PlayState*, play)))
{
    s32 result = recomphook_get_return_s32();

    if (this->heldItemId >= ITEM_SWORD_KOKIRI && this->heldItemId <= ITEM_SWORD_GILDED)
    {
        if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) == 0 &&
            CONFIG_FALLING_ATTACK_BEHAVIOUR == ATTACK_BEHAVIOUR_SLASH)
        {
            return result;
        }
        
        sPlayerUseHeldItem = sPlayerHeldItemButtonIsHeldDown = false;
    }

    return result;
}
