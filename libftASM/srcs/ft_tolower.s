section	.text
	global ft_tolower

ft_tolower:
	enter	0, 0	; save register
	cmp	rdi, 122
	jg	success
	cmp	rdi, 97
	jl	success
	jmp	fail

fail:
	mov	rax, rdi
	jmp	exit

success:
    add rdi, 32
	mov	rax, rdi

exit:
	leave
	ret