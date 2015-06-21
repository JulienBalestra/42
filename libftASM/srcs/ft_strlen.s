section	.text
	global	ft_strlen

ft_strlen:
	enter 0, 0
	push rdi
	mov	rax, 0
	mov	rcx, -1
	repne scasb ; compare memory byte
	mov	rax, -2
	sub	rax, rcx

exit:
	pop	rdi
	leave
	ret
