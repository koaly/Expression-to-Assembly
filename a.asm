.text # text section
.globl main # call main by SPIM
main:
sw $a0, 0($sp) # push acc to stack
addiu $sp, $sp, -4 # move stack pointer
li $a0, 12 # load new acc
sw $a0, 0($sp) # push acc to stack
addiu $sp, $sp, -4 # move stack pointer
li $a0, 3 # load new acc
lw $t0, 4($sp) # load top of stack
mul $a0, $t0, $a0 # acc = tos * acc
addiu $sp, $sp, 4 # pop stack
sw $a0, 0($sp) # push acc to stack
addiu $sp, $sp, -4 # move stack pointer
li $a0, 2 # load new acc
sw $a0, 0($sp) # push acc to stack
addiu $sp, $sp, -4 # move stack pointer
li $a0, 7 # load new acc
lw $t0, 4($sp) # load top of stack
add $a0, $t0, $a0 # acc = tos + acc
addiu $sp, $sp, 4 # pop stack
lw $t0, 4($sp) # load top of stack
div $t0, $a0 # acc = top / acc
mflo $a0 # move quotient from lo to acc
addiu $sp, $sp, 4 # pop stack
sw $a0, 0($sp) # push acc to stack
addiu $sp, $sp, -4 # move stack pointer
li $a0, 5 # load new acc
sw $a0, 0($sp) # push acc to stack
addiu $sp, $sp, -4 # move stack pointer
li $a0, 2 # load new acc
lw $t0, 4($sp) # load top of stack
div $t0, $a0 # acc = top / acc
mfhi $a0 # move remainer from hi to acc
addiu $sp, $sp, 4 # pop stack
lw $t0, 4($sp) # load top of stack
sub $a0, $t0, $a0 # acc = tos - acc
addiu $sp, $sp, 4 # pop stack
li $v0, 1 # for printing an integer result
syscall # for printing an integer result
li $v0, 10 # for correct exit (or termination)
syscall # for correct exit (or termination)
