#=================================================================
# Copyright 2022 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================
#     D i a m o n d   S e a r c h
#
# P1-2
# Student Name: Janah Abu Hassan
# Date: 10/23/2022
#
# This program finds the shortest path out of a diamond of weighted squares.
#
#===========================================================================
# CHANGE LOG: brief description of changes made from P1-2-shell.asm
# to this version of code.
# 10/06/2022
# 10/06 Looping through squares to get mincost of indices 5, 55, 65, and 115
# 10/06 Storing the MinCost in the Array
# 10/14 Looped through all squares and stored MinCost in array
# 10/14 MinCost accurately showing in $4
# 10/20 Improving efficiency by changing to do-while loop
# 10/23 Improving efficiency by using less registers and looping less
#===========================================================================

.data
Array:	.alloc	121	# allocate static space for padded weight map

.text
PathOut:	    addi	$1, $0, Array	    # set memory base
                swi	    514		            # create weight map in memory

# Find MinCost for indices 5, 55, 65, and 115
                sw      $31, -4($1)         # store value of $31 into base address - 1
                addi    $3, $0, 11          # $3 = 11
                addi    $5, $0, 2           # $5 = i

FirstLoop:      mult    $5, $3              # i * 11
                mflo    $7                  # store it in $7
                sll     $7, $7, 2           # $7 = i * 11 * 4 (address)
                sll     $6, $5, 2           # $6 = i * 4 (address)
                addi    $8, $1, 240         # $8 = base + 60 -> index (starting at index 60)
                sub     $9, $8, $7          # $9 = index - (i * 11)
                add     $7, $7, $8          # $7 = index + (i * 11)
                sub     $12, $8, $6         # $12 = index - i
                add     $6, $6, $8          # $6 = index + i 
                lw      $10, 0($9)          # $10 = Array[index - (i * 11)]
                lw      $11, 44($9)         # $11 = Array[index - (i * 11) + 11]
                add     $8, $10, $11        # $8 = Array[index - (i * 11)] + Array[index - (i * 11) + 11]
                sw      $8, 0($9)           # Array[index - (i * 11)] = Array[index - (i * 11)] + Array[index - (i * 11) + 11]
                lw      $10, 0($7)          # $10 = Array[index + (i * 11)]
                lw      $11, -44($7)        # $11 = Array[index + (i * 11) - 11]
                add     $8, $10, $11        # $8 = Array[index + (i * 11)] + Array[index + (i * 11) - 11]
                sw      $8, 0($7)           # Array[index index + (1 * 11)] = Array[index + (i * 11)] + Array[index + (i * 11) - 11]
                lw      $10, 0($12)         # $10 = Array[index - i]
                lw      $11, 4($12)         # $11 = Array[index - i + 1]
                add     $8, $10, $11        # $8 = Array[index - i] + Array[index - i + 1]
                sw      $8, 0($12)          # Array[index - i] = Array[index - i] + Array[index - i + 1]
                lw      $10, 0($6)          # $10 = Array[index + i]
                lw      $11, -4($6)         # $11 = Array[index + i - 1]
                add     $8, $10, $11        # $8 = Array[index + i] + Array[index + i - 1]
                sw      $8, 0($6)           # Array[index + i] = Array[index + i] + Array[index + i - 1]
                addi    $5 $5, 1            # i++
                slti    $9, $5, 6           # if i < 6
                bne     $9, $0, FirstLoop   # if yes, loop back

# Find MinCost for the quadrants of the diamond

Calls: 			lw      $4, 20($1)          # load index 5 into $4
				lw      $7, 260($1)         # load index 65 into $7
				jal     MinCostChange       # if yes, make value to be MinCost
				lw      $7, 220($1)         # load index 55 into $7
				jal     MinCostChange       # if yes, make value to be MinCost
				lw      $7, 460($1)         # load index 115 into $7
				jal     MinCostChange       # if yes, make value to be MinCost
				addi    $13, $0, 1          # $13 = 1

                # Top right quadrant
				addi    $8, $0, 200         # change starting index value
				addi    $7, $0, -11         # $7 = -11
				addi    $2, $0, 44          # $2 = 11
				addi    $11, $0, -4         # $11 = -1
				jal     Func                # jump to Func

                # Bottom right quadrant
				addi    $8, $0, 288         # change starting index value
				addi    $7, $0, 11          # $7 = 11
				addi    $2, $0, -44         # $2 = -11
				jal     Func                # jump to Func

                # Top left quadrant
				addi    $13, $0, 0      
				addi    $8, $0, 192         # change starting index value
				addi    $7, $0, -11         # $7 = -11
				addi    $2, $0, 44          # $2 = 11
				addi    $11, $0, 4          # $11 = 1
				jal     Func                # jump to Func

                # Bottom left quadrant
				addi    $8, $0, 280         # change starting index value
				addi    $7, $0, 11          # $7 = 11
				addi    $2, $0, -44         # $2 = -11
				jal     Func                # jump to Func
				lw      $31, -4($1)         # get original value of $31 back into $31
				j       End                 # End Program

Func:		    addi    $5, $0, 0           # $5 = i = 0
                addi    $14, $0, 4          # set max. value of outer loop

OuterLoop:		addi    $6, $0, 0           # $6 = j = 0

InnerLoop:		sll     $3, $5, 2           # $3 = i * 4
				mult    $3, $7              # i * 4 * (-11 or +11)
				mflo    $12                 # store it in $12
				add     $10, $8, $12        # index + (11 * i)

				sll     $3, $6, 2           # $3 = j * 4
				beq     $13, $0, Negate     # Negate $3 if iterating to the left

Then:			add     $3, $10, $3         # index = index + (11 * i) + j
				add     $3, $3, $1          # Adding to base address
                add     $12, $11, $3        # $12 = index + j - 1
                add     $9, $2, $3          # $9 = index + j + 11
				lw      $9, 0($9)           # $9 = Array[index + j + 11]
				lw      $12, 0($12)         # $12 = Array[index + j - 1]
				slt     $10, $9, $12        # if Array[index + j + 11] < Array[index + j - 1]
				beq     $10, $0, Then2      # if not, go to Then2
				lw      $10, 0($3)          # if yes, $10 = Array[index + j]
				add     $10, $10, $9        # $10 = Array[index + j] + Array[index + j + 11]
				sw      $10, 0($3)          # store value in Array[index + j]
				j       EndInner            # End inner loop

Then2:			lw      $10, 0($3)          # $10 = Array[index + j]
				add     $10, $10, $12       # $10 = Array[index + j] + Array[index + j - 1]
				sw      $10, 0($3)          # store value in Array[index + j]         

EndInner:	    addi    $6, $6, 1           # j++

While:          addi    $9, $0, 4           # $9 = 4
				sub     $9, $9, $5          # $9 = 4 - i
				slt     $12, $6, $9         # if j < 4 - i
				bne     $12, $0, InnerLoop  # if yes, go to InnerLoop
                addi    $5, $5, 1           # i++
				slt     $12, $10, $4        # if Array[index + j] + Array[index + j - 1] < minCost
				beq     $0, $12, CheckLimit     # if no, check limit
                addi    $4, $10, 0          # if yes, change value of MinCost to value in $10

CheckLimit:    beq     $5, $14, Returns    # if i == max value (4), go to Returns

End2:			j       OuterLoop           # go to outerloop

Negate:			sub     $3, $0, $3          # make $3 = -$3
				j       Then                # go back to Then

MinCostChange:  slt     $11, $7, $4         # if value at index < MinCost
                beq     $11, $0, Returns    # if no, go to Returns

ChangeValue:    add     $4, $0, $7          # $4 = $7 if Array[index] < MinCost

Returns:        jr      $31                 # jump to $31

End:	        swi     591                 # report the answer
                jr      $31                 # End program
