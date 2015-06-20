%ifdef OSX
	%define SUCCESS 1
%elif LINUX
	%define SUCCESS 1024
%endif

section	.text
	global ft_isalpha

ft_isalpha:
	enter	0, 0	; save register
	cmp	rdi, 122
	jg	fail
	cmp	rdi, 65
	jl	fail
	cmp	rdi, 90
	jg	low
	jmp	success

low:
	cmp	rdi, 97
	jl	fail
	jmp	success

fail:
	mov	rax, 0
	jmp	exit

success:
	mov	rax, SUCCESS ; macro

exit:
	leave
	ret