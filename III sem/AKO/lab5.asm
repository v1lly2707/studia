.686
.model flat


public _srednia_wazona

.code
_srednia_wazona PROC

      push ebp
      mov ebp, esp
      push esi
      push edi
      push ecx

      mov esi,[ebp+8]
      mov edi,[ebp+12]
      mov ecx,[ebp+16]

      finit
      fild dword ptr [ebp+16]
      fldz
      fldz
      dec ecx


      

licz:
      fld qword ptr [esi+8*ecx]
      fld qword ptr [edi+8*ecx]
      fadd st(3),st(0)
      fmulp
      faddp

      dec ecx
      cmp ecx,-1
      jne licz

      fdiv st(0), st(1)

      pop ecx
      pop edi
      pop esi
      pop ebp
      ret


_srednia_wazona ENDP
END