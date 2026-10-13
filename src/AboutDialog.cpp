#include "AboutDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

namespace YANP {

AboutDialog::AboutDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(tr("About YANP"));
    setFixedSize(460, 320);

    auto* mainLayout = new QVBoxLayout(this);

    auto* titleLabel = new QLabel(QStringLiteral("<h2>YANP &mdash; Yet Another Notepad</h2>"), this);
    titleLabel->setAlignment(Qt::AlignCenter);

    auto* versionLabel = new QLabel(tr("Version 1.0.0 (C++20 &amp; Qt %1)").arg(QT_VERSION_STR), this);
    versionLabel->setAlignment(Qt::AlignCenter);

    auto* infoLabel = new QLabel(
        tr("<p><b>YANP</b> is a lightweight, classic desktop text editor designed with "
           "simplicity, responsiveness, and cross-platform reliability.</p>"
           "<p>Inspired by <b>TinyRetroPad</b> by Dave Plummer (Plummer's Software LLC).<br>"
           "Reference project: <a href=\"https://github.com/plummersSoftwareLLC/TinyRetroPad\">"
           "https://github.com/plummersSoftwareLLC/TinyRetroPad</a></p>"
           "<p>Features maintainer-curated themes, standard Notepad keybindings, "
           "native dialogs, and reliable text handling.</p>"
           "<p><small>Licensed under the MIT License.</small></p>"),
        this
    );
    infoLabel->setWordWrap(true);
    infoLabel->setOpenExternalLinks(true);

    auto* buttonLayout = new QHBoxLayout();
    auto* okButton = new QPushButton(tr("OK"), this);
    okButton->setDefault(true);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(versionLabel);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(infoLabel);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
}

} // namespace YANP
