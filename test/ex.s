	.text
	.file	"../test/ex.ll"
	.globl	array
	.p2align	4, 0x90
	.type	array,@function
array:                                  # @array
	.cfi_startproc
# BB#0:
	pushq	%rax
.Lcfi0:
	.cfi_def_cfa_offset 16
	movl	$16, %edi
	callq	malloc
	movq	%rax, (%rsp)
	popq	%rcx
	retq
.Lfunc_end0:
	.size	array, .Lfunc_end0-array
	.cfi_endproc


	.section	".note.GNU-stack","",@progbits
