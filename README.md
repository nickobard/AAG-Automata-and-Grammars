# Automata and Grammars Course Practicals

This repository contains solutions and implementations related to formal languages and automata theory. The tasks involve designing grammars, implementing algorithms, and proving language properties using concepts such as context-free grammars, finite automata, and the pumping lemma.

## Contents

### 1. Determinization of Finite Automata

**Directory**: `01 - Determinization`

- **Objective**: Implement an algorithm in C++ to determinize a non-deterministic finite automaton with multiple initial states (MISNFA) into an equivalent deterministic finite automaton (DFA) without unnecessary or unreachable states.
- **Main File**: `sample.cpp` containing the `determinize` function.

### 2. CYK Algorithm Application

**Directory**: `02 - CYK`

- **Objective**: Implement the Cocke–Younger–Kasami (CYK) algorithm in C++ to parse a word using a context-free grammar in Chomsky Normal Form (CNF) and provide a derivation if the word belongs to the language.
- **Main File**: `sample.cpp` containing the `trace` function.

### 3. Proofs and Theoretical Tasks

**Directory**: `proofs`

- **Task 1**: Context-Free Grammar Design and Language Properties
    - **Files**: `task_hw_1_en.pdf`, `task_hw_1_en.tex`, and corresponding Czech versions.
    - **Content**: Designing a CFG for a specific language and proving statements about regular languages.

- **Task 3**: Regularity of Languages and the Pumping Lemma
    - **Files**: `task_hw_3_en.pdf`, `task_hw_3_en.tex`, `automat.png`, and corresponding Czech versions.
    - **Content**: Determining the regularity of given languages and using the pumping lemma to prove or disprove regularity.

## Notes

- The original proofs are in Czech and have been translated into English.
- The solutions are for educational purposes to aid understanding of formal languages and automata theory.

## Repository Structure

```
.
├── 01 - Determinization
│   ├── .gitignore
│   ├── .gitkeep
│   ├── README.md
│   └── sample.cpp
├── 02 - CYK
│   ├── .gitignore
│   ├── .gitkeep
│   ├── README.md
│   └── sample.cpp
├── .gitignore
├── proofs
│   ├── 01 - Context-Free Grammar Design and Language Properties
│   │   ├── task_hw_1_en.pdf
│   │   ├── task_hw_1_en.tex
│   │   ├── zadani-du-1-cz.pdf
│   │   └── zadani-du-1_cz.tex
│   ├── 03 - Regularity of Languages and the Pumping Lemma
│   │   ├── automat.png
│   │   ├── task_hw_3_en.pdf
│   │   ├── task_hw_3_en.tex
│   │   ├── zadani-du-3-cz.pdf
│   │   └── zadani-du-3_cz.tex
│   └── README.md
└── README.md

6 directories, 20 files

```

