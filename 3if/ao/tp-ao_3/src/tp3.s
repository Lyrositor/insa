.section .init9

main:
    /* initialisation de l'écran */
    call #lcd_init
    
    /* emballage des arguments */
    MOV #6, R15
    MOV #7, R14
    
    call #mult
    
    /* deballage de la valeur de retour de mult
       qu'on re-emballe comme argument pour l'appel suivant */
    MOV R13, R15
    
    call #lcd_display_number

/* infinite loop */
done:
    jmp done

mult:
    MOV #0, R13
    
    ret