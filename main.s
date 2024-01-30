.set MAGIC, 0x1BADB002

.set ALIGN,   1
.set MEMINFO, 1<<1 # memory map info

.set FLAGS, ALIGN | MEMINFO

.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    movl $stack_top, %esp

    # multiboot boot information
    push %ebx
    push %eax

    call kmain

    cli
    hlt
    jmp .

.size _start, . - _start
