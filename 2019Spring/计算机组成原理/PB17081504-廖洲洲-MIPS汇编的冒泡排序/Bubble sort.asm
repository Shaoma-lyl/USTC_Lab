.data
array:.space 128
string1 : .asciiz "Please input the number of Numbers to sort: \n"
string2 : .asciiz "Please input the numbers:\n"
string3 : .asciiz "After sort :\n"
string4 : .asciiz " "
starttime:.asciiz"\nstarttime:"
finishtime:.asciiz"\nfinishtime:"
duration:.asciiz"\nduration:"

.text
.globl main
main:


    la $a0 , string1 
    li $v0 , 4
    syscall  #ϵͳ���������ʾ

    li $v0 , 5   #ϵͳ���ý��������С������$v0
    syscall

    la $t6 , array     # $t6 �������׵�ַ
    move $t7 , $zero   # i
    move $t8 , $v0       # num
    move $t9 , $zero   # j

input:               # ����Ԫ�ص�����
    la $a0 , string2 
    li $v0 , 4
    syscall   # ��ӡ�ַ�������ʾ�û����������Ԫ��

    li $v0 , 5
    syscall

    move $t0 , $t7     
    mul $t0 , $t0 , 4    # $to=i*4
    addu $t1 , $t0 , $t6 #�õ��µ�ַ
    sw $v0 , 0($t1)

    addi $t7,$t7,1
    blt $t7,$t8,input   #i��num����ȣ���������
    move $t7,$zero  # ���������ѭ��������Ϊ0
    
    li $v0,30
    add $a2,$a1,$zero
    syscall

    li	$v0,	30
    syscall				#record system time
    add	$s2,	$a0,	$zero	#$s0=$a0=low 32 bit of system time
    add     $s3,    $a1,	$zero

loop1:
    move $t9,$zero    # ��һ��ѭ����$t9Ϊj��ִ�����ֵΪ0
loop2:
    move $t0,$t9      # a[j]
    mul $t0,$t0,4
    addu $t1,$t0,$t6
    lw $t2,0($t1)

    addi $t0,$t9,1    # a[j+1]
    mul $t0,$t0,4
    addu $t4,$t0,$t6
    lw $t3,0($t4)

    bge $t2,$t3,skip  # ���a[j] > a[j+1],������,���򽻻����ߵ�ֵ
    sw $t3,0($t1)   
    sw $t2,0($t4)    

skip:
   addi $t9,$t9,1   # j=j+1
   addi $t0,$t9,1   
   sub $t1,$t8,$t7    
   blt $t0,$t1,loop2  # ������㣬����ת��loop1
   addi $t7,$t7,1     # ��������㣬����ת������ִ������Ĵ���
   sub $t2,$t8,1
   blt $t7,$t2,loop1

output:

   li $v0,4
   la $a0,string3  # After sort
   syscall

   move $t7,$zero   # i=0

print:          # ���
   move $t0,$t7
   mul $t0,$t0,4
   addu $t1,$t0,$t6 
   lw $a0,0($t1) #v[i]
   li $v0,1
   syscall

   la $a0,string4  
   li $v0,4
   syscall

   addi $t7,$t7,1
   blt $t7,$t8,print   # �������ѭ����������ת��print����ִ��ѭ��

   	li $v0,30
	syscall				#record system time
	add $s4,$a0,$zero	#$s0=$a0=low 32 bit of system time
	add $s5,$a1,$zero   
	
	la $a0,starttime
	li $v0,4
	syscall
	add $a0,$zero,$s3
	li $v0,1
	syscall
	add $a0,$zero,$s2
	li $v0,36
	syscall
	la $a0,finishtime
	li $v0,4
	syscall
	add $a0,$zero,$s5
	li $v0,1
	syscall
	add $a0,$zero,$s4
	li $v0,36
	syscall
	la $a0,duration
	li $v0,4
	syscall
	sub $a0,$s4,$s2
	li $v0,36
	syscall




