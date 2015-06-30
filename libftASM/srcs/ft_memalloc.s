extern malloc
extern ft_bzero

section	.text
	global ft_memalloc

ft_memalloc:
	enter	0, 0
	push	rdi
	call	malloc
	cmp	rax, 0
	je	exit
	pop	rdi
	push rdi
	push	rax
	mov	rsi, rdi
	mov	rdi, rax
	call	ft_bzero
	pop	rax

exit:
	pop rdi
	leave
	ret