.section .init9

main:
    /* initialisation de l'écran */
    call #lcd_init

    JMP ex3

ex2:
    /* emballage des arguments */
    MOV #6, R15
    MOV #7, R14

    CALL #mult

    /* deballage de la valeur de retour de mult
       qu'on re-emballe comme argument pour l'appel suivant */
    MOV R13, R15

    CALL #lcd_display_number

    JMP done

ex3:
    /* emballage des arguments */
    MOV #6, &0x0130
    MOV #7, &0x0138

    /* deballage de la valeur de retour de mult
       qu'on re-emballe comme argument pour l'appel suivant */
    MOV &0x013A, R15

    CALL #lcd_display_number

    JMP done

/* infinite loop */
done:
    JMP done

mult:
    MOV #0, R13
    MOV R14, R12

multloop:
    ADD R15, R13
    SUB #1, R12
    JNZ multloop

multdone:
    RET
