	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.intel_syntax noprefix
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	push	rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi2:
	.cfi_def_cfa_register rbp
	sub	rsp, 48
	mov	eax, 10
	mov	ecx, eax
	mov	eax, 8
	mov	edx, eax
	mov	dword ptr [rbp - 4], 0
	mov	dword ptr [rbp - 8], edi
	mov	qword ptr [rbp - 16], rsi
	mov	rdi, rcx
	mov	rsi, rdx
	call	_calloc
	mov	qword ptr [rbp - 32], rax
	mov	dword ptr [rbp - 20], 0
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmp	dword ptr [rbp - 20], 10
	jge	LBB0_4
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	cvtsi2sd	xmm0, dword ptr [rbp - 20]
	mov	rax, qword ptr [rbp - 32]
	movsxd	rcx, dword ptr [rbp - 20]
	movsd	qword ptr [rax + 8*rcx], xmm0
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	mov	eax, dword ptr [rbp - 20]
	add	eax, 1
	mov	dword ptr [rbp - 20], eax
	jmp	LBB0_1
LBB0_4:
	mov	dword ptr [rbp - 20], 0
LBB0_5:                                 ## =>This Inner Loop Header: Depth=1
	cmp	dword ptr [rbp - 20], 10
	jge	LBB0_8
## BB#6:                                ##   in Loop: Header=BB0_5 Depth=1
	lea	rdi, [rip + L_.str]
	mov	esi, dword ptr [rbp - 20]
	mov	rax, qword ptr [rbp - 32]
	movsxd	rcx, dword ptr [rbp - 20]
	movsd	xmm0, qword ptr [rax + 8*rcx] ## xmm0 = mem[0],zero
	mov	al, 1
	call	_printf
	mov	dword ptr [rbp - 36], eax ## 4-byte Spill
## BB#7:                                ##   in Loop: Header=BB0_5 Depth=1
	mov	eax, dword ptr [rbp - 20]
	add	eax, 1
	mov	dword ptr [rbp - 20], eax
	jmp	LBB0_5
LBB0_8:
	mov	rax, qword ptr [rbp - 32]
	mov	rdi, rax
	call	_free
	mov	eax, dword ptr [rbp - 4]
	add	rsp, 48
	pop	rbp
	ret
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"*(p + %d) = %lf\n"


.subsections_via_symbols
