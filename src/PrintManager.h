#pragma once

#include <QObject>
#include <QPrinter>
#include <QTextDocument>

namespace YANP {

class PrintManager : public QObject {
    Q_OBJECT
public:
    explicit PrintManager(QObject* parent = nullptr);

    bool pageSetup(QWidget* parentWidget);
    bool printDocument(QWidget* parentWidget, QTextDocument* document, const QString& docTitle);

private:
    QPrinter m_printer;
};

} // namespace YANP
