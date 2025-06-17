.686
.model flat
public _main
extern __write : PROC
extern __read : PROC
extern _ExitProcess@4 : PROC

.data
dekoder db '0123456789ABCDEF'
obszar db 12 dup (?)
dziesiec dd 10

.code
wczytaj_do_EAX PROC
push ebx
push esi
push edi
push ebp

push dword PTR 12
push dword PTR OFFSET obszar
push dword PTR 0
call __read
add esp, 12

xor eax, eax
mov ebx, OFFSET obszar

pobieraj_znaki:
mov cl, [ebx]
inc ebx
cmp cl, 10
je byl_enter
sub cl, 30H
movzx ecx, cl

mul dword PTR dziesiec
add eax, ecx
jmp pobieraj_znaki

byl_enter:

pop ebp
pop edi
pop esi
pop ebx
ret

wczytaj_do_EAX ENDP

wyswietl_EAX_hex PROC
pusha
sub esp, 12 ; rezerwacja 12 bajtow na stosie
mov edi, esp ; adres zarezerwowanego obszaru


;przygotowanie konwersji

mov ecx, 8
mov esi, 1

ptl3hex:
;przesuniecie cykliczne (obrot) rejestru EAX
;o 4 bity w lewo
; w pierwszym obiegu petli bity nr 31-28
;zostana przesuniete na pozycje 3-0

rol eax, 4
mov ebx, eax ;kopiowanie eax do ebx
and ebx, 0000000FH ; zerowanie bitow 31-4
mov dl, dekoder[ebx] ; pobranie cyfry z tablicy
;przeslanie cyfry do obszaru roboczego
cmp dl, '0'
je spacja
mov dh, 'e' ; znacznik zakonzcenia najmniej waznych zer
jne dalej

dalej:
mov [edi][esi], dl
inc esi
loop ptl3hex
jmp koniec

spacja:
cmp dh, 'e'
je dalej
mov dl,' '
mov [edi][esi], dl
inc esi
loop ptl3hex


koniec:
mov byte PTR [edi][0], 10
mov byte PTR [edi][9], 10

push 10
push edi
push 1
call __write

add esp, 24
popa
ret

wyswietl_EAX_hex ENDP

_main PROC
call wczytaj_do_EAX
call wyswietl_EAX_hex

push 0
call _ExitProcess@4

_main ENDP
END

;3_5
