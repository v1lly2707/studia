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

znaki db 12 dup (?) ; deklaracja do przechowywania tworzonych cyfr

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

  wyswietl_EAX PROC
  pusha
  mov esi, 10 ; indeks w tablicy znaki
  mov ebx, 8 ; dzielnik rowny 8

;konwersja na kod ascii

  konwersja:
  mov edx, 0 ; zerowanie starszej czesci dzielnej
  div ebx ; dzielenie przez 10, reszta w EDX, iloraz w EAX

  add dl, 30H ; zamiana reszty z dzielenia na kod ascii
  mov znaki[esi], dl ; zapisanie cyfry w kodzie ascii
  dec esi ; zmniejszenie indeksu
  cmp eax, 0 ; sprawdzenie czy iloraz=0
  jne konwersja

  wypeln:
  or esi, esi
  jz wyswietl ; gdy indeks = 9
  mov byte PTR znaki[esi], 20H ; kod spacji
  dec esi
  jmp wypeln

  wyswietl:
  mov byte PTR znaki[0], 0AH ; kod nowego wiersza
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
  call wczytaj_do_EAX
  call wyswietl_EAX

  push 0
  call _ExitProcess@4

_main ENDP
END
