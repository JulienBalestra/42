section	.text
	global ft_power

ft_power:
	enter 0, 0	; save register
	imul rdi, rdi
	mov rax, rdi
    leave
    ret
