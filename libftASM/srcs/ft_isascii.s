%ifdef OSX
	%define SUCCESS 1
%elif LINUX
	%define SUCCESS 1
%endif

section	.text
	global ft_isascii

ft_isascii:
	enter	0, 0	; save register
	cmp	rdi, 0
	jl	fail
	cmp	rdi, 127
	jg	fail
	jmp	success

fail:
	mov	rax, 0
	jmp	exit

success:
	mov	rax, SUCCESS ; macro

exit:
	leave
	ret