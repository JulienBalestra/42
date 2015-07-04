extern ft_abs

section	.text
	global ft_tolower

ft_tolower:
	enter	0, 0	; save register
	call ft_abs
	mov rdi, rax
	cmp	rdi, 90
	jg	fail
	cmp	rdi, 65
	jl	fail
	jmp	success

negative:
	mov rdi, 1
	jmp fail

fail:
	mov	rax, rdi
	jmp	exit

success:
    add rdi, 32
	mov	rax, rdi
	jmp exit

exit:
	leave
	ret