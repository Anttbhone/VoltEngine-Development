### VoltEngine-Development ###

## Volt-Log 1 ##

* Decided to stop working on the 1B parameters LLM due to Hardware limitations and the steep learning curve.

* Made the decision to build a small 100~ parameters XOR problem solver first to learn more about backpropogation, foward passing, weights and bias.

1. Re-organized files.
2. Deleted non-needed scripts.
3. Updated README.md

* Log made in 24th June(Wednesday), 2026, 8:25 p.m.

## Volt-Log 2 ##

* Learnt how to make a MSE Loss Engine and a Foward Pass by a Vitrual Mentor(Gemini 3.1)

<details>
<summary>Click to see Output of program.</summary>

```text
--- Dataset Verification ---
Xor Input: 1 0 | Xor Target: 1
Xor Input: 0 1 | Xor Target: 1
Xor Input: 1 1 | Xor Target: 0
Xor Input: 0 0 | Xor Target: 0

--- Computing Hidden Layer Outputs ---

--- Computing Final AI Guesses ---
Scenario 0 AI Guess: 0.430894 | Correct Target: 1
Scenario 1 AI Guess: 0.437724 | Correct Target: 1
Scenario 2 AI Guess: 0.411697 | Correct Target: 0
Scenario 3 AI Guess: 0.46295 | Correct Target: 0
Total Loss: 0.255963
Row 0 | Gradient Error Delta: -0.139559
Row 1 | Gradient Error Delta: -0.138388
Row 2 | Gradient Error Delta: 0.099714
Row 3 | Gradient Error Delta: 0.115102
```

</details>

1. Updated README.md

* Log made in 28th June(Sunday), 2026, 12:39 p.m.
