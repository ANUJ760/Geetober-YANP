#pragma once

#include "Theme.h"
#include <QObject>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QStatusBar>
#include <QSettings>

namespace YANP {

class ThemeManager : public QObject {
    Q_OBJECT
public:
    explicit ThemeManager(QObject* parent = nullptr);

    Theme currentTheme() const;
    bool setTheme(const QString& themeId);
    void applyTheme(const Theme& theme, QMainWindow* window, QPlainTextEdit* editor, QStatusBar* statusBar);

    void loadSavedTheme();
    void saveCurrentTheme();

signals:
    void themeChanged(const Theme& theme);

private:
    Theme m_currentTheme;
};

} // namespace YANP
