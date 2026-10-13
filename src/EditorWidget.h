#pragma once

#include <QPlainTextEdit>
#include <QDragEnterEvent>
#include <QDropEvent>

namespace YANP {

class EditorWidget : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit EditorWidget(QWidget* parent = nullptr);

    void setWordWrapEnabled(bool enabled);
    bool isWordWrapEnabled() const;

    void insertDateTime();
    void deleteSelection();

    int currentLine() const;
    int currentColumn() const;

signals:
    void cursorCoordinatesChanged(int line, int column);
    void fileDropped(const QString& filePath);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private slots:
    void onCursorPositionChanged();
};

} // namespace YANP
