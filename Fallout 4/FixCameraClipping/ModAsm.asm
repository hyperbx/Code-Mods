include Helpers.inc

EXTERN g_pSigSetNearDistance : QWORD
EXTERN GetNearDistance : PROTO
ASM_HOOK SetNearDistance, g_pSigSetNearDistance
    movaps xmm0, xmm6
    call   [GetNearDistance]
    movss  xmm3, xmm0
    mov    rcx, [g_pSigSetNearDistance]
    lea    rcx, [rcx + 8]
    jmp    rcx
END_ASM_HOOK SetNearDistance

end