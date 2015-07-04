section .text
    global ft_abs

ft_abs:
	mov rax, rdi
	cmp eax, 0				
	jl neg						
	ret

neg:
	neg rax
	ret