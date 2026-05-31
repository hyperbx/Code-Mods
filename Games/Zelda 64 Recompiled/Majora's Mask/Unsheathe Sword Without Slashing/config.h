#pragma once

#include <recompconfig.h>

#define CONFIG_FALLING_ATTACK_BEHAVIOUR recomp_get_config_u32("falling_attack_behaviour")

enum AttackBehaviour
{
    ATTACK_BEHAVIOUR_UNSHEATHE,
    ATTACK_BEHAVIOUR_SLASH
};
