ASM_HOOK_START MACRO NAME, ADDRESS
.data
public original_&NAME&
original_&NAME& QWORD ADDRESS
.code
impl_&NAME& proc
ENDM

ASM_HOOK_END MACRO NAME
impl_&NAME& endp
ENDM