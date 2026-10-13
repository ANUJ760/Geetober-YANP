#pragma once

#include <QString>
#include <QColor>

namespace YANP {

struct Theme {
    QString id;
    QString name;
    bool isSystemDefault = false;

    QColor windowBackground;
    QColor editorBackground;
    QColor textColor;
    QColor selectionBackground;
    QColor selectedTextColor;
    QColor caretColor;
    QColor statusBarBackground;
    QColor statusBarTextColor;
    QColor borderColor;

    QString defaultFontFamily;
    int defaultFontSize = 11;

    bool isValid() const;
};

} // namespace YANP
