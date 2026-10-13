#include "PrintManager.h"
#include <QPrintDialog>
#include <QPageSetupDialog>

namespace YANP {

PrintManager::PrintManager(QObject* parent)
    : QObject(parent), m_printer(QPrinter::HighResolution)
{
}

bool PrintManager::pageSetup(QWidget* parentWidget) {
    QPageSetupDialog dialog(&m_printer, parentWidget);
    return dialog.exec() == QDialog::Accepted;
}

bool PrintManager::printDocument(QWidget* parentWidget, QTextDocument* document, const QString& docTitle) {
    if (!document) {
        return false;
    }

    m_printer.setDocName(docTitle);
    QPrintDialog dialog(&m_printer, parentWidget);
    dialog.setWindowTitle(tr("Print Document"));

    if (dialog.exec() != QDialog::Accepted) {
        return false;
    }

    document->print(&m_printer);
    return true;
}

} // namespace YANP
