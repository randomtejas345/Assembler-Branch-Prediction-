core   0: 0x8000c81c (0x00150513) addi    x0, x0, 1
core   0: 0x8000c820 (0xfff5c703) lbu     x4, -1(x1)
core   0: 0x8000c824 (0x00078863) beqz    x5, pc + 16
core   0: 0x8000c828 (0xfee786e3) beq     x5, x4, pc - 20
core   0: 0x8000c814 (0x00054783) lbu     x5, 0(x0)
core   0: 0x8000c828 (0xfee786e3) beq     x5, x4, pc - 20
core   0: 0x8000c818 (0x00158593) addi    x1, x1, 1
core   0: 0x8000c828 (0xfee786e3) beq     x5, x4, pc + 4
core   0: 0x8000c828 (0xfee786e3) beq     x5, x4, pc - 20
core   0: 0x8000c828 (0xfee786e3) beq     x5, x4, pc - 20
core   0: 0x8000c828 (0xfee786e3) beq     x5, x4, pc + 4
core   0: 0x8000c81c (0x00150513) addi    x0, x0, 1
core   0: 0x8000c828 (0xfee786e3) beq     x5, x4, pc - 20
core   0: 0x8000c820 (0xfff5c703) lbu     x4, -1(x1)
core   0: 0x8000c824 (0x00078863) beqz    x5, pc + 16
core   0: 0x8000c828 (0xfee786e3) beq     x5, x4, pc + 4
core   0: 0x8000c82c (0x40e78533) sub     x0, x5, x4
core   0: 0x8000c830 (0x00008067) ret
core   0: 0x80005b98 (0x02051663) bnez    x0, pc + 44
core   0: 0x80005bc4 (0x003c0c13) addi    x8, x8, 3
core   0: 0x80005bc8 (0x41fc5793) srai    x5, x8, 31
core   0: 0x80005bcc (0x0037f793) andi    x5, x5, 3
core   0: 0x80005bd0 (0x018787b3) add     x5, x5, x8
core   0: 0x80005bd4 (0x004b2703) lw      x4, 4(x6)
