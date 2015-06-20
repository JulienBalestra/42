extern	ft_isalpha
extern	ft_isdigit

%ifdef OSX
	%define SUCCESS 1
%elif LINUX
	%define SUCCESS 8
%endif

section	.text
	global	ft_isalnum

ft_isalnum:
	enter	0, 0
	call	ft_isalpha
	cmp	rax, 0
	jne	success	
	call	ft_isdigit
	cmp	rax, 0
	jne	success
	jmp exit

success:
	mov rax, SUCCESS
	jmp exit

exit:
	leave
	ret