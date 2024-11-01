# Determinization of a Finite Automaton with Multiple Initial States

Here is my implementation of an algorithm for determinizing a non-deterministic finite automaton with multiple initial states (MISNFA) into a deterministic finite automaton (DFA) in C++. The implementation is provided in the `sample.cpp` file.

## Problem Description

The task is to implement a function that converts a given MISNFA into an equivalent DFA without any unnecessary or unreachable states. The language accepted by the DFA should be equivalent to the language accepted by the original MISNFA.

### Key Points:

- **MISNFA (Multiple Initial States NFA)**: An NFA that may have multiple initial states.
- **DFA (Deterministic Finite Automaton)**: An automaton where for each state and input symbol, there is exactly one transition to a next state.
- **Determinization Algorithm**: The process of converting an NFA (possibly with multiple initial states) into an equivalent DFA.
- **Constraints**:
    - The resulting DFA must not have any unnecessary (useless) or unreachable states.
    - If the language of the automaton is empty, the DFA should be a single-state automaton over the same alphabet as the original automaton.
    - The implementation should adhere strictly to the specified function signature.

### Function Signature

The core function to implement is:

```cpp
DFA determinize(const MISNFA &nfa);
```

- **Input**: An MISNFA represented by the `MISNFA` structure.
- **Output**: A DFA represented by the `DFA` structure.

## Implementation Overview

The `sample.cpp` file contains the implementation of the determinization algorithm along with necessary supporting functions. The code is structured to be compatible with a testing environment that expects the exact function signature and data structures.

### Data Structures

- **State**: Defined as `unsigned int`, represents a state in the automaton.
- **Symbol**: Defined as `char`, represents an input symbol from the automaton's alphabet.
- **MISNFA Structure**:
    - `m_States`: Set of all states in the MISNFA.
    - `m_Alphabet`: Set of symbols that form the automaton's input alphabet.
    - `m_Transitions`: Map representing the transition function. Each key is a `(State, Symbol)` pair, and the value is a set of destination states.
    - `m_InitialStates`: Set of initial states.
    - `m_FinalStates`: Set of accepting (final) states.
- **DFA Structure**:
    - `m_States`: Set of all states in the DFA.
    - `m_Alphabet`: Set of symbols that form the automaton's input alphabet.
    - `m_Transitions`: Map representing the transition function. Each key is a `(State, Symbol)` pair, and the value is a single destination state.
    - `m_InitialState`: Single initial state.
    - `m_FinalStates`: Set of accepting (final) states.

### Key Functions

1. **`reduce_initial_states`**:
    - Purpose: Converts an MISNFA with multiple initial states into an NFA with a single initial state by introducing a new initial state that transitions to all original initial states.
    - Steps:
        - If there's only one initial state, returns the NFA as is.
        - Otherwise, creates a new initial state and adds transitions from this state to all original initial states for each symbol in the alphabet.

2. **`remove_unreachable_states`**:
    - Purpose: Removes states that are not reachable from the initial state.
    - Steps:
        - Performs a breadth-first search (BFS) starting from the initial state.
        - Collects all reachable states and transitions.

3. **`remove_useless_states`**:
    - Purpose: Removes states that do not lead to any accepting state (useless states).
    - Steps:
        - Performs a reverse BFS starting from the accepting states.
        - Collects all states and transitions that can reach an accepting state.

4. **`to_NFA`**:
    - Purpose: Converts an MISNFA to an NFA without unreachable or useless states.
    - Steps:
        - Calls `reduce_initial_states`, `remove_unreachable_states`, and `remove_useless_states` in sequence.

5. **`to_DFA`**:
    - Purpose: Converts the cleaned NFA into a DFA using the standard subset construction algorithm.
    - Steps:
        - Uses a queue to process state subsets.
        - For each subset of NFA states, creates a corresponding DFA state.
        - Determines transitions based on the NFA transitions for each symbol.
        - Marks DFA states as accepting if any NFA state in the subset is accepting.

6. **`determinize`**:
    - Purpose: The main function that integrates all steps to convert an MISNFA to a DFA.
    - Steps:
        - Calls `to_NFA` to clean the MISNFA.
        - Calls `to_DFA` to perform the determinization.

### Testing and Debugging

The code includes functions wrapped in conditional compilation blocks (`#ifndef __PROGTEST__` and `#endif`) for testing purposes:

- **Printing Functions**:
    - `print_MISNFA_table`: Prints the MISNFA transition table.
    - `print_NFA_table`: Prints the NFA transition table.
    - `print_DFA_table`: Prints the DFA transition table.

These functions help visualize the automata during testing and debugging.

### Important Notes

- The code is designed to work within a specific testing environment that may remove or modify certain parts of the code during compilation (e.g., the `main` function and included headers).
- The `constexpr State UNDEF = -1;` is used to represent an undefined state during processing.

## Summary

This implementation provides a step-by-step approach to determinize an MISNFA:

1. **Reducing Multiple Initial States**: Converts MISNFA to NFA with a single initial state.
2. **Removing Unreachable States**: Cleans the NFA by removing states that cannot be reached from the initial state.
3. **Removing Useless States**: Further cleans the NFA by removing states that do not lead to any accepting states.
4. **Determinization**: Applies the subset construction algorithm to convert the cleaned NFA into a DFA.

The resulting DFA is equivalent to the original MISNFA in terms of the language it accepts but is deterministic and optimized by removing unnecessary states.
