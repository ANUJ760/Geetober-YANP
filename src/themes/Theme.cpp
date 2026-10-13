#include "Theme.h"

namespace YANP {

bool Theme::isValid() const {
    if (id.trimmed().isEmpty() || name.trimmed().isEmpty()) {
        return false;
    }
    if (isSystemDefault) {
        return true;
    }
    if (!windowBackground.isValid() || !editorBackground.isValid() ||
        !textColor.isValid() || !selectionBackground.isValid() ||
        !selectedTextColor.isValid() || !caretColor.isValid() ||
        !statusBarBackground.isValid() || !statusBarTextColor.isValid()) {
        return false;
    }
    return true;
}

} // namespace YANP
