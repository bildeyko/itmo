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

	xor esi, esi
	xor ecx, ecx
	mov esi, array_ptr ; поместили адрес на голову массива
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

	mov esp, ebp
	pop ebp
	ret
_print_array ENDP

_sort_gen_asm PROC
	array_ptr equ [ebp+8]
	comp equ [ebp+12]
	i_var equ [ebp-4]
	j_var equ [ebp-8]
	k_var equ [ebp-12]
	temp_var equ [ebp-16]
	array_head equ [ebp-20]
	byte_size = 4

	push ebp
	mov ebp, esp
	sub esp, 20

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


	shr ecx, 1
	k_loop:
		mov k_var, ecx
		i_loop:
			mov i_var, ecx
			mov ebx, array_head
			mov eax, [ebx+ecx]
			mov temp_var, eax
			
			j_loop:
				mov j_var, ecx
				
				mov edx, j_var
				sub edx, k_var
				shl edx, 2 ; умножение на 4, т.е. на размер int
				mov ebx, array_head
				add ebx, edx ;в ebx сейчас адрес элемента [j-k]
				mov eax, [ebx]
				push eax

				mov eax, temp_var
				push eax

				mov eax, comp
				call eax
				add esp, 8

				cmp eax, -1
				jne break
					mov edx, j_var
					shl edx, 2
					mov edi, array_head
					add edi, edx

					mov eax, [ebx]
					mov [edi], eax

				sub ecx, k_var
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
		shr ecx, 1
		cmp ecx, 0
		ja k_loop

	mov esp, ebp
	pop ebp
	ret
_sort_gen_asm ENDP

text ends

end