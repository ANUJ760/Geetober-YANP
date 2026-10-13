#include "SolarizedDarkTheme.h"

namespace YANP::Themes {

Theme createSolarizedDarkTheme() {
    Theme theme;
    theme.id = QStringLiteral("solarized-dark");
    theme.name = QStringLiteral("Solarized Dark");
    theme.isSystemDefault = false;

    theme.windowBackground = QColor(7, 54, 66);
    theme.editorBackground = QColor(0, 43, 54);
    theme.textColor = QColor(131, 148, 150);
    theme.selectionBackground = QColor(10, 68, 83);
    theme.selectedTextColor = QColor(147, 161, 161);
    theme.caretColor = QColor(147, 161, 161);
    theme.statusBarBackground = QColor(9, 48, 59);
    theme.statusBarTextColor = QColor(131, 148, 150);
    theme.borderColor = QColor(20, 75, 90);

    theme.defaultFontFamily = QStringLiteral("Monospace");
    theme.defaultFontSize = 11;

    return theme;
}

} // namespace YANP::Themes
