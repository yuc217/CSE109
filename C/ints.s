	.file	"ints.c"
	.section	.rodata
.LC0:
	.string	"%6u %6i %6x\n"
	.text
.globl main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movw	$0, -20(%rbp)
	jmp	.L2
	.cfi_offset 3, -24
.L3:
	movzwl	-20(%rbp), %eax
	movw	%ax, -18(%rbp)
	movzwl	-20(%rbp), %ecx
	movswl	-18(%rbp), %edx
	movzwl	-20(%rbp), %ebx
	movl	$.LC0, %eax
	movl	%ebx, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	addw	$1000, -20(%rbp)
.L2:
	cmpw	$-1001, -20(%rbp)
	jbe	.L3
	movl	$0, %eax
	addq	$40, %rsp
	popq	%rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-11)"
	.section	.note.GNU-stack,"",@progbits
