# VoltEngine Design

## The Goal
The AI needs to look at two inputs and guess the correct XOR output. 
XOR means if the inputs are different, the answer is 1. If they are the same, the answer is 0.

## How it Works
1. **The Dataset**: We check all 4 possible scenarios for XOR.
2. **Forward Pass**: The AI takes the inputs, multiplies them by weights, adds biases, and makes a guess.
3. **Loss Engine**: We use Mean Squared Error (MSE) to calculate a "Total Loss" score. This score tells us how far off the AI's guesses are from the real answers.
4. **Gradient Error Delta**: This tells us the direction the AI needs to change its weights to make better guesses next time.
