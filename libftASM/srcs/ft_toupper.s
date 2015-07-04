extern ft_abs

section	.text
	global ft_toupper

ft_toupper:
	enter	0, 0	; save register
	call ft_abs
	mov rdi, rax
	cmp	rdi, 122
	jg	fail
	cmp	rdi, 97
	jl	fail
	jmp	success

negative:
	mov rdi, 1
	jmp fail

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