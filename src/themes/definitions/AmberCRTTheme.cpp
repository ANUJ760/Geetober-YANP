#include "AmberCRTTheme.h"

namespace YANP::Themes {

Theme createAmberCRTTheme() {
    Theme theme;
    theme.id = QStringLiteral("amber-crt");
    theme.name = QStringLiteral("Amber CRT");
    theme.isSystemDefault = false;

    theme.windowBackground = QColor(20, 14, 5);
    theme.editorBackground = QColor(12, 8, 2);
    theme.textColor = QColor(255, 176, 0);
    theme.selectionBackground = QColor(102, 68, 0);
    theme.selectedTextColor = QColor(255, 204, 51);
    theme.caretColor = QColor(255, 176, 0);
    theme.statusBarBackground = QColor(28, 20, 7);
    theme.statusBarTextColor = QColor(229, 158, 0);
    theme.borderColor = QColor(50, 35, 12);

    theme.defaultFontFamily = QStringLiteral("Monospace");
    theme.defaultFontSize = 11;

    return theme;
}

} // namespace YANP::Themes
