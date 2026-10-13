# YANP Theme System Documentation

## Overview

YANP features a **maintainer-defined theme system**. Rather than relying on fragile runtime plugins or arbitrary user-injected stylesheets, themes are strongly typed, curated, and compiled directly into the application.

This ensures:
- Instant switching between themes without application restarts.
- Guaranteed high contrast and readability.
- Reliable cross-platform palette and styling across Windows, macOS, and Linux.
- Offline availability with zero external file dependencies or runtime security risks.

---

## Shipped Themes

YANP currently ships with the following built-in themes:

| Theme ID | Display Name | Background | Text Color | Caret Color | Accent / Selection | Aesthetic |
|---|---|---|---|---|---|---|
| `system-default` | **System Default** | System Palette | System Palette | System | System Accent | Follows OS native dark/light theme |
| `classic-light` | **Classic Light** | `#FFFFFF` | `#000000` | `#000000` | `#0078D7` | Clean, crisp traditional Notepad |
| `classic-dark` | **Classic Dark** | `#18191B` | `#E6E6E6` | `#C8C8C8` | `#264F78` | Modern restrained dark mode |
| `retro-green` | **Retro Phosphor Green**| `#050C05` | `#33FF33` | `#33FF33` | `#005500` | Vintage VT100 / IBM 5151 monochrome CRT monitor |
| `amber-crt` | **Amber CRT** | `#0C0802` | `#FFB000` | `#FFB000` | `#664400` | Classic 1980s amber phosphor terminal |
| `solarized-dark` | **Solarized Dark** | `#002B36` | `#839496` | `#93A1A1` | `#0A4453` | Ethan Schoonover's precision Solarized palette |

---

## Technical Specifications

### The `Theme` Data Structure

```cpp
struct Theme {
    QString id;                 // Unique identifier in kebab-case
    QString name;               // Human-readable title shown in View -> Theme
    bool isSystemDefault;       // When true, delegates to native system styling

    QColor windowBackground;    // Frame and menu bar background
    QColor editorBackground;    // Text area background
    QColor textColor;           // Main text font color
    QColor selectionBackground; // Highlight box color
    QColor selectedTextColor;   // Font color when selected
    QColor caretColor;          // Cursor caret color
    QColor statusBarBackground; // Status bar bottom pane
    QColor statusBarTextColor;  // Status bar text color
    QColor borderColor;         // Separators and menu border

    QString defaultFontFamily;  // e.g. "Monospace"
    int defaultFontSize = 11;

    bool isValid() const;
};
```

### Persistence and Safety

1. **Selection Persistence:** The selected theme's identifier is stored via `QSettings` under `theme/id`.
2. **Safe Fallback:** If a stored theme identifier is missing or invalid on subsequent launches, `ThemeManager` safely defaults to `system-default`.
3. **Immutability:** Shipped themes are statically registered at application startup in `ThemeRegistry`. They cannot be modified or deleted at runtime.
4. **Document Integrity:** Theme changes apply purely to widget styling; document text, line endings, and file content are strictly unaffected.

---

## Proposing and Adding New Themes

To contribute a new theme, see [CONTRIBUTING.md](../CONTRIBUTING.md).
