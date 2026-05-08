; void my_strcopy64(char *dst, const char *src, long len)
; System V AMD64: rdi=dst, rsi=src, rdx=len

global my_strcopy64

section .text

my_strcopy64:
    mov     rcx, rdx
    inc     rcx

    cmp     rdi, rsi
    jbe     .forward
    lea     rax, [rsi + rcx]
    cmp     rdi, rax
    jae     .forward

.backward:
    add     rsi, rcx
    dec     rsi
    add     rdi, rcx
    dec     rdi
    std
    rep     movsb
    cld
    ret

.forward:
    cld
    rep     movsb
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
