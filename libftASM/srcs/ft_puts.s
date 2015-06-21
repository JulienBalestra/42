extern	ft_strlen

%ifdef OSX
	%define WRITE 0x2000004
%elif LINUX
	%define WRITE 1
%endif


section	.data
okret: db 0x0a
nullret: db "(null)", 10, 0

section	.text
	global ft_puts


ft_puts:
	enter	0, 0
	cmp	rdi, 0
	je	null
	call	ft_strlen
	mov	rsi, rdi
	mov	rdx, rax
	mov	rax, WRITE
	mov	rdi, 1
	syscall
	jc	exit
	mov	rax, WRITE
	mov	rsi, okret
	mov	rdx, 1
	syscall
	jmp	exit

null:
	mov	rax, WRITE
	mov	rdi, 1
	mov	rsi, nullret
	mov	rdx, 7
	syscall

exit:
	leave
	ret