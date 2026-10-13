#include "RetroGreenTheme.h"

namespace YANP::Themes {

Theme createRetroGreenTheme() {
    Theme theme;
    theme.id = QStringLiteral("retro-green");
    theme.name = QStringLiteral("Retro Phosphor Green");
    theme.isSystemDefault = false;

    theme.windowBackground = QColor(10, 20, 10);
    theme.editorBackground = QColor(5, 12, 5);
    theme.textColor = QColor(51, 255, 51);
    theme.selectionBackground = QColor(0, 85, 0);
    theme.selectedTextColor = QColor(153, 255, 153);
    theme.caretColor = QColor(51, 255, 51);
    theme.statusBarBackground = QColor(12, 28, 12);
    theme.statusBarTextColor = QColor(40, 200, 40);
    theme.borderColor = QColor(20, 50, 20);

    theme.defaultFontFamily = QStringLiteral("Monospace");
    theme.defaultFontSize = 11;

    return theme;
}

} // namespace YANP::Themes
