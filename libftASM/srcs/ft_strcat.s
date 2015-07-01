section	.text
	global	ft_strcat

ft_strcat:
	enter 0, 0
    mov	rcx, rdi ; dest
	mov	rbx, rsi ; src

find_end:
	cmp byte[rcx], 0
	je char_cpy
	inc rcx
	jmp find_end

char_cpy:
	cmp byte[rbx], 0
	je exit
	mov al, byte[rbx]
	mov byte[rcx], al ; invalid combination of opcode and operands
	inc rcx
	inc rbx
	jmp char_cpy

zeroed:
    mov byte[rcx], 0
    jmp end_str

end_str:
	cmp byte[rcx], 0
	je exit
	jmp zeroed

exit:
	mov rax, rdi
	leave
	ret