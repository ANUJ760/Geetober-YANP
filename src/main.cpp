#include "MainWindow.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QFileInfo>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName(QStringLiteral("Geektober"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("geektober.yanp"));
    QCoreApplication::setApplicationName(QStringLiteral("YANP"));
    QCoreApplication::setApplicationVersion(QStringLiteral("1.0.0"));

    QCommandLineParser parser;
    parser.setApplicationDescription(
        QCoreApplication::translate("main", "YANP - Yet Another Notepad. A lightweight, classic desktop text editor.")
    );
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument(
        QStringLiteral("[file]"),
        QCoreApplication::translate("main", "Text file to open.")
    );

    parser.process(app);

    YANP::MainWindow mainWindow;
    mainWindow.show();

    const QStringList positionalArgs = parser.positionalArguments();
    if (!positionalArgs.isEmpty()) {
        const QString filePath = positionalArgs.first();
        if (QFileInfo::exists(filePath)) {
            mainWindow.openFileFromPath(filePath);
        }
    }

    return app.exec();
}
