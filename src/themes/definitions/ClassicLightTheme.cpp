#include "ClassicLightTheme.h"

namespace YANP::Themes {

Theme createClassicLightTheme() {
    Theme theme;
    theme.id = QStringLiteral("classic-light");
    theme.name = QStringLiteral("Classic Light");
    theme.isSystemDefault = false;

    theme.windowBackground = QColor(240, 240, 240);
    theme.editorBackground = QColor(255, 255, 255);
    theme.textColor = QColor(0, 0, 0);
    theme.selectionBackground = QColor(0, 120, 215);
    theme.selectedTextColor = QColor(255, 255, 255);
    theme.caretColor = QColor(0, 0, 0);
    theme.statusBarBackground = QColor(225, 225, 225);
    theme.statusBarTextColor = QColor(30, 30, 30);
    theme.borderColor = QColor(200, 200, 200);

    theme.defaultFontFamily = QStringLiteral("Monospace");
    theme.defaultFontSize = 11;

    return theme;
}

} // namespace YANP::Themes
