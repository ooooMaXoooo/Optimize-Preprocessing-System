	.file	"main.cpp"
	.text
	.globl	_Z3Logiii
	.def	_Z3Logiii;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z3Logiii
_Z3Logiii:
.LFB0:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movl	16(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	24(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	32(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	addl	%eax, -8(%rbp)
	nop
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z4testi
	.def	_Z4testi;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z4testi
_Z4testi:
.LFB1:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	cmpl	$0, 16(%rbp)
	jne	.L3
	movl	$1, %eax
	jmp	.L4
.L3:
	movl	$0, %eax
.L4:
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB2:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	call	__main
	movl	$5, %ecx
	call	_Z4testi
	movl	$0, %eax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (Rev6, Built by MSYS2 project) 12.2.0"
