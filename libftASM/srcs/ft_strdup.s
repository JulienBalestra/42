extern ft_strlen
extern ft_memcpy
extern malloc

section	.text
	global	ft_strdup

ft_strdup:
	enter 0, 0
	cmp rdi, 0
	je exit
	call ft_strlen
	push rdi
	push rax
	mov rdi, rax
	call malloc
	mov rdi, rax
	pop rdx
	pop rsi
	call ft_memcpy

exit:
	leave
	ret
