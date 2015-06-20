
section	.text
	global ft_toupper

ft_toupper:
	enter	0, 0	; save register
	cmp	rdi, 90
	jg	success
	cmp	rdi, 65
	jl	success
	jmp	fail

fail:
	mov	rax, rdi
	jmp	exit

success:
    sub rdi, 32
	mov	rax, rdi

exit:
	leave
	ret