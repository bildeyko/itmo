.686
.model flat

include libc.inc

public _print_array
public _sort_gen_asm

data segment "data"

printf_template db "%d ",0
newline db 10,13,0

data ends

text segment "code"

_print_array PROC
	array_size equ [ebp+12]
	array_ptr equ [ebp+8]

	push ebp
	mov ebp, esp
	push esi
	push edi
	push ebx

	xor esi, esi
	xor ecx, ecx
	mov esi, array_ptr ; ��������� ����� �� ������ �������
	add ecx, array_size
	mov eax, 4
	mov ebx, 0

	print_loop:
		mul ebx

		push ecx
		push [esi+eax]
		push offset printf_template
		call _printf
		add esp, 8
		pop ecx

		inc ebx
		mov eax, 4
	loop print_loop

	push [esi+eax]
	push offset newline
	call _printf
	add esp, 8

	pop ebx
	pop edi
	pop esi
	mov esp, ebp
	pop ebp
	ret
_print_array ENDP

_sort_gen_asm PROC

	array_ptr equ [ebp+8]
	comp equ [ebp+12]
	i_var equ [ebp-16] ;4
	j_var equ [ebp-20] ;8
	k_var equ [ebp-24] ;12
	temp_var equ [ebp-28] ;16
	array_head equ [ebp-32] ;20
	byte_size = 4

	push ebp
	mov ebp, esp
	sub esp, 32 ;20
	push esi
	push edi
	push ebx

	xor edx, edx
	xor eax, eax
	xor esi, esi
	mov esi, array_ptr

	xor ecx,ecx
	mov ecx, [esi+4]
	mov ebx, [esi]
	mov array_head, ebx
	;mov edx, [ebx+4]
	;mov eax, comp
	;push 4
	;push 5
	;call eax
	;add esp, 8
	;xor ebx,ebx
	;pop ebx


	;sub ecx, 2
	k_loop:
		shr ecx, 1		
		mov k_var, ecx
		i_loop:
			mov i_var, ecx			
			mov ebx, array_head
			shl ecx, 2
			mov eax, [ebx+ecx]
			shr ecx, 2
			mov temp_var, eax
			
			j_loop:
				mov j_var, ecx
				
				mov edx, j_var
				sub edx, k_var
				shl edx, 2 ; ��������� �� 4, �.�. �� ������ int
				mov ebx, array_head
				add ebx, edx ;� ebx ������ ����� �������� [j-k]
				mov eax, [ebx]
				push ecx ;����������� ����� ������� �������
				push eax

				mov eax, temp_var
				push eax

				mov eax, comp
				call eax
				add esp, 8
				pop ecx

				cmp eax, -1
				jne break
					mov edx, j_var
					shl edx, 2
					mov edi, array_head
					add edi, edx

					push ebx
					mov ebx, [edi]
					pop ebx

					mov eax, [ebx]
					mov [edi], eax

				sub ecx, k_var
				mov j_var, ecx
				cmp ecx, k_var
				jae j_loop
				break:
				
			mov edx, j_var
			shl edx, 2
			mov edi, array_head
			add edi, edx

			mov eax, temp_var
			mov [edi], eax
					
			mov ecx, i_var	
			inc ecx
			cmp ecx, [esi+4]
			jl i_loop
			
		mov ecx, k_var	
		;shr ecx, 1
		cmp ecx, 0
		ja k_loop

	;pop ebx
	pop ebx
	pop edi
	pop esi
	mov esp, ebp
	
	pop ebp
	ret
_sort_gen_asm ENDP

text ends

end