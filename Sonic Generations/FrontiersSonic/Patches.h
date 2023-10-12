#pragma once

class Patches
{
public:
	static void Install()
	{
        // Disable physics death state for enemies.
        WRITE_NOP(0xBDF589, 5);

        // Restore XButtonHoming string to disable the HMM code.
        WRITE_STRING(0x15FA418, "XButtonHoming");

        // Loop dash ring animations.
        WRITE_MEMORY(0x1276D20, uint8_t, 0x1D);
        WRITE_MEMORY(0x1276D87, uint8_t, 0x1D);

        // Replace animations with the jump ball.
        WRITE_MEMORY(0x12733A2, const char*, "sn_ball_loop"); // JumpShortBegin
        WRITE_MEMORY(0x1273409, const char*, "sn_ball_loop"); // JumpShort
        WRITE_MEMORY(0x1273470, const char*, "sn_ball_loop"); // JumpShortTop
        WRITE_MEMORY(0x127380A, const char*, "sn_ball_loop"); // JumpHurdleL
        WRITE_MEMORY(0x1273876, const char*, "sn_ball_loop"); // JumpHurdleR
        WRITE_MEMORY(0x1273A12, const char*, "sn_ball_loop"); // SquatToJump

        // Disable boost particles.
        WRITE_MEMORY(0x15A3568, uint8_t, 0x00); // ef_bo_sha_yh1_boost1
        WRITE_MEMORY(0x15E9048, uint8_t, 0x00); // ef_ch_sng_yh1_boost1
        WRITE_MEMORY(0x15E9060, uint8_t, 0x00); // ef_ch_sng_yh1_boost2
        WRITE_MEMORY(0x15EE774, uint8_t, 0x00); // ef_bo_sha_yh1_hyper_sn
        WRITE_MEMORY(0x15EE78C, uint8_t, 0x00); // ef_bo_sha_yh1_hyper_sn
        WRITE_MEMORY(0x15F99F8, uint8_t, 0x00); // ef_ch_sps_yh1_boost1
        WRITE_MEMORY(0x15F9A10, uint8_t, 0x00); // ef_ch_sps_yh1_boost2
        WRITE_MEMORY(0x164330C, uint8_t, 0x00); // ef_st_ssh_yh1_bobsled_boost

        // Disable spin dash on dash panels.
        WRITE_MEMORY(0xE0AC1C, uint8_t, 0xE9, 0x27, 0x01, 0x00, 0x00);
        WRITE_MEMORY(0xE0C734, uint8_t, 0xE9, 0x27, 0x01, 0x00, 0x00);

        // Right mouth bones.
        WRITE_MEMORY(0x15E8F9C, const char*, "MouthR_Reference");
        WRITE_MEMORY(0x15E8FA4, const char*, "MouthR_Position");
        WRITE_MEMORY(0x15E8FAC, const char*, "MouthR_Jaw");
        WRITE_MEMORY(0x15E8FB4, const char*, "MouthR_Teeth_Low");
        WRITE_MEMORY(0x15E8FBC, const char*, "MouthR_Lip_C");
        WRITE_MEMORY(0x15E8FC4, const char*, "MouthR_Teeth_Up");
        WRITE_MEMORY(0x15E8FCC, const char*, "MouthR_Lip_L");
        WRITE_MEMORY(0x15E8FD4, const char*, "MouthR_Lip_R");
        WRITE_MEMORY(0x15E8FDC, const char*, "MouthR_Nose");

        // Left mouth bones.
        WRITE_MEMORY(0x15E8FE4, const char*, "MouthL_Reference");
        WRITE_MEMORY(0x15E8FEC, const char*, "MouthL_Position");
        WRITE_MEMORY(0x15E8FF4, const char*, "MouthL_Jaw");
        WRITE_MEMORY(0x15E8FFC, const char*, "MouthL_Teeth_Low");
        WRITE_MEMORY(0x15E9004, const char*, "MouthL_Lip_C");
        WRITE_MEMORY(0x15E900C, const char*, "MouthL_Teeth_Up");
        WRITE_MEMORY(0x15E9014, const char*, "MouthL_Lip_L");
        WRITE_MEMORY(0x15E901C, const char*, "MouthL_Lip_R");
        WRITE_MEMORY(0x15E9024, const char*, "MouthL_Nose");
	}
};

