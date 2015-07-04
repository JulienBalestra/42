section	.text
	global ft_square

ft_square:
	enter 0, 0	; save register
	imul rdi, rdi
	mov rax, rdi
    leave
    ret
