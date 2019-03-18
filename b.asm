.text # text section
.globl main # call main by SPIM
main:
sw $a0, 0($sp)
addiu $sp, $sp, -4
li $a0, 20
sw $a0, 0($sp)
addiu $sp, $sp, -4
li $a0, 10
lw $t0, 4($sp)
sub $a0, $t0, $a0
addiu $sp, $sp, 4
sw $a0, 0($sp)
addiu $sp, $sp, -4
li $a0, 30
sw $a0, 0($sp)
addiu $sp, $sp, -4
li $a0, 4
lw $t0, 4($sp)
div $t0, $a0
mflo $a0
addiu $sp, $sp, 4
sw $a0, 0($sp)
addiu $sp, $sp, -4
li $a0, 40
lw $t0, 4($sp)
add $a0, $t0, $a0
addiu $sp, $sp, 4
lw $t0, 4($sp)
mul $a0, $t0, $a0
addiu $sp, $sp, 4
sw $a0, 0($sp)
addiu $sp, $sp, -4
li $a0, 5
sw $a0, 0($sp)
addiu $sp, $sp, -4
li $a0, 6
lw $t0, 4($sp)
add $a0, $t0, $a0
addiu $sp, $sp, 4
lw $t0, 4($sp)
div $t0, $a0
mfhi $a0
addiu $sp, $sp, 4
li $v0, 1 # for printing an integer result
syscall # for printing an integer result
li $v0, 10 # for correct exit (or termination)
syscall # for correct exit (or termination)
