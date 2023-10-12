include Helpers.inc

EXTERN m_pSigCheckHomingTarget : QWORD
EXTERN m_HomingTargetActiveFrames : QWORD
ASM_HOOK CheckHomingTarget, m_pSigCheckHomingTarget
	lea r8, qword ptr [rsp + 30h]
	inc qword ptr [m_HomingTargetActiveFrames]
	mov rax, [m_pSigCheckHomingTarget]
	lea rax, [rax + 5]
	jmp rax
END_ASM_HOOK CheckHomingTarget

end