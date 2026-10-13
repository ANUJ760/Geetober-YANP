# Contributing to YANP

Thank you for your interest in contributing to **YANP (Yet Another Notepad)**!

YANP follows a philosophy of minimalism, cross-platform reliability, and maintainability.

---

## 1. Code of Conduct and General Guidelines

- We use **C++20** and **Qt 6 Widgets**.
- Keep dependencies minimal: do not add external third-party libraries without prior discussion.
- Preserve platform-native conventions (dialogs, keybindings, and menus).
- Ensure all automated unit tests (`ctest`) pass before submitting a pull request.

---

## 2. Maintainer-Defined Theme Contribution Workflow

YANP themes are **curated and shipped as part of the application source code**. There are deliberately no runtime plugin loaders or user-facing theme creators. All themes are compiled in and available offline to all users in subsequent releases.

### Step 1: Open an Issue
Before creating a theme, open a GitHub issue with the title `[Theme Proposal] <Theme Name>`:
- Describe the aesthetic inspiration (e.g., vintage terminal, retro computer, classic paper).
- Provide proposed hex color values for:
  - Editor background & text
  - Window & status bar
  - Selection background & text
  - Caret color
- Explain how contrast and readability are ensured.

### Step 2: Implement the Theme Definition
Create a new header and source file in `src/themes/definitions/`:

**`src/themes/definitions/MyNewTheme.h`**:
```cpp
#pragma once

#include "../Theme.h"

namespace YANP::Themes {

Theme createMyNewTheme();

} // namespace YANP::Themes
```

**`src/themes/definitions/MyNewTheme.cpp`**:
```cpp
#include "MyNewTheme.h"

namespace YANP::Themes {

Theme createMyNewTheme() {
    Theme theme;
    theme.id = QStringLiteral("my-new-theme"); // Stable unique identifier (kebab-case)
    theme.name = QStringLiteral("My New Theme"); // Human-readable display name
    theme.isSystemDefault = false;

    theme.windowBackground = QColor(30, 30, 30);
    theme.editorBackground = QColor(20, 20, 20);
    theme.textColor = QColor(240, 240, 240);
    theme.selectionBackground = QColor(60, 90, 140);
    theme.selectedTextColor = QColor(255, 255, 255);
    theme.caretColor = QColor(255, 255, 255);
    theme.statusBarBackground = QColor(35, 35, 35);
    theme.statusBarTextColor = QColor(200, 200, 200);
    theme.borderColor = QColor(50, 50, 50);

    theme.defaultFontFamily = QStringLiteral("Monospace");
    theme.defaultFontSize = 11;

    return theme;
}

} // namespace YANP::Themes
```

### Step 3: Register in ThemeRegistry
In `src/themes/ThemeRegistry.cpp`:
1. Include `#include "definitions/MyNewTheme.h"`
2. Add `registerTheme(Themes::createMyNewTheme());` in `registerDefaults()`.

### Step 4: Add to CMake
In `CMakeLists.txt` and `tests/CMakeLists.txt`, add the new `.h` and `.cpp` files to the target sources.

### Step 5: Verify and Test
Add an assertion in `tests/test_themes.cpp`:
```cpp
QVERIFY(ThemeRegistry::instance().hasTheme(QStringLiteral("my-new-theme")));
```
Run the test suite:
```bash
ctest --test-dir build --output-on-failure
```

### Step 6: Submit a Pull Request
1. Provide screenshots of the theme applied in YANP.
2. Confirm contrast ratios meet accessibility standards.
3. State attribution for any referenced design or color palette.

---

## 3. Theme Quality Criteria

- **High Contrast & Readability:** Text must be immediately legible against the background.
- **Selection Readability:** Selected text must remain clear against the selection highlight.
- **Distinct Caret:** The cursor / caret must be easily spotted during editing.
- **Distraction-Free:** Avoid jarring or extreme neon colors unless deliberately emulating specific retro CRT phosphor hardware.
- **Cross-Platform:** Fonts must fall back to standard monospace font families.
