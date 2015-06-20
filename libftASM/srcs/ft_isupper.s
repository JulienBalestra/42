%ifdef OSX
	%define SUCCESS 1
%elif LINUX
	%define SUCCESS 1
%endif

section	.text
	global ft_isupper

ft_isupper:
	enter	0, 0	; save register
	cmp	rdi, 90
	jg	fail
	cmp	rdi, 65
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