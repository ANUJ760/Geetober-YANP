#include "ClassicDarkTheme.h"

namespace YANP::Themes {

Theme createClassicDarkTheme() {
    Theme theme;
    theme.id = QStringLiteral("classic-dark");
    theme.name = QStringLiteral("Classic Dark");
    theme.isSystemDefault = false;

    theme.windowBackground = QColor(32, 33, 36);
    theme.editorBackground = QColor(24, 25, 27);
    theme.textColor = QColor(230, 230, 230);
    theme.selectionBackground = QColor(38, 79, 120);
    theme.selectedTextColor = QColor(255, 255, 255);
    theme.caretColor = QColor(200, 200, 200);
    theme.statusBarBackground = QColor(40, 42, 45);
    theme.statusBarTextColor = QColor(180, 185, 190);
    theme.borderColor = QColor(50, 52, 56);

    theme.defaultFontFamily = QStringLiteral("Monospace");
    theme.defaultFontSize = 11;

    return theme;
}

} // namespace YANP::Themes
