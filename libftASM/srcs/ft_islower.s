%ifdef OSX
	%define SUCCESS 1
%elif LINUX
	%define SUCCESS 1
%endif

section	.text
	global ft_islower

ft_islower:
	enter	0, 0	; save register
	cmp	rdi, 122
	jg	fail
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