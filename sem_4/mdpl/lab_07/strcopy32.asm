; void my_strcopy32(char *dst, const char *src, int len)
; cdecl: параметры через стек [esp+4], [esp+8], [esp+12]

global my_strcopy32

section .text

my_strcopy32:
    push    ebp
    mov     ebp, esp
    push    esi
    push    edi

    mov     edi, [ebp + 8]
    mov     esi, [ebp + 12]
    mov     ecx, [ebp + 16]
    inc     ecx

    cmp     edi, esi
    jbe     .forward
    lea     eax, [esi + ecx]
    cmp     edi, eax
    jae     .forward

.backward:
    add     esi, ecx
    dec     esi
    add     edi, ecx
    dec     edi
    std
    rep     movsb
    cld
    jmp     .done

.forward:
    cld
    rep     movsb

.done:
    pop     edi
    pop     esi
    pop     ebp
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
