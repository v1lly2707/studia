.686 
.model flat 
extern  _ExitProcess@4 : PROC
extern  __write : PROC  
extern  __read  : PROC   
extern  _MessageBoxA@16 : PROC 
public  _main 

.data 
    tytul db 'Lab2', 0 
    tekst_pocz db 10, 'Prosze napisac jakis tekst ' 
    db 'i nacisnac Enter', 10 
    koniec_t db ? 
    magazyn db 80 dup (?) 
    nowa_linia db 10 
    liczba_znakow dd ? 

.code 
    _main PROC 

    
    mov ecx, (OFFSET koniec_t) - (OFFSET tekst_pocz) 
    push ecx 
    push OFFSET tekst_pocz  
    push 1  
    call __write  
    add esp, 12  

    
    push 80  
    push OFFSET magazyn 
    push 0  
    call __read  
    add esp, 12  

    
    mov liczba_znakow, eax 
    mov ecx, eax 
    mov ebx, 0  

    ptl: 
        mov dl, magazyn[ebx]  
        
        ; ------ male na duze pl
        cmp dl, 0A5H 
        je polish_a 

        cmp dl, 86H 
        je polish_c 

        cmp dl, 0A9H 
        je polish_e 

        cmp dl, 88H 
        je polish_l 

        cmp dl, 0E4H 
        je polish_n 

        cmp dl, 0A2H 
        je polish_o 

        cmp dl, 98H 
        je polish_s 

        cmp dl, 0ABH 
        je polish_z1 

        cmp dl, 0BEH 
        je polish_z2 

        ; ------ duze na male pl
        cmp dl, 0A4H 
        je polish_a2 

        cmp dl, 8FH 
        je polish_c2 

        cmp dl, 0A8H 
        je polish_e2 

        cmp dl, 9DH 
        je polish_l2 

        cmp dl, 0E3H 
        je polish_n2 

        cmp dl, 0E0H 
        je polish_o2 

        cmp dl, 97H 
        je polish_s2 

        cmp dl, 8DH 
        je polish_z12 

        cmp dl, 0BDH 
        je polish_z22 

        
        cmp dl, 'a'
        jb duze_na_male
        cmp dl, 'z'
        ja duze_na_male
        sub dl, 20H   
        mov magazyn[ebx], dl
        jmp dalej

duze_na_male:
        
        cmp dl, 'A'
        jb inne
        cmp dl, 'Z'
        ja inne
        add dl, 20H   
        mov magazyn[ebx], dl
        jmp dalej

polish_a: 
        mov dl, 0A5H 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_c: 
        mov dl, 0C6H 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_e: 
        mov dl, 0CAH 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_l: 
        mov dl, 0A3H 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_n: 
        mov dl, 0D1H 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_o: 
        mov dl, 0D3H 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_s: 
        mov dl, 8CH 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_z1: 
        mov dl, 8FH 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_z2: 
        mov dl, 0AFH 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_a2: 
        mov dl, 0B9H 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_c2: 
        mov dl, 0E6H 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_e2: 
        mov dl, 0EAH 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_l2: 
        mov dl, 0B3H 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_n2: 
        mov dl, 0F1H 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_o2: 
        mov dl, 0F3H 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_s2: 
        mov dl, 9CH 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_z12: 
        mov dl, 9FH 
        mov magazyn[ebx], dl 
        jmp dalej 

polish_z22: 
        mov dl, 0BFH 
        mov magazyn[ebx], dl 
        jmp dalej 

        
inne:
        cmp dl, 'A' 
        jb znak
        cmp dl, 'Z' 
        jbe dalej   

znak:
        cmp dl, 0AH
        jnz zmiana
        

zmiana: 
        mov dl, '*'
        mov magazyn[ebx],dl
dalej:  
        inc ebx  
        dec ecx 
        jnz ptl  

    push 0 
    push OFFSET tytul 
    push OFFSET magazyn 
    push 0 
    call _MessageBoxA@16 
    add esp, 12  
    push 0 
    call _ExitProcess@4 


   
_main ENDP 
END
