# week02-mini-project: Temperature Conversion App

EECE 2140 (Computing Fundamentals for Engineers), Fall 2026, Mini Project #01, Part B.

## Purpose

This is a small C++ terminal program that converts a temperature between Celsius and
Fahrenheit. It reads a conversion direction and a temperature, prints the
converted value, and rejects invalid input or unsupported directions. The
project also shows a test-driven workflow: acceptance tests as input /
expected-output files, a `test.sh` script that runs them with input
redirection and `diff`, and a GitHub Actions workflow that runs the tests on
every push and pull request.

## Setup

Requirements: a terminal (macOS or Ubuntu/WSL), `g++` with C++17 support, Git,
and Bash.

```bash
g++ --version
git --version
# Ubuntu only, if anything is missing:
sudo apt update
sudo apt install build-essential git gdb

git clone https://github.com/lucasperalta29/week02-mini-project.git
cd week02-mini-project
```

## Input/output contract

Input is one line: a direction letter, a space, then a temperature (any number,
including decimals and negatives).

| Direction | Meaning                | Formula                 | Output format |
|-----------|------------------------|-------------------------|---------------|
| `C`       | Celsius to Fahrenheit  | `F = C * 9 / 5 + 32`    | `<value> F`   |
| `F`       | Fahrenheit to Celsius  | `C = (F - 32) * 5 / 9`  | `<value> C`   |

Anything else prints exactly `Invalid input`.

| Test | Input   | Expected output | What it checks                          |
|------|---------|-----------------|-----------------------------------------|
| 1    | `C 0`   | `32 F`          | Celsius to Fahrenheit                   |
| 2    | `F 32`  | `0 C`           | Fahrenheit to Celsius                   |
| 3    | `X 10`  | `Invalid input` | Unsupported direction                   |
| 4    | `C abc` | `Invalid input` | Team edge case: non-numeric temperature |

The test files live in `tests/` as `inputN.txt` / `expectedN.txt` pairs.

## Build and run

```bash
mkdir -p build
g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp -o build/app
echo "C 100" | ./build/app
```

Example output:

```
212 F
```

## Test

```bash
bash test.sh
```

`test.sh` compiles the program with strict warnings, runs each test with input
redirection (`./build/app < tests/inputN.txt > build/actualN.txt`), and
compares the result to the expected file with `diff -u`. Because of `set -eu`,
it stops with a nonzero exit code at the first failing test. If every test
passes it prints:

```
All acceptance tests passed
```

GitHub Actions (`.github/workflows/cpp.yml`) runs the same `bash test.sh` on
every push and pull request. We deliberately broke an expected-output file
once to confirm the workflow turns red, then fixed it to turn it green again.

## Limitations

- Direction letters are case-sensitive: `c 0` and `f 32` are rejected.
- Only the first two values are read; extra text after the number is ignored
  (`C 100 extra` prints `212 F`).
- No physical range check: temperatures below absolute zero (for example
  `C -500`) are still converted.
- Results use C++'s default output precision (about 6 significant digits), so
  `F 100` prints `37.7778 C`.
- Only one conversion per run; there is no interactive loop or Kelvin support.

## AI-use disclosure

Our team used Claude (an AI assistant) for step-by-step guidance with Git,
GitHub (branches, pull requests, personal access tokens, tags), GitHub Actions,
and writing/running the terminal tests. All code, tests, and documentation were
reviewed, run, and understood by the team before being committed.
