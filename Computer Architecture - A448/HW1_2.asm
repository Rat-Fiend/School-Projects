# Add numbers to stack to act as array
	add 	a5, sp, zero 	# Start of array
	addi 	a6, sp, 40 	# Element after end of array
L2:	
	li	a7, 5
	sw	a7, 0(a5)
	addi	a5, a5, 4	# Increment array pointer by 4 to point at next element
	blt	a5, a6, L2	# Loop while pointer is still in array
	# End of loop
	
	add 	a5, sp, zero 	# Start of array
	addi 	a6, sp, 40	# Element after end of array
L1:
	lw	a7, (a5)	# Load num from array
	addi 	a7, a7, 1	# Increment Num
	sw	a7, 0(a5)	# Store num back to array
	addi	a5, a5, 4	# Increment array pointer by 4 to point at next element
	blt	a5, a6, L1	# Loop while pointer is still in array
