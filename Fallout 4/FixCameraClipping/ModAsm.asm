include Helpers.inc

EXTERN g_pSigSetNearDistance : QWORD
EXTERN g_pNiCameraSingleton : QWORD
EXTERN GetNearDistance : PROTO

ASM_HOOK SetNearDistance_1_10_163, g_pSigSetNearDistance
    movaps xmm0, xmm6
    call   [GetNearDistance]
    movss  xmm3, xmm0
    mov    rcx, [g_pNiCameraSingleton]  ; This register store happens before our hook in the original game
    mov    rcx, [rcx]                   ; code and gets overwritten by the call to GetNearDistance, so we
                                        ; restore it here manually. push and pop does not apply.
                                        ;
                                        ; An alternative fix would be to write GetNearDistance entirely in
                                        ; assembly, with careful use of any available registers, but I'd
                                        ; rather not do something like that right now. Maybe in the future
                                        ; for supporting other versions of Fallout 4, if necessary.
    mov    rax, [g_pSigSetNearDistance]
    lea    rax, [rax + 8]
    jmp    rax
END_ASM_HOOK SetNearDistance_1_10_163

ASM_HOOK SetNearDistance_1_10_984, g_pSigSetNearDistance
    movaps xmm0, xmm6
    call   [GetNearDistance]
    movss  xmm3, xmm0
    mov    rax, [g_pSigSetNearDistance]
    lea    rax, [rax + 8]
    jmp    rax
END_ASM_HOOK SetNearDistance_1_10_984

end