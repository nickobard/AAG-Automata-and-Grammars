
Here are solutions to theoretical computer science tasks related to formal languages and automata theory. The tasks involve designing grammars, proving properties of languages, and determining the regularity of languages using concepts such as context-free grammars, regular grammars, finite automata, and the pumping lemma.

## File Structure

```
.
├── README.md
├── task_01
│   ├── task_hw_1_en.pdf
│   ├── task_hw_1_en.tex
│   ├── zadani-du-1-cz.pdf
│   └── zadani-du-1_cz.tex
└── task_03
    ├── automat.png
    ├── task_hw_3_en.pdf
    ├── task_hw_3_en.tex
    ├── zadani-du-3-cz.pdf
    └── zadani-du-3_cz.tex
```

## Task 1: Context-Free Grammar Design and Language Properties

### Description

In **task_01**, we are presented with two problems:

1. **Designing a Context-Free Grammar (CFG):**

    - **Task:** Design a CFG for the language $ L_1 $ defined as:
      $$
      L_1 = \{ w \in \{ \mathtt{a}, \mathtt{b}, \mathtt{c} \}^* \mid w = w^R \} \cap \{ u \in \{ \mathtt{a}, \mathtt{b} \}^* \mid |u|_{\mathtt{a}} \bmod 3 = 0 \}
      $$
      where $ w^R $ is the reverse of string $ w $, and $ |x|_a $ denotes the number of occurrences of symbol $a$ in string $x $.

    - **Solution Overview:** The task requires constructing a CFG that generates palindromes over the alphabet $ \{a, b\} $ with the number of $ a $ symbols divisible by 3. The solution involves defining non-terminal symbols that keep track of the modulo 3 count of $ a $ symbols during derivations.

2. **Proving Statements about Regular Languages:**

    - **Statement 1:** Every finite language is regular.
    - **Statement 2:** Every regular language is finite.

    - **Solution Overview:**
        - For **Statement 1**, the proof uses mathematical induction to show that finite languages can be represented by regular expressions or finite automata, and thus are regular.
        - For **Statement 2**, a counterexample is provided by constructing an infinite regular language (e.g., the language of all strings over a single symbol), demonstrating that not all regular languages are finite.

### Files

- `task_hw_1_en.tex`: English LaTeX source file containing the tasks and detailed solutions.
- `task_hw_1_en.pdf`: Compiled PDF of the English version.
- `zadani-du-1_cz.tex`: Original Czech LaTeX source file.
- `zadani-du-1-cz.pdf`: Compiled PDF of the Czech version.

## Task 3: Regularity of Languages and the Pumping Lemma

### Description

In **task_03**, we analyze two languages to determine their regularity and, if they are regular, find the smallest possible pumping lemma constant $ p $.

1. **Language $ L_1 $:**

    - **Definition:**
      $$
      L_1 = \left\{ w \in \{\mathtt{a}, \mathtt{b}\}^* \mid |w|_{\mathtt{a}} \bmod 3 = |w|_{\mathtt{b}} \right\} \cap \left\{ \mathtt{a}^m \mathtt{b}^j \mathtt{b}^i \mid m, j, i \in \mathbb{N}_0, j < m \right\}
      $$
      where $ |w|_{\mathtt{a}} $ and $ |w|_{\mathtt{b}} $ denote the number of $ a $ and $ b $ symbols in $ w $, respectively.

    - **Task:** Determine if $ L_1 $ is regular. If it is, describe it using a formalism for regular languages (FA, RG, or RE) and find the minimal pumping lemma constant $ p $.

    - **Solution Overview:** By simplifying the language and constructing a finite automaton (illustrated in `automat.png`), we demonstrate that $ L_1 $ is regular. We then use the pumping lemma to find the smallest possible constant $ p = 5 $ that satisfies the conditions of the lemma for $ L_1 $.

2. **Language $ L_2 $:**

    - **Definition:**
      $$
      L_2 = \{ 2^m 1^n 2^j \mid m, n, j \in \mathbb{N}, m > 1, n \geq 1, j \geq 1, j \neq m + n \}
      $$

    - **Task:** Determine if $ L_2 $ is regular. If it is, describe it using a formalism for regular languages and find the minimal pumping lemma constant $ p $.

    - **Solution Overview:** We prove that $ L_2 $ is not regular by using the pumping lemma for regular languages. We show that the language does not satisfy the necessary conditions of the pumping lemma, and thus cannot be regular.

### Files

- `task_hw_3_en.tex`: English LaTeX source file containing the tasks and detailed solutions.
- `task_hw_3_en.pdf`: Compiled PDF of the English version.
- `automat.png`: Image of the finite automaton used in the solution for $ L_1 $.
- `zadani-du-3_cz.tex`: Original Czech LaTeX source file.
- `zadani-du-3-cz.pdf`: Compiled PDF of the Czech version.

## How to Use

- **Viewing Solutions:** Open the PDF files in each task directory to read the tasks and their solutions.
- **Compiling LaTeX Files:** If you wish to view or edit the source files, you can compile the `.tex` files using a LaTeX compiler (e.g., `pdflatex`).

## Summary

This repository provides detailed solutions to problems in formal language theory. The tasks cover:

- Designing context-free grammars for specific languages.
- Proving properties of languages using induction and counterexamples.
- Determining the regularity of languages using the pumping lemma.
- Constructing finite automata to recognize regular languages.

The solutions are intended for educational purposes, to aid understanding of key concepts in automata theory and formal languages.

## Notes

- The original proofs were written in Czech and have been automatically translated into English.
- Care has been taken to ensure the correctness of the translations, but there may be minor discrepancies due to the automated process.
- The finite automaton image (`automat.png`) is included to illustrate the solution for one of the tasks.
