.section .init9

main:
	/* initialisation de la diode rouge */
	mov.b #2, &50

loop:

/* eteindre */
	mov #20000, R4
	mov.b #0, &49
inc1:
	sub #1, R4
	jnz inc1
	
/* allumer */
	mov #20000, R4
	mov.b #2, &49	
inc2:
	sub #1, R4
	jnz inc2
	
	jmp loop
