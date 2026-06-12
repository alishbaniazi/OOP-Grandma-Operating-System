# Grandma's Computer System

A fully object-oriented C++ simulation of a personal computer built for a non-technical user — modelling hardware resources, application lifecycle management, file operations, and a calculator with history and statistics, all through a clean console interface.

---

## Project Overview

This project was built as part of **CS-1004 Object-Oriented Programming (Spring 2026)** at **FAST-NUCES**. The theme: your grandmother wants to digitize her decades of handwritten journals. You build her a custom computer — simple on the outside, complex under the hood.

The user never touches RAM, disk pointers, or memory — she just says *"Open the calculator"* or *"I accidentally deleted something, get it back!"* and the system handles everything invisibly.

---

## Project Structure

```
├── Header.h          # All class definitions and inline menu functions
├── main.cpp          # Entry point and top-level computer boot flow
├── pch.h             # Precompiled header
```

---

## Architecture

### Hardware Layer
| Class | Responsibility |
|-------|---------------|
| `Storage` | Fixed-capacity disk. Saves, deletes, and retrieves `File` objects. Dynamically grows its internal array. |
| `RAM` | Fixed memory pool. Allocated on app launch, freed on close. Never goes below zero. |

### Application Layer
| Class | Disk | RAM |
|-------|------|-----|
| `FileExplorer` | 20 MB | 50 MB |
| `RecycleBin` | 10 MB | 30 MB |
| `Calculator` | 15 MB | 40 MB |
| `Settings` | 5 MB | 20 MB |

### Coordinator
- **`ApplicationManager`** — manages app lifecycle (launch, close, status checks), creates pre-installed app files on `Storage` at boot.
- **`Computer`** — the single public interface. All of Grandma's interactions go through here.

---

## Features

### File Management
- Create, delete, view, and list files via `FileExplorer`
- Deleted files move to `RecycleBin` (if running) before permanent removal
- Restore files from bin back to storage
- Merge two files with the `+` operator (combined name, content, and size)
- Compare files by size with the `<` operator
- Empty the recycle bin permanently

### Calculator
- Basic arithmetic: add, subtract, multiply, divide, power, square root
- Full calculation history stored as human-readable strings (e.g. `"3 + 4 = 7"`)
- 26 named variables (A–Z), case-insensitive
- Statistical queries: mean, sum, min, max over all stored results
- Export history to a file in Storage
- Operator overloads: `()` for calculation dispatch, `[]` for variable recall

### Settings
- 5 predefined keys: `font_size`, `font_family`, `theme`, `language`, `date_format`
- Get, set, display, and reset to defaults
- Rejects unknown keys gracefully

### System Status
- Live display of storage usage, RAM availability, and per-app running state
- `<<` operator overload for clean console output of full system status
- `>` operator to compare two computers by available RAM
- `+=` / `-=` shorthand operators for launching and closing apps

---

## Getting Started

### Requirements
- Visual Studio 2019 or above
- C++17 or later

### Build & Run
1. Open the solution in Visual Studio
2. Build the project (`Ctrl+Shift+B`)
3. Run (`F5` or `Ctrl+F5`)
4. Enter your desired storage and RAM when prompted

### Minimum Requirements at Boot
| Resource | Minimum |
|----------|---------|
| Storage | 50 MB (for pre-installed apps) |
| RAM | Any positive value |

---

## Usage Flow

```
Main Menu
 └── Boot Up Computer  (enter storage + RAM)
      ├── Application Manager  (launch / close / check apps)
      ├── File Manager         (create / delete / restore / merge files)
      ├── Calculator           (arithmetic, variables, stats, history export)
      ├── Settings             (font, theme, language, date format)
      └── System Status        (live usage + operator demos)
```

---

## Design Highlights

- **No STL strings or string libraries** — all strings are raw `char*` with manual deep-copy, length, and comparison helpers
- **No `cmath` or `cstring`** — custom `sqrt` (Newton's method), `pow`, `len`, `copystr`, `areEqual`, `inttostr` implemented from scratch
- **Dynamic memory throughout** — all arrays double in capacity when full, with proper cleanup in destructors
- **Copy constructors** on every class that owns heap memory
- **Forward declaration** used to break the circular dependency between `FileExplorer` and `RecycleBin`

---

## Operator Summary

| Operator | Class | Meaning |
|----------|-------|---------|
| `+` | `File` | Merge two files |
| `<` | `File` | Compare by size |
| `+=` | `Computer` | Launch app shorthand |
| `-=` | `Computer` | Close app shorthand |
| `>` | `Computer` | Compare available RAM |
| `<<` | `Computer` | Print system status |
| `()` | `Calculator` | Dispatch arithmetic by operator char |
| `[]` | `Calculator` | Recall variable by letter |
| `-` | `RecycleBin` | Permanently delete file from bin and storage |

---

## Author

Built for **CS-1004 OOP Assignment 2** — FAST-NUCES, Spring 2026.
