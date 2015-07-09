%ifdef OSX
	%define WRITE 0x2000004
	%define READ 0x2000003
%elif LINUX
	%define WRITE 1
	%define READ 0
%endif

section	.bss
	buf resb 10
	.size equ $ - buf

section	.text
	global	ft_cat

ft_cat:
	enter 0, 0
	cmp rdi, 0 ; if fd
	jl exit

read_fd:
	push rdi
	mov rax, READ
	lea rsi, [rel buf]
	mov rdx, buf.size
	syscall
	jc error
	cmp rax, 0
	jle error
	jmp write_buf
	
write_buf:
	mov rdx, rax
	mov rax, WRITE
	mov rdi, 1
	lea rsi, [rel buf]
	syscall
	cmp rax, 0
	jl error
	pop rdi
	jmp read_fd ; recurse

error:
	pop	rdi
	leave
	ret

exit:
	leave
	ret

