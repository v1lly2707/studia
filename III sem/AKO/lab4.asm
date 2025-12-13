.686
.model flat
public _przestaw
.code

_przestaw PROC
      push ebp
      mov ebp,esp
      push ebx
      push edx

      mov ebx, [ebp+8]
      mov ecx, [ebp+12]
      dec ecx

      mov edx,2147483647

ptl:
      mov eax, [ebx]

      cmp eax, 0
      jl zamien
      
dalej:
      cmp eax,edx
      jl min

gotowe:
      add ebx,4
      loop ptl
      mov eax,edx

      pop edx
      pop ebx
      pop ebp
      ret


zamien:
      neg eax
      jmp dalej







min:
      mov edx, eax
      jmp gotowe


_przestaw ENDP
END