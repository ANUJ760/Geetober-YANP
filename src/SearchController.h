#pragma once

#include <QObject>
#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include "EditorWidget.h"

namespace YANP {

class FindDialog : public QDialog {
    Q_OBJECT
public:
    explicit FindDialog(QWidget* parent = nullptr);

    QString searchText() const;
    void setSearchText(const QString& text);
    bool matchCase() const;
    bool searchBackward() const;
    bool wrapAround() const;

signals:
    void findRequested(const QString& text, bool matchCase, bool backward, bool wrap);

private slots:
    void onFindClicked();
    void updateButtons();

private:
    QLineEdit* m_findEdit = nullptr;
    QCheckBox* m_caseCheckBox = nullptr;
    QCheckBox* m_wrapCheckBox = nullptr;
    QRadioButton* m_downRadio = nullptr;
    QRadioButton* m_upRadio = nullptr;
    QPushButton* m_findButton = nullptr;
    QPushButton* m_cancelButton = nullptr;
};

class ReplaceDialog : public QDialog {
    Q_OBJECT
public:
    explicit ReplaceDialog(QWidget* parent = nullptr);

    QString searchText() const;
    void setSearchText(const QString& text);
    QString replaceText() const;
    bool matchCase() const;
    bool wrapAround() const;

signals:
    void findRequested(const QString& text, bool matchCase, bool backward, bool wrap);
    void replaceRequested(const QString& findText, const QString& replaceText, bool matchCase);
    void replaceAllRequested(const QString& findText, const QString& replaceText, bool matchCase);

private slots:
    void onFindClicked();
    void onReplaceClicked();
    void onReplaceAllClicked();
    void updateButtons();

private:
    QLineEdit* m_findEdit = nullptr;
    QLineEdit* m_replaceEdit = nullptr;
    QCheckBox* m_caseCheckBox = nullptr;
    QCheckBox* m_wrapCheckBox = nullptr;
    QPushButton* m_findButton = nullptr;
    QPushButton* m_replaceButton = nullptr;
    QPushButton* m_replaceAllButton = nullptr;
    QPushButton* m_cancelButton = nullptr;
};

class GoToDialog : public QDialog {
    Q_OBJECT
public:
    explicit GoToDialog(int maxLine, int currentLine, QWidget* parent = nullptr);

    int targetLine() const;

private slots:
    void onGoToClicked();

private:
    int m_maxLine = 1;
    int m_targetLine = 1;
    QLineEdit* m_lineInput = nullptr;
    QLabel* m_errorLabel = nullptr;
};

class SearchController : public QObject {
    Q_OBJECT
public:
    explicit SearchController(EditorWidget* editor, QWidget* parentWindow = nullptr);

    void showFindDialog();
    void showReplaceDialog();
    void showGoToDialog();
    void findNext(); // Uses last find query or selected text

    // Programmatic search API
    bool find(const QString& query, bool matchCase, bool backward, bool wrap = true);
    bool replace(const QString& query, const QString& replacement, bool matchCase);
    int replaceAll(const QString& query, const QString& replacement, bool matchCase);
    bool goToLine(int line);

    QString lastSearchText() const;
    bool lastMatchCase() const;

private:
    EditorWidget* m_editor = nullptr;
    QWidget* m_parentWindow = nullptr;
    FindDialog* m_findDialog = nullptr;
    ReplaceDialog* m_replaceDialog = nullptr;

    QString m_lastSearchText;
    bool m_lastMatchCase = false;
    bool m_lastSearchBackward = false;
    bool m_lastWrapAround = true;
};

} // namespace YANP
