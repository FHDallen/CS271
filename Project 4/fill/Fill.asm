// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen
// by writing 'black' in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen by writing
// 'white' in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Starting point
@place
M=0     // Initialize place at upper left corner

(LOOP)
@KBD    // Take in keyboard value
D=M     // Put it into D
@WHITE
D;JEQ   // If keyboard value == 0 (not pressed) goto WHITE
@BLACK
0;JMP   // Otherwise, goto BLACK

(WHITE)
@place
D=M     // Put place into D
@MIN_PLACE
D;JLT   // Jump to LOOP if we are at less than minimum (0)
@SCREEN
A=M+D   // Calculate address in screen
M=0     // Fill pixel with white
@place
M=M-1   // Decrease place
@LOOP
0;JMP   // Jump to LOOP

(BLACK)
@place
D=M     // Put place into D
@MAX_PLACE
D;JGE   // Jump to LOOP if we are at the max (place >= 8192)
@SCREEN
A=M+D   // Calculate address in screen
M=-1    // Fill pixel with black
@place
M=M+1   // Increase place by 1
@LOOP
0;JMP   // Go back to LOOP

(END)
@END
0;JMP   // Infinite loop at end

// Constants
(MIN_PLACE)
@0

(MAX_PLACE)
@8192
