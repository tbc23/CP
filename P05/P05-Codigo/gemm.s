	.file	"gemm.c"
	.text
	.p2align 4
	.globl	gemm1
	.type	gemm1, @function
gemm1:
.LFB23:
	.cfi_startproc
	endbr64
	testl	%ecx, %ecx
	jle	.L9
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	%ecx, %r9d
	xorl	%r13d, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rsi, %r12
	movslq	%ecx, %rsi
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	salq	$2, %rsi
	movq	%rdx, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	.p2align 4,,10
	.p2align 3
.L3:
	movq	%rbx, %r11
	movq	%r12, %rdi
	xorl	%r10d, %r10d
	.p2align 4,,10
	.p2align 3
.L6:
	movq	%r11, %rcx
	movq	%rbp, %rdx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L4:
	movss	(%rcx), %xmm0
	mulss	(%rdi), %xmm0
	movl	%eax, %r8d
	addl	$1, %eax
	addss	(%rdx), %xmm0
	addq	%rsi, %rcx
	movss	%xmm0, (%rdx)
	addq	%rsi, %rdx
	cmpl	%eax, %r9d
	jne	.L4
	leal	1(%r10), %eax
	addq	$4, %r11
	addq	%rsi, %rdi
	cmpl	%r10d, %r8d
	je	.L5
	movl	%eax, %r10d
	jmp	.L6
	.p2align 4,,10
	.p2align 3
.L5:
	leal	1(%r13), %eax
	addq	$4, %rbp
	addq	$4, %r12
	cmpl	%r13d, %r10d
	je	.L1
	movl	%eax, %r13d
	jmp	.L3
.L1:
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L9:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	ret
	.cfi_endproc
.LFE23:
	.size	gemm1, .-gemm1
	.p2align 4
	.globl	gemm2
	.type	gemm2, @function
gemm2:
.LFB24:
	.cfi_startproc
	endbr64
	testl	%ecx, %ecx
	jle	.L21
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	leal	-1(%rcx), %eax
	movl	%ecx, %r12d
	movslq	%ecx, %r8
	salq	$2, %rax
	negq	%r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdx, %r10
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rsi, %rbp
	movl	%ecx, %ebx
	salq	$2, %r8
	leaq	4(%rdi,%rax), %r9
	leaq	4(%rax,%rdx), %rsi
	xorl	%r11d, %r11d
	salq	$2, %r12
	.p2align 4,,10
	.p2align 3
.L15:
	movq	%rbp, %rdi
	leaq	(%r12,%r9), %rcx
	.p2align 4,,10
	.p2align 3
.L18:
	movq	%rdi, %rdx
	movq	%r10, %rax
	.p2align 4,,10
	.p2align 3
.L16:
	movss	(%rcx), %xmm0
	mulss	(%rdx), %xmm0
	addq	$4, %rax
	addq	$4, %rdx
	addss	-4(%rax), %xmm0
	movss	%xmm0, -4(%rax)
	cmpq	%rsi, %rax
	jne	.L16
	addq	$4, %rcx
	addq	%r8, %rdi
	cmpq	%rcx, %r9
	jne	.L18
	addl	$1, %r11d
	addq	%r8, %r9
	addq	%r8, %r10
	addq	%r8, %rsi
	cmpl	%r11d, %ebx
	jne	.L15
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L21:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	ret
	.cfi_endproc
.LFE24:
	.size	gemm2, .-gemm2
	.p2align 4
	.globl	gemm3
	.type	gemm3, @function
gemm3:
.LFB25:
	.cfi_startproc
	endbr64
	testl	%ecx, %ecx
	jle	.L32
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	leal	-1(%rcx), %eax
	movslq	%ecx, %r8
	movq	%rdx, %r10
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movl	%ecx, %ebp
	salq	$2, %rax
	xorl	%r11d, %r11d
	movl	%ebp, %r12d
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	salq	$2, %r8
	movq	%rsi, %rbx
	negq	%r12
	leaq	4(%rdi,%rax), %r9
	leaq	4(%rdx,%rax), %rcx
	salq	$2, %r12
	.p2align 4,,10
	.p2align 3
.L26:
	leaq	(%r12,%r9), %rsi
	movq	%rbx, %rdi
	.p2align 4,,10
	.p2align 3
.L28:
	movss	(%rsi), %xmm1
	movq	%rdi, %rdx
	movq	%r10, %rax
	.p2align 4,,10
	.p2align 3
.L27:
	movss	(%rdx), %xmm0
	addq	$4, %rax
	addq	$4, %rdx
	mulss	%xmm1, %xmm0
	addss	-4(%rax), %xmm0
	movss	%xmm0, -4(%rax)
	cmpq	%rcx, %rax
	jne	.L27
	addq	$4, %rsi
	addq	%r8, %rdi
	cmpq	%rsi, %r9
	jne	.L28
	addl	$1, %r11d
	addq	%r8, %r9
	addq	%r8, %r10
	addq	%r8, %rcx
	cmpl	%r11d, %ebp
	jne	.L26
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L32:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	ret
	.cfi_endproc
.LFE25:
	.size	gemm3, .-gemm3
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"gemm4() not supported!\n\n"
	.text
	.p2align 4
	.globl	gemm4
	.type	gemm4, @function
gemm4:
.LFB26:
	.cfi_startproc
	endbr64
	movq	stderr(%rip), %rcx
	movl	$24, %edx
	movl	$1, %esi
	leaq	.LC0(%rip), %rdi
	jmp	fwrite@PLT
	.cfi_endproc
.LFE26:
	.size	gemm4, .-gemm4
	.section	.rodata.str1.1
.LC1:
	.string	"gemm5() not supported!\n\n"
	.text
	.p2align 4
	.globl	gemm5
	.type	gemm5, @function
gemm5:
.LFB27:
	.cfi_startproc
	endbr64
	movq	stderr(%rip), %rcx
	movl	$24, %edx
	movl	$1, %esi
	leaq	.LC1(%rip), %rdi
	jmp	fwrite@PLT
	.cfi_endproc
.LFE27:
	.size	gemm5, .-gemm5
	.p2align 4
	.globl	gemm6
	.type	gemm6, @function
gemm6:
.LFB28:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	andq	$-32, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, -40(%rsp)
	testl	%ecx, %ecx
	jle	.L52
	movslq	%ecx, %rax
	movq	%rdi, %rbx
	movl	%ecx, %r8d
	movl	%ecx, %r12d
	movq	%rax, -16(%rsp)
	salq	$2, %rax
	shrl	$3, %r8d
	movq	%rsi, %r13
	movq	%rax, -8(%rsp)
	leal	-1(%rcx), %eax
	movq	%rdx, %r14
	movl	%ecx, %edi
	movl	%eax, -28(%rsp)
	leaq	4(%rbx,%rax,4), %rax
	salq	$5, %r8
	xorl	%r15d, %r15d
	movq	%rax, -24(%rsp)
	andl	$-8, %r12d
	movl	$0, -32(%rsp)
	.p2align 4,,10
	.p2align 3
.L39:
	movq	-40(%rsp), %rax
	movq	%r13, %rcx
	xorl	%ebx, %ebx
	leaq	(%rax,%r15,4), %r11
	.p2align 4,,10
	.p2align 3
.L46:
	cmpl	$6, -28(%rsp)
	vmovss	(%r11), %xmm2
	jbe	.L47
	vbroadcastss	%xmm2, %ymm3
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L41:
	vmovups	(%rdx,%rax), %xmm5
	vmovups	(%rcx,%rax), %xmm4
	vinsertf128	$0x1, 16(%rdx,%rax), %ymm5, %ymm1
	vinsertf128	$0x1, 16(%rcx,%rax), %ymm4, %ymm0
	vfmadd132ps	%ymm3, %ymm1, %ymm0
	vmovups	%xmm0, (%rdx,%rax)
	vextractf128	$0x1, %ymm0, 16(%rdx,%rax)
	addq	$32, %rax
	cmpq	%rax, %r8
	jne	.L41
	cmpl	%edi, %r12d
	je	.L42
	movl	%r12d, %esi
	movl	%r12d, %eax
.L40:
	movl	%edi, %r9d
	subl	%esi, %r9d
	leal	-1(%r9), %r10d
	cmpl	$2, %r10d
	jbe	.L43
	leaq	(%r15,%rsi), %r10
	addq	%rbx, %rsi
	vshufps	$0, %xmm2, %xmm2, %xmm0
	leaq	(%r14,%r10,4), %r10
	vmovups	(%r10), %xmm6
	vfmadd132ps	0(%r13,%rsi,4), %xmm6, %xmm0
	movl	%r9d, %esi
	andl	$-4, %esi
	addl	%esi, %eax
	vmovups	%xmm0, (%r10)
	cmpl	%esi, %r9d
	je	.L42
.L43:
	cltq
	.p2align 4,,10
	.p2align 3
.L45:
	vmovss	(%rcx,%rax,4), %xmm0
	vfmadd213ss	(%rdx,%rax,4), %xmm2, %xmm0
	vmovss	%xmm0, (%rdx,%rax,4)
	addq	$1, %rax
	cmpl	%eax, %edi
	jg	.L45
.L42:
	addq	$4, %r11
	addq	-8(%rsp), %rcx
	addq	-16(%rsp), %rbx
	cmpq	%r11, -24(%rsp)
	jne	.L46
	movq	-8(%rsp), %rsi
	addl	$1, -32(%rsp)
	movl	-32(%rsp), %eax
	addq	%rsi, -24(%rsp)
	addq	%rsi, %rdx
	addq	-16(%rsp), %r15
	cmpl	%eax, %edi
	jne	.L39
	vzeroupper
.L52:
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
	.p2align 4,,10
	.p2align 3
.L47:
	.cfi_restore_state
	xorl	%esi, %esi
	xorl	%eax, %eax
	jmp	.L40
	.cfi_endproc
.LFE28:
	.size	gemm6, .-gemm6
	.p2align 4
	.globl	gemm7
	.type	gemm7, @function
gemm7:
.LFB29:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	andq	$-32, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdx, -40(%rsp)
	testl	%ecx, %ecx
	jle	.L70
	movslq	%ecx, %rax
	movq	%rdi, %rbx
	movl	%ecx, %edi
	movl	$0, -32(%rsp)
	movq	%rax, -16(%rsp)
	salq	$2, %rax
	movl	%edi, %r8d
	movl	%edi, %r13d
	movq	%rax, -24(%rsp)
	leal	-1(%rcx), %eax
	shrl	$3, %r8d
	movq	%rsi, %r12
	movl	%eax, -28(%rsp)
	leaq	4(%rdx,%rax,4), %rax
	movq	%rbx, %rcx
	salq	$5, %r8
	movq	%rax, -8(%rsp)
	andl	$-8, %r13d
	xorl	%r14d, %r14d
	.p2align 4,,10
	.p2align 3
.L57:
	movq	-40(%rsp), %rax
	movq	%r12, %rdx
	xorl	%r11d, %r11d
	leaq	(%rax,%r14,4), %r9
	.p2align 4,,10
	.p2align 3
.L64:
	cmpl	$6, -28(%rsp)
	vmovss	(%r9), %xmm1
	jbe	.L65
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L59:
	vmovups	(%rdx,%rax), %xmm5
	vmovups	(%rcx,%rax), %xmm6
	vinsertf128	$0x1, 16(%rdx,%rax), %ymm5, %ymm3
	vinsertf128	$0x1, 16(%rcx,%rax), %ymm6, %ymm0
	addq	$32, %rax
	vmulps	%ymm0, %ymm3, %ymm3
	vaddss	%xmm3, %xmm1, %xmm1
	vshufps	$85, %xmm3, %xmm3, %xmm2
	vshufps	$255, %xmm3, %xmm3, %xmm0
	vaddss	%xmm2, %xmm1, %xmm1
	vunpckhps	%xmm3, %xmm3, %xmm2
	vaddss	%xmm2, %xmm1, %xmm1
	vaddss	%xmm1, %xmm0, %xmm0
	vextractf128	$0x1, %ymm3, %xmm1
	vshufps	$85, %xmm1, %xmm1, %xmm2
	vaddss	%xmm1, %xmm0, %xmm0
	vaddss	%xmm2, %xmm0, %xmm0
	vunpckhps	%xmm1, %xmm1, %xmm2
	vshufps	$255, %xmm1, %xmm1, %xmm1
	vaddss	%xmm2, %xmm0, %xmm0
	vaddss	%xmm1, %xmm0, %xmm1
	cmpq	%rax, %r8
	jne	.L59
	cmpl	%edi, %r13d
	je	.L60
	movl	%r13d, %esi
	movl	%r13d, %eax
.L58:
	movl	%edi, %r10d
	subl	%esi, %r10d
	leal	-1(%r10), %r15d
	cmpl	$2, %r15d
	jbe	.L61
	leaq	(%rsi,%r14), %r15
	addq	%r11, %rsi
	vmovups	(%r12,%rsi,4), %xmm2
	vmulps	(%rbx,%r15,4), %xmm2, %xmm2
	movl	%r10d, %esi
	andl	$-4, %esi
	addl	%esi, %eax
	vaddss	%xmm2, %xmm1, %xmm0
	vshufps	$85, %xmm2, %xmm2, %xmm1
	vaddss	%xmm1, %xmm0, %xmm0
	vunpckhps	%xmm2, %xmm2, %xmm1
	vaddss	%xmm1, %xmm0, %xmm0
	vshufps	$255, %xmm2, %xmm2, %xmm1
	vaddss	%xmm1, %xmm0, %xmm1
	cmpl	%esi, %r10d
	je	.L60
.L61:
	cltq
	.p2align 4,,10
	.p2align 3
.L63:
	vmovss	(%rcx,%rax,4), %xmm4
	vfmadd231ss	(%rdx,%rax,4), %xmm4, %xmm1
	addq	$1, %rax
	cmpl	%eax, %edi
	jg	.L63
.L60:
	vmovss	%xmm1, (%r9)
	addq	-24(%rsp), %rdx
	addq	$4, %r9
	addq	-16(%rsp), %r11
	cmpq	-8(%rsp), %r9
	jne	.L64
	movq	-24(%rsp), %rdx
	addl	$1, -32(%rsp)
	movl	-32(%rsp), %eax
	addq	%rdx, -8(%rsp)
	addq	%rdx, %rcx
	addq	-16(%rsp), %r14
	cmpl	%eax, %edi
	jne	.L57
	vzeroupper
.L70:
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
	.p2align 4,,10
	.p2align 3
.L65:
	.cfi_restore_state
	xorl	%esi, %esi
	xorl	%eax, %eax
	jmp	.L58
	.cfi_endproc
.LFE29:
	.size	gemm7, .-gemm7
	.p2align 4
	.globl	gemm8
	.type	gemm8, @function
gemm8:
.LFB30:
	.cfi_startproc
	endbr64
	ret
	.cfi_endproc
.LFE30:
	.size	gemm8, .-gemm8
	.p2align 4
	.globl	gemm9
	.type	gemm9, @function
gemm9:
.LFB34:
	.cfi_startproc
	endbr64
	ret
	.cfi_endproc
.LFE34:
	.size	gemm9, .-gemm9
	.p2align 4
	.globl	gemm10
	.type	gemm10, @function
gemm10:
.LFB36:
	.cfi_startproc
	endbr64
	ret
	.cfi_endproc
.LFE36:
	.size	gemm10, .-gemm10
	.ident	"GCC: (Ubuntu 10.2.0-13ubuntu1) 10.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
