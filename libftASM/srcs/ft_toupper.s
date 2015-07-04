
section	.text
	global ft_toupper

ft_toupper:
	enter	0, 0	; save register
	cmp	rdi, 122
	jg	fail
	cmp	rdi, 97
	jl	fail
	jmp	success

fail:
	mov	rax, rdi
	jmp	exit

success:
    sub rdi, 32
	mov	rax, rdi
	jmp exit

exit:
	leave
	ret