%ifdef OSX
	%define SUCCESS 1
%elif LINUX
	%define SUCCESS 1
%endif

section	.text
	global ft_isblank

ft_isblank:
	enter	0, 0	; save register
	cmp	rdi, 9
	je	success
	cmp	rdi, 32
	je	success
	jmp	fail

fail:
	mov	rax, 0
	jmp	exit

success:
	mov	rax, SUCCESS ; macro

exit:
	leave
	ret