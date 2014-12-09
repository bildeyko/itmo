.686
.model flat

include libc.inc

public _print_array
public _sort_gen_asm

.DATA
printf_template db "%d ",0
newline db 10,13,0

.CODE
_print_array PROC
	array_size equ [ebp+12]
	array_ptr equ [ebp+8]

	push ebp
	mov ebp, esp
	pusha

	mov esi, array_ptr
	mov ecx, array_size
	mov eax, 4
	mov ebx, 0				; the counter for a loop

	print_loop:
		mul ebx				; create a real offset in the array (0,4,...)
		pusha
		push [esi+eax]
		push offset printf_template
		call _printf
		add esp, 8
		popa
		inc ebx
		mov eax, 4
	loop print_loop

	push offset newline
	call _printf
	add esp, 4

	popa
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
	array_size equ [ebp-24]

	push ebp
	mov ebp, esp
	sub esp, 24
	pusha

	mov esi, array_ptr
	mov ecx, [esi+4]
	mov array_size, ecx
	mov ebx, [esi]
	mov array_head, ebx	

	k_loop:
		shr ecx, 1		
		mov k_var, ecx
		i_loop:
			mov i_var, ecx			
			mov ebx, array_head
			shl ecx, 2			; multiplication by 4 (as the size of integer) to create a real offset in the array
			mov eax, [ebx+ecx]
			shr ecx, 2
			mov temp_var, eax			
			j_loop:
				mov j_var, ecx				
				mov edx, j_var
				sub edx, k_var	; a number of the [j-k] element
				shl edx, 2		
				mov ebx, array_head
				add ebx, edx	; creation of the address of the [j-k] element of the array
				mov eax, [ebx]
				push ecx		; saving of the counter before the function call from the eax
				push eax		; sending a second parameter
				mov eax, temp_var
				push eax		; sending a first parameter
				mov eax, comp
				call eax
				add esp, 8
				pop ecx

				cmp eax, -1		; check the return value
				jne break
					mov edx, j_var
					shl edx, 2
					mov edi, array_head
					add edi, edx
					mov eax, [ebx]
					mov [edi], eax

				sub ecx, k_var
				mov j_var, ecx
				cmp ecx, k_var
				jae j_loop
			break:
				
			; put the temp variable in the [j] element of the array:
			mov edx, j_var
			shl edx, 2
			mov edi, array_head
			add edi, edx
			mov eax, temp_var
			mov [edi], eax
								
			mov ecx, i_var	
			inc ecx
			cmp ecx, array_size
			jl i_loop
			
		mov ecx, k_var	
		cmp ecx, 0
		ja k_loop

	popa
	mov esp, ebp	
	pop ebp
	ret
_sort_gen_asm ENDP

END