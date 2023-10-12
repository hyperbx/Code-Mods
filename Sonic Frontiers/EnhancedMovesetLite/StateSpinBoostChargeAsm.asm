include Helpers.inc

EXTERN m_pSigDisableSpinChargeOriginalChargeInput : QWORD
EXTERN m_IsSpinCharge : BYTE
ASM_HOOK SpinChargeInputHandler, m_pSigDisableSpinChargeOriginalChargeInput
	mov  al, m_IsSpinCharge
	test al, al
	mov  rax, [m_pSigDisableSpinChargeOriginalChargeInput]
	lea  rax, [rax + 5]
	jmp  rax
END_ASM_HOOK SpinChargeInputHandler

end