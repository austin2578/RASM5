.section .text
.global bubbleSortA

bubbleSortA:
    // x0: Address of the array
    // x1: Length of the array

    mov x2, x1         // Load the length value
    mov x3, #0         // Outer loop counter (i = 0)
    
outer_loop:
    cmp x3, x2         // Compare i with length
    bge end_program    // If i >= length, end the program

    mov x4, #0         // Inner loop counter (j = 0)

inner_loop:
    cmp x4, x2         // Compare j with length
    bge end_inner_loop // If j >= length, end the inner loop

    sub x5, x2, x4     // Calculate length - j
    sub x5, x5, #1     // Calculate length - j - 1

    cmp x3, x5         // Compare i with length - j - 1
    bge next_outer_loop // If i >= length - j - 1, move to the next outer loop

    // Your code for processing array elements goes here
    ldr x6, [x0]       // Load a[j]
    add x0, x0, #4     // Assuming 32-bit integers, increment x0 to point to the next element
    ldr x7, [x0]       // Load a[j + 1]
    sub x0, x0, #4     // Reset x0 to point back to the current element

    cmp x6, x7
    ble no_swap
    
    // Swap a[j] and a[j + 1]
    str x7, [x0]       // Store a[j] = a[j + 1]
    add x0, x0, #4     // Increment x0 to point to the next element
    str x6, [x0]       // Store a[j + 1] = a[j]
    sub x0, x0, #4     // Reset x0 to point back to the current element

no_swap:
    add x4, x4, #1     // Increment inner loop counter
    b inner_loop

next_outer_loop:
    add x3, x3, #1     // Increment outer loop counter
    b outer_loop

end_inner_loop:
    b end_program

end_program:
    // Your sorted array is now in the "array" variable

    ret
    