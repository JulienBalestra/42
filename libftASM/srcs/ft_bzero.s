section	.text
	global ft_bzero

ft_bzero:
	enter	0, 0
	push rdi

while:
	cmp	rsi, 0
	jle	exit
	mov	byte[rdi], 0 ; eq 0b
	inc	rdi
	dec	rsi
	jmp	while

exit:
	pop rdi
	leave
	ret