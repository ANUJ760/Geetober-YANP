#pragma once

#include "Theme.h"
#include <vector>
#include <optional>
#include <memory>

namespace YANP {

class ThemeRegistry {
public:
    static ThemeRegistry& instance();

    bool registerTheme(const Theme& theme);
    std::vector<Theme> registeredThemes() const;
    std::optional<Theme> getTheme(const QString& id) const;
    bool hasTheme(const QString& id) const;
    Theme defaultTheme() const;

    // Reset registry (useful for unit testing)
    void resetToDefaults();

private:
    ThemeRegistry();
    void registerDefaults();

    std::vector<Theme> m_themes;
};

} // namespace YANP
