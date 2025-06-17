.686
.model flat
extern _ExitProcess@4 : PROC
extern __write : PROC ; (dwa znaki podkreślenia)
extern __read : PROC ; (dwa znaki podkreślenia)
extern _MessageBoxA@16 : PROC
public _main

.data
      tytul db 'Twoje duze litery', 0
      tekst_pocz db 10, 'Proszę napisać jakiś tekst '
      db 'i nacisnac Enter', 10
      koniec_t db ?
      magazyn db 80 dup (?)
      nowa_linia db 10
      liczba_znakow dd ?

.code
_main PROC
; wyświetlenie tekstu informacyjnego

; liczba znaków tekstu
      mov ecx,(OFFSET koniec_t) - (OFFSET tekst_pocz)
      push ecx
      push OFFSET tekst_pocz ; adres tekstu
      push 1 ; nr urządzenia (tu: ekran - nr 1)
      call __write ; wyświetlenie tekstu początkowego
      add esp, 12 ; usuniecie parametrów ze stosu

; czytanie wiersza z klawiatury
      push 80 ; maksymalna liczba znaków
      push OFFSET magazyn
      push 0 ; nr urządzenia (tu: klawiatura - nr 0)
      call __read ; czytanie znaków z klawiatury
      add esp, 12 ; usuniecie parametrów ze stosu
; kody ASCII napisanego tekstu zostały wprowadzone
; do obszaru 'magazyn'

; funkcja read wpisuje do rejestru EAX liczbę
; wprowadzonych znaków
      mov liczba_znakow, eax
; rejestr ECX pełni rolę licznika obiegów pętli
      mov ecx, eax
      mov ebx, 0 ; indeks początkowy

ptl: mov dl, magazyn[ebx] ; pobranie kolejnego znaku

      cmp dl, 0A5H
      jz polish_a

      cmp dl,0A9H
      jz polish_e

      cmp dl, 86H
      jz polish_c

      cmp dl, 88H
      jz polish_l

      cmp dl, 0E4H
      jz polish_n

      cmp dl, 0A2H
      jz polish_o

      cmp dl, 98H
      jz polish_s

      cmp dl, 0ABH
      jz polish_z1

      cmp dl, 0BEH
      jz polish_z2

      ; na male

      cmp dl, 0A4H
      jz polish_a2

      cmp dl, 8FH
      jz polish_c2

      cmp dl, 0A8H
      jz polish_e2

      cmp dl, 9DH
      jz polish_l2

      cmp dl, 0E3H
      jz polish_n2

      cmp dl, 0E0H
      jz polish_o2

      cmp dl, 97H
      jz polish_s2

      cmp dl, 8DH
      jz polish_z12

      cmp dl, 0BDH
      jz polish_z22

      jmp normal

polish_a:
      mov dl, 0A5H
      mov magazyn[ebx], dl
      jmp dalej

polish_e:
      mov dl, 0CAH
      mov magazyn[ebx], dl
      jmp dalej

polish_c:
      mov dl, 0C6H
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

normal:
      cmp dl, 'a'
      jb dalej ; skok, gdy znak nie wymaga zamiany
      cmp dl, 'z'
      ja dalej ; skok, gdy znak nie wymaga zamiany
      sub dl, 20H ; zamiana na wielkie litery
      ; odesłanie znaku do pamięci
      jmp ety

      cmp dl 'A'
      jb inny
      cmp dl, 'Z'
      jb male

ety:  mov magazyn[ebx], dl

dalej: inc ebx ; inkrementacja indeksu

         dec ecx
         jnz ptl ; sterowanie pętlą

male: 
            add  dl,20H
            mov magazyn[ebx], dl

inny:
            mov dl, '*'


; wyświetlenie przekształconego tekstu
      push 0
      push OFFSET tytul
      push OFFSET magazyn
      push 0
      call _MessageBoxA@16
      add esp, 12 ; usuniecie parametrów ze stosu
      push 0

call _ExitProcess@4 ; zakończenie programu
_main ENDP
END