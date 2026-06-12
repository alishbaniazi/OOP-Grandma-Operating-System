# Design Constraints

## Grandma's Computer System — CS-1004 OOP Assignment 2

This document outlines the technical constraints, deliberate design decisions, and known limitations of the implementation.

---

## 1. Language & Library Restrictions

Per assignment rules, the following are **strictly prohibited**:

- No `<string>`, `<cstring>`, `<cmath>`, or any other standard utility library
- No built-in functions such as `strlen`, `strcmp`, `strcpy`, `pow`, `sqrt`
- No STL containers (`vector`, `list`, `map`, etc.)
- No AI-generated or copied code

All of the following were implemented from scratch in `Header.h`:

| Helper | Implementation |
|--------|---------------|
| `len(const char*)` | Recursive character count |
| `copystr(src, dst, size)` | Recursive character-by-character copy |
| `areEqual(s1, s2, size)` | Recursive character comparison |
| `sqrt(double)` | Newton's method, 100 iterations |
| `pow(double, int)` | Recursive multiplication |
| `inttostr(long long)` | Manual digit extraction with sign handling |

---

## 2. Memory Management Rules

- Every class that owns heap memory implements a **destructor**, **copy constructor**, and where relevant a proper **assignment path**
- `File` deep-copies both `name` and `content` on every construction and copy
- `Storage` deep-copies `File` objects on `saveFile` — it owns its own copies
- `RecycleBin` deep-copies `File` objects on `addFile` — independent from Storage copies
- Dynamic arrays (`File**`, `char**`, `double*`) all double in capacity when full
- No raw pointer is reused after `delete` — dangling pointer risk is managed by setting to `nullptr` post-free

---

## 3. Circular Dependency Resolution

`FileExplorer::deleteFile` requires a `RecycleBin*` parameter, but `RecycleBin` is defined after `FileExplorer` in the header.

**Resolution:** `RecycleBin` is forward-declared at the top of `Header.h`. The `deleteFile` method body is defined **after** the full `RecycleBin` class definition using an `inline` out-of-class implementation.

---

## 4. Application Constraints

### RAM
- An application can only be launched if sufficient RAM is available
- RAM is deallocated immediately on `closeApp`
- `usedMemory` is floor-clamped at zero in `deallocate` — it cannot go negative

### Storage
- Files are stored as deep-copied pointers in a dynamically growing `File**` array
- The internal array starts at capacity 10 and doubles when all slots are full
- `deleteFile` compacts the array by shifting — no gaps are left
- Storage does **not** shrink after deletion (conservative design)

### Applications
- An application can only perform operations when `isRunning == true`
- All methods return a safe failure value (`false`, `0.0`, `nullptr`) if the app is not running
- Pre-installed app files (FileExplorer, RecycleBin, Calculator, Settings) are created and saved to Storage during `ApplicationManager` construction — they consume disk space from the moment the computer boots

---

## 5. FileExplorer & RecycleBin Interaction

- `Computer::deleteFile` always goes through `FileExplorer::deleteFile(name, RecycleBin*)`
- If `RecycleBin` is running, the file is **copied into the bin before removal** from Storage
- If `RecycleBin` is not running, the file is permanently removed immediately
- `RecycleBin::restoreFile` moves the file back to Storage and removes it from the bin; if Storage has insufficient space the restore fails and the file remains in the bin

---

## 6. Calculator Constraints

- History strings are manually constructed using `inttostr` — floating-point decimal portions are truncated (cast to `long long`) due to no `<cmath>` or `sprintf` availability
- History and memory arrays both start at capacity 5 and double independently
- Division by zero prints an error to `cout` and returns `0.0` without adding to history or memory
- Square root of a negative value prints an error and returns `0.0`
- `exportHistory` creates a 1 MB `File` and appends all history entries as content via `setContent`; it requires Storage to have at least 1 MB free

---

## 7. Settings Constraints

- Exactly 5 keys are supported: `font_size`, `font_family`, `theme`, `language`, `date_format`
- The internal arrays are initialised at capacity 5 and **never grow** — the spec fixes the count
- `setSetting` only updates existing keys; it **does not insert new keys** and returns `false` for unknown keys
- `resetToDefault` reallocates the values array with the original defaults

---

## 8. Computer Interface Constraints

- `Computer` is the **only public interface** — Grandma never touches `Storage`, `RAM`, or `ApplicationManager` directly
- `getApp(const char*)` returns `void*`; the `Computer` accessor methods (`getFileExplorer`, etc.) perform the type cast internally
- `operator<<` mirrors `displaySystemStatus()` exactly — both iterate the same app set in the same order
- `operator>` compares **available** RAM (not total RAM), reflecting real-time system load

---

## 9. Known Limitations

| Limitation | Reason |
|------------|--------|
| Floating-point history entries are truncated to integers | No `sprintf` / `<cstdio>` allowed; `inttostr` only handles `long long` |
| `areEqual` does not check length parity before character comparison | Length is pre-checked at call sites in `Storage::deleteFile` and `getFile` |
| `RecycleBin::addFile` doubles `maxFiles` on every add rather than only when full | Minor logic bug — functionally harmless but wastes capacity |
| No assignment operator (`operator=`) on most classes | Not required by test cases; copy constructors cover the tested scenarios |
| `Storage` array never shrinks after deletions | Conservative choice; reallocation on shrink was deemed unnecessary for the assignment scope |

---

## 10. Compiler & Platform

- **Compiler:** MSVC (Visual Studio 2019+)
- **Standard:** C++17
- **Precompiled header:** `pch.h` (required by the VS project template)
- **Test guard:** `#ifndef TESTING` wraps `main` to allow Google Test integration without `main` conflicts
