#include <QTest>
#include "themes/ThemeRegistry.h"
#include "themes/ThemeManager.h"

using namespace YANP;

class TestThemes : public QObject {
    Q_OBJECT

private slots:
    void init();
    void testBuiltInThemesRegistered();
    void testThemeValidity();
    void testDuplicateRegistrationRejected();
    void testInvalidThemeRejected();
    void testThemeLookupAndFallback();
    void testThemeManagerSwitching();
};

void TestThemes::init() {
    ThemeRegistry::instance().resetToDefaults();
}

void TestThemes::testBuiltInThemesRegistered() {
    auto themes = ThemeRegistry::instance().registeredThemes();
    QVERIFY(themes.size() >= 3);

    QVERIFY(ThemeRegistry::instance().hasTheme(QStringLiteral("system-default")));
    QVERIFY(ThemeRegistry::instance().hasTheme(QStringLiteral("classic-light")));
    QVERIFY(ThemeRegistry::instance().hasTheme(QStringLiteral("classic-dark")));
    QVERIFY(ThemeRegistry::instance().hasTheme(QStringLiteral("retro-green")));
    QVERIFY(ThemeRegistry::instance().hasTheme(QStringLiteral("amber-crt")));
    QVERIFY(ThemeRegistry::instance().hasTheme(QStringLiteral("solarized-dark")));
}

void TestThemes::testThemeValidity() {
    auto themes = ThemeRegistry::instance().registeredThemes();
    for (const auto& theme : themes) {
        QVERIFY2(theme.isValid(), qPrintable(QString("Theme '%1' failed validation").arg(theme.id)));
        QVERIFY(!theme.id.isEmpty());
        QVERIFY(!theme.name.isEmpty());

        if (!theme.isSystemDefault) {
            QVERIFY(theme.windowBackground.isValid());
            QVERIFY(theme.editorBackground.isValid());
            QVERIFY(theme.textColor.isValid());
            QVERIFY(theme.selectionBackground.isValid());
            QVERIFY(theme.selectedTextColor.isValid());
            QVERIFY(theme.statusBarBackground.isValid());
            QVERIFY(theme.statusBarTextColor.isValid());
            // Contrast sanity check: text color must not equal editor background
            QVERIFY(theme.textColor != theme.editorBackground);
            // Selection text must not equal selection background
            QVERIFY(theme.selectedTextColor != theme.selectionBackground);
        }
    }
}

void TestThemes::testDuplicateRegistrationRejected() {
    Theme dup;
    dup.id = QStringLiteral("classic-light");
    dup.name = QStringLiteral("Duplicate Classic Light");
    dup.isSystemDefault = false;
    dup.windowBackground = QColor(255, 255, 255);
    dup.editorBackground = QColor(255, 255, 255);
    dup.textColor = QColor(0, 0, 0);
    dup.selectionBackground = QColor(0, 0, 255);
    dup.selectedTextColor = QColor(255, 255, 255);
    dup.caretColor = QColor(0, 0, 0);
    dup.statusBarBackground = QColor(200, 200, 200);
    dup.statusBarTextColor = QColor(0, 0, 0);

    bool result = ThemeRegistry::instance().registerTheme(dup);
    QVERIFY(!result);
}

void TestThemes::testInvalidThemeRejected() {
    Theme invalid;
    invalid.id = ""; // Empty ID
    invalid.name = "Invalid";

    bool result = ThemeRegistry::instance().registerTheme(invalid);
    QVERIFY(!result);
}

void TestThemes::testThemeLookupAndFallback() {
    auto theme = ThemeRegistry::instance().getTheme(QStringLiteral("classic-dark"));
    QVERIFY(theme.has_value());
    QCOMPARE(theme->id, QStringLiteral("classic-dark"));

    auto nonExistent = ThemeRegistry::instance().getTheme(QStringLiteral("non-existent-theme"));
    QVERIFY(!nonExistent.has_value());

    Theme defaultTheme = ThemeRegistry::instance().defaultTheme();
    QCOMPARE(defaultTheme.id, QStringLiteral("system-default"));
}

void TestThemes::testThemeManagerSwitching() {
    ThemeManager tm;
    QVERIFY(tm.setTheme(QStringLiteral("classic-dark")));
    QCOMPARE(tm.currentTheme().id, QStringLiteral("classic-dark"));

    // Setting invalid theme ID should return false and not change current theme
    QVERIFY(!tm.setTheme(QStringLiteral("unknown-theme")));
    QCOMPARE(tm.currentTheme().id, QStringLiteral("classic-dark"));

    // Switch back to system default
    QVERIFY(tm.setTheme(QStringLiteral("system-default")));
    QCOMPARE(tm.currentTheme().id, QStringLiteral("system-default"));
}

QTEST_MAIN(TestThemes)
#include "test_themes.moc"
