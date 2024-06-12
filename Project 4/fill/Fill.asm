// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Initialize R2 to 0 (to store the result)
@R2
M=0

// Check if R0 or R1 is zero, jump to END if either is zero
@R0
D=M
@CHECK_R1
D;JEQ

(CHECK_R1)
@R1
D=M
@END
D;JEQ

// Main loop to multiply R1 and R0 using repeated addition
(MULTIPLY)
    // Add R1 to R2
    @R2
    D=M
    @R1
    D=D+M
    @R2
    M=D

    // Decrement R0
    @R0
    D=M-1
    M=D

    // If R0 is not zero, repeat the loop
    @MULTIPLY
    D;JNE

// End of the program
(END)
    @END
    0;JMP
