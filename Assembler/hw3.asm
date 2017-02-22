segment .bss
char resb 1

section .text
	 global main 		;must be declared for linker (ld)
main:	 			;tells linker entry point
	 jmp lab2
lab2:
	 cmp [str], byte 0
	 jz lab1

	 mov eax,4;
	 mov ebx,1;
	 lea ecx, [edx]
	 mov edx ,1;
	 int 80h
	 inc edx
	 jmp lab2
lab1: 
	mov eax,1 ;system call number (sys_exit) 
	int 0x80
section .data
	 str db 'Hello, world!', 0xa ;our dear string





