section .text
    global ft_memset

ft_memset:
	push rdi
	mov rax, rsi
	mov rcx, rdx
	cld
	rep stosb
	jmp exit

exit:
	pop rax
	leave
	ret