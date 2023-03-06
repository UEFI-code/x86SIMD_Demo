.code _text

SIMD_ADD_ALIGN PROC PUBLIC

movaps xmm0, [rcx];
movaps xmm1, [rdx];
addps xmm0, xmm1;
movaps [r8], xmm0
ret

SIMD_ADD_ALIGN ENDP

END