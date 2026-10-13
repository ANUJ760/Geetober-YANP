#include "SystemDefaultTheme.h"

namespace YANP::Themes {

Theme createSystemDefaultTheme() {
    Theme theme;
    theme.id = QStringLiteral("system-default");
    theme.name = QStringLiteral("System Default");
    theme.isSystemDefault = true;
    theme.defaultFontFamily = QStringLiteral("Monospace");
    theme.defaultFontSize = 11;
    return theme;
}

} // namespace YANP::Themes
