%ifdef OSX
	%define SUCCESS 1
%elif LINUX
	%define SUCCESS 16384
%endif

section	.text
	global ft_isprint

ft_isprint:
	enter	0, 0	; save register
	cmp	rdi, 32
	jl	fail
	cmp	rdi, 126
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