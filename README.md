# YANP — Yet Another Notepad

[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-20-brightgreen.svg)]()
[![Qt](https://img.shields.io/badge/Qt-6-green.svg)]()

**YANP (Yet Another Notepad)** is a lightweight, cross-platform classic desktop text editor written in **C++20** and **Qt 6 Widgets**.

Inspired by Dave Plummer's [TinyRetroPad](https://github.com/plummersSoftwareLLC/TinyRetroPad), YANP recreates the core Notepad-style user experience with clean, native desktop integration, safe file handling, and a maintainer-curated theme system.

---

## Key Features

- **Classic Desktop Interface:** Clean, distraction-free Notepad layout with native menus and status bar.
- **Robust File Operations:**
  - Create new document (`Ctrl+N`), Open (`Ctrl+O`), Save (`Ctrl+S`), Save As (`Ctrl+Shift+S`).
  - Safe atomic saving via `QSaveFile` (prevents data loss or file corruption upon disk write failures).
  - Dirty document indicator (`*filename - YANP`) with prompt to save, discard, or cancel on exit or document swap.
  - Native Drag-and-Drop file opening.
  - Command-line argument support (`./YANP document.txt`).
  - Text encoding detection & preservation: UTF-8, UTF-8 with BOM, UTF-16 LE, UTF-16 BE, and local 8-bit fallback.
  - Line ending detection (Windows CRLF vs Unix LF) with preservation on save.
- **Complete Editing Commands:**
  - Undo (`Ctrl+Z`), Cut (`Ctrl+X`), Copy (`Ctrl+C`), Paste (`Ctrl+V`), Delete (`Del`), Select All (`Ctrl+A`).
  - Model search dialogs:
    - **Find (`Ctrl+F`):** Forward and backward search, case sensitivity, wrap-around search, error reporting.
    - **Find Next (`F3`):** Repeat search from current cursor position.
    - **Replace (`Ctrl+H` / `Cmd+Option+F`):** Single replace, Replace All, replacement count feedback.
    - **Go To (`Ctrl+G` / `Cmd+L`):** Jump to line with boundary validation.
  - **Time/Date (`F5`):** Instantly inserts current timestamp at cursor or replaces selection.
- **Formatting & View Controls:**
  - **Word Wrap:** Toggle line wrapping with horizontal scrolling when disabled. Preserves cursor position.
  - **Font Selection:** Native font picker; persists user font family and size in `QSettings`.
  - **Status Bar:** Real-time `Ln X, Col Y`, encoding display, and line ending format. Can be toggled from View menu.
- **Printing:**
  - Native **Page Setup** dialog.
  - Full paginated **Print** support (`Ctrl+P`) via Qt Print Support.
- **Maintainer-Curated Themes:**
  - Centrally registered themes in source code (no runtime plugin risks or malformed user configs).
  - Shipped with:
    1. **System Default** (inherits operating system light/dark theme)
    2. **Classic Light** (crisp traditional Notepad)
    3. **Classic Dark** (restrained modern dark theme)
    4. **Retro Phosphor Green** (classic monochrome CRT VT100 / IBM 5151 terminal)
    5. **Amber CRT** (1980s amber phosphor terminal)
    6. **Solarized Dark** (popular precision palette)
  - Instantly applied without app restarts; persisted in `QSettings`.

---

## Keyboard Shortcuts

| Action | Windows / Linux | macOS |
|---|---|---|
| New | `Ctrl+N` | `Cmd+N` |
| Open | `Ctrl+O` | `Cmd+O` |
| Save | `Ctrl+S` | `Cmd+S` |
| Save As | `Ctrl+Shift+S` | `Cmd+Shift+S` |
| Print | `Ctrl+P` | `Cmd+P` |
| Exit | `Ctrl+Q` | `Cmd+Q` |
| Undo | `Ctrl+Z` | `Cmd+Z` |
| Cut | `Ctrl+X` | `Cmd+X` |
| Copy | `Ctrl+C` | `Cmd+C` |
| Paste | `Ctrl+V` | `Cmd+V` |
| Delete | `Del` | `Del` |
| Select All | `Ctrl+A` | `Cmd+A` |
| Find | `Ctrl+F` | `Cmd+F` |
| Find Next | `F3` | `F3` |
| Replace | `Ctrl+H` | `Cmd+Option+F` |
| Go To | `Ctrl+G` | `Cmd+L` |
| Time/Date | `F5` | `F5` |
| View Help | `F1` | `F1` |

---

## Building and Testing

### Prerequisites
- CMake 3.16+
- C++20 compatible compiler (GCC 11+, Clang 13+, MSVC 2022)
- Qt 6 (Core, Gui, Widgets, PrintSupport, Test)

### Build Instructions

```bash
# Configure
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build -j$(nproc)
```

Or using CMake Presets:
```bash
cmake --preset release
cmake --build --preset release
```

### Running Tests
Execute the automated test suite with CTest:
```bash
ctest --test-dir build --output-on-failure
```

### Running YANP
```bash
./build/YANP [optional_file_path.txt]
```

For detailed platform-specific setup on Windows, macOS, and Linux, refer to [docs/build.md](docs/build.md).

---

## Project Structure

```text
YANP/
├── CMakeLists.txt              # Root build configuration
├── CMakePresets.json           # Presets for Release, Debug, Test
├── README.md                   # Project overview & guide
├── CONTRIBUTING.md             # Contribution guidelines & Theme contribution guide
├── LICENSE                     # Apache 2.0 license
├── NOTICE                      # Upstream attribution notice
├── .gitignore
├── src/
│   ├── main.cpp                # Application entry point & CLI parser
│   ├── MainWindow.h/.cpp       # Window orchestration, menus, status bar, actions
│   ├── EditorWidget.h/.cpp     # QPlainTextEdit subclass with drag-and-drop & cursor tracking
│   ├── FileManager.h/.cpp      # File I/O, BOM/encodings, line endings, atomic writes
│   ├── SearchController.h/.cpp # Find, Replace, GoTo dialogs & search execution
│   ├── PrintManager.h/.cpp     # Printing and Page Setup support
│   ├── AboutDialog.h/.cpp      # Application and attribution about dialog
│   └── themes/
│       ├── Theme.h/.cpp        # Strongly-typed Theme struct & validation
│       ├── ThemeRegistry.h/.cpp# Central theme registry
│       ├── ThemeManager.h/.cpp # Theme application, palette, styling & persistence
│       └── definitions/        # Shipped compile-in theme implementations
│           ├── SystemDefaultTheme.h/.cpp
│           ├── ClassicLightTheme.h/.cpp
│           ├── ClassicDarkTheme.h/.cpp
│           ├── RetroGreenTheme.h/.cpp
│           ├── AmberCRTTheme.h/.cpp
│           └── SolarizedDarkTheme.h/.cpp
├── tests/
│   ├── CMakeLists.txt          # Test build configuration
│   ├── test_filemanager.cpp    # Unit tests for FileManager
│   ├── test_search.cpp         # Unit tests for SearchController
│   └── test_themes.cpp         # Unit tests for ThemeRegistry & ThemeManager
└── docs/
    ├── architecture.md         # Component diagrams and architecture details
    ├── build.md                # Cross-platform compilation and packaging
    └── themes.md               # Theme specifications and color tables
```

---

## Feature Verification Checklist

### File Operations
- [x] Create a new document (`Untitled`).
- [x] Open a text file via native file dialog.
- [x] Save an existing document.
- [x] Save a new document through Save As.
- [x] Cancel a file dialog without losing content.
- [x] Handle missing files and permission errors safely.
- [x] Atomic write via `QSaveFile` guarantees original file is never corrupted on write error.
- [x] Display unsaved-change asterisk (`*`) in title bar.
- [x] Prompt before discarding unsaved changes (Save / Discard / Cancel).
- [x] Open file supplied via CLI launch argument.
- [x] Open file via Drag-and-Drop.
- [x] UTF-8, UTF-8 with BOM, UTF-16 LE, and UTF-16 BE preservation.
- [x] Line ending detection and preservation (CRLF and LF).

### Editing Commands
- [x] Undo, Cut, Copy, Paste, Delete, and Select All.
- [x] Dynamic enabling/disabling of Cut/Copy/Delete based on selection.
- [x] Find dialog with forward, backward, case sensitivity, and wrap-around.
- [x] Find Next (`F3`).
- [x] Replace dialog with single Replace, Replace All, and replacement count.
- [x] Go To line dialog with line range validation and error display.
- [x] Time/Date insertion (`F5`).
- [x] Word Wrap toggle with horizontal scrollbar when disabled.
- [x] Font selection dialog and persistent font preferences.
- [x] Status bar with real-time `Ln X, Col Y`, encoding, and line endings.

### Printing
- [x] Page Setup dialog.
- [x] Print dialog and document printing via `QtPrintSupport`.
- [x] Printing preserves document contents intact.

### Maintainer-Defined Themes
- [x] All built-in themes registered centrally in `ThemeRegistry`.
- [x] View -> Theme menu dynamically populated from registry.
- [x] Instant theme application without app restart.
- [x] Selected theme persisted across launches via `QSettings`.
- [x] Missing or invalid theme IDs safely fall back to System Default.
- [x] Contributed themes can be added without modifying editor core logic.
- [x] Shipped themes work completely offline.
- [x] All themes validated for contrast and non-null styling in unit tests.
- [x] Zero user-facing theme creation or in-app theme editing (strict maintainer-curated design).

---

## Attribution and Licensing

YANP is inspired by **TinyRetroPad** by Dave Plummer (Plummer's Software LLC).
Reference: [https://github.com/plummersSoftwareLLC/TinyRetroPad](https://github.com/plummersSoftwareLLC/TinyRetroPad)

Licensed under the **Apache License, Version 2.0**. See [LICENSE](LICENSE) and [NOTICE](NOTICE) for details.
