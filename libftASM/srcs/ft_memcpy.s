section	.text
	global	ft_memcpy

ft_memcpy:
	enter 0, 0
	push rdi
	mov rcx, rdx
	rep movsb
	pop rax
	leave
	ret