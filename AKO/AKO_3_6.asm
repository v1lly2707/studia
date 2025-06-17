.686
.model flat
public _main
extern __write : PROC
extern __read : PROC
extern _ExitProcess@4: PROC

.data
dekoder db '0123456789ABCDEF'
znaki db 12 dup (?)
dziesiec dd 10

.code
wczytaj_do_EAX_hex PROC

push ebx
push ecx
push edx
push esi
push edi
push ebp

sub esp, 12
mov esi, esp

push dword PTR 10
push esi
push dword PTR 0
call __read

add esp, 12
mov eax, 0

pocz_konw:
mov dl, [esi]
inc esi
cmp dl, 10
je gotowe
;sprawdzenie czy znak jest cyfra
cmp dl, '0'
jb pocz_konw
cmp dl, '9'
ja sprawdzaj_dalej
sub dl, '0' ; zamiana ascii na wartosc cyfry

dopisz:
shl eax, 4 ; przesuniecie logiczne w lewo o 4 bity
or al, dl ; dopisanie ytworzongeo kodu 4-bitowego na 4 ostatnie bity eax

jmp pocz_konw

;sprawzenie czy znak (A-F)

sprawdzaj_dalej:
cmp dl, 'A'
jb pocz_konw
cmp dl, 'F'
ja sprawdzaj_dalej2
sub dl, 'A' - 10
jmp dopisz

;sprzwdzenie (a-f)

sprawdzaj_dalej2:
cmp dl, 'a'
jb pocz_konw
cmp dl, 'f'
ja pocz_konw
sub dl, 'a' - 10
jmp dopisz

gotowe:
add esp,12
pop ebp
pop edi
pop esi
pop edx
pop ecx
pop ebx
ret

wczytaj_do_EAX_hex ENDP

wyswietl_EAX PROC
pusha

mov esi, 10
mov ebx, 10

konwersja:
mov edx, 0
div ebx

add dl, 30H
mov znaki[esi], dl
dec esi
cmp eax, 0
jne konwersja

wypeln:
or esi, esi
jz wyswietl
mov byte PTR znaki[esi], 20H
dec esi
jmp wypeln

wyswietl:
mov byte PTR znaki[0], 0AH
mov byte PTR znaki[11], 0AH
push dword PTR 12
push dword PTR OFFSET znaki
push dword PTR 1
call __write
add esp, 12

popa
ret

wyswietl_EAX ENDP

_main PROC
call wczytaj_do_EAX_hex
call wyswietl_EAX

push 0
call _ExitProcess@4

_main ENDP

END
