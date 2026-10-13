#include <QTest>
#include <QTemporaryDir>
#include <QFile>
#include "FileManager.h"

using namespace YANP;

class TestFileManager : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void testInitialState();
    void testOpenNonExistentFile();
    void testSaveAndOpenUtf8();
    void testUtf8BomHandling();
    void testUtf16LeHandling();
    void testLineEndingDetectionAndPreservation();
    void testModifiedStateAndTitle();

private:
    std::unique_ptr<QTemporaryDir> m_tempDir;
};

void TestFileManager::initTestCase() {
    m_tempDir = std::make_unique<QTemporaryDir>();
    QVERIFY(m_tempDir->isValid());
}

void TestFileManager::testInitialState() {
    FileManager fm;
    QCOMPARE(fm.filePath(), QString());
    QCOMPARE(fm.fileName(), QStringLiteral("Untitled"));
    QCOMPARE(fm.isModified(), false);
    QCOMPARE(fm.windowTitle(), QStringLiteral("Untitled - YANP"));
}

void TestFileManager::testOpenNonExistentFile() {
    FileManager fm;
    FileResult res = fm.openFile(QStringLiteral("/path/does/not/exist/yanp_test.txt"));
    QVERIFY(!res.success);
    QVERIFY(!res.errorMessage.isEmpty());
    QCOMPARE(fm.filePath(), QString());
}

void TestFileManager::testSaveAndOpenUtf8() {
    FileManager fm;
    QString filePath = m_tempDir->filePath(QStringLiteral("test_utf8.txt"));
    QString content = QStringLiteral("Hello World from YANP!\nSecond line with unicode: 🚀 — é à ü ñ");

    FileResult saveRes = fm.saveFile(filePath, content);
    QVERIFY(saveRes.success);
    QCOMPARE(fm.isModified(), false);
    QCOMPARE(fm.filePath(), filePath);
    QCOMPARE(fm.fileName(), QStringLiteral("test_utf8.txt"));

    FileManager fm2;
    FileResult openRes = fm2.openFile(filePath);
    QVERIFY(openRes.success);
    QCOMPARE(openRes.content, content);
    QCOMPARE(fm2.encoding(), FileEncoding::UTF8);
}

void TestFileManager::testUtf8BomHandling() {
    QString filePath = m_tempDir->filePath(QStringLiteral("test_bom.txt"));

    // Write file with UTF-8 BOM
    {
        QFile file(filePath);
        QVERIFY(file.open(QIODevice::WriteOnly));
        file.write("\xEF\xBB\xBF");
        file.write("BOM content text");
        file.close();
    }

    FileManager fm;
    FileResult openRes = fm.openFile(filePath);
    QVERIFY(openRes.success);
    QCOMPARE(openRes.content, QStringLiteral("BOM content text"));
    QCOMPARE(fm.encoding(), FileEncoding::UTF8_BOM);

    // Save and verify BOM is preserved
    FileResult saveRes = fm.saveFile(filePath, QStringLiteral("Updated BOM content"));
    QVERIFY(saveRes.success);

    QFile checkFile(filePath);
    QVERIFY(checkFile.open(QIODevice::ReadOnly));
    QByteArray data = checkFile.readAll();
    checkFile.close();

    QVERIFY(data.startsWith("\xEF\xBB\xBF"));
    QCOMPARE(data.mid(3), QByteArray("Updated BOM content"));
}

void TestFileManager::testUtf16LeHandling() {
    QString filePath = m_tempDir->filePath(QStringLiteral("test_utf16le.txt"));

    // Write UTF-16 LE file
    {
        QFile file(filePath);
        QVERIFY(file.open(QIODevice::WriteOnly));
        file.write("\xFF\xFE");
        // "Hi" in UTF-16LE: 'H'(0x48, 0x00), 'i'(0x69, 0x00)
        const char hi[] = {'H', 0, 'i', 0};
        file.write(hi, 4);
        file.close();
    }

    FileManager fm;
    FileResult openRes = fm.openFile(filePath);
    QVERIFY(openRes.success);
    QCOMPARE(openRes.content, QStringLiteral("Hi"));
    QCOMPARE(fm.encoding(), FileEncoding::UTF16_LE);
}

void TestFileManager::testLineEndingDetectionAndPreservation() {
    QString filePathCrlf = m_tempDir->filePath(QStringLiteral("test_crlf.txt"));
    {
        QFile file(filePathCrlf);
        QVERIFY(file.open(QIODevice::WriteOnly));
        file.write("Line1\r\nLine2\r\nLine3");
        file.close();
    }

    FileManager fm;
    FileResult openRes = fm.openFile(filePathCrlf);
    QVERIFY(openRes.success);
    QCOMPARE(fm.lineEnding(), LineEnding::CRLF);

    // Save with CRLF
    fm.saveFile(filePathCrlf, QStringLiteral("A\nB"));
    QFile checkFile(filePathCrlf);
    QVERIFY(checkFile.open(QIODevice::ReadOnly));
    QByteArray data = checkFile.readAll();
    checkFile.close();
    QCOMPARE(data, QByteArray("A\r\nB"));
}

void TestFileManager::testModifiedStateAndTitle() {
    FileManager fm;
    QCOMPARE(fm.windowTitle(), QStringLiteral("Untitled - YANP"));

    fm.setModified(true);
    QCOMPARE(fm.windowTitle(), QStringLiteral("*Untitled - YANP"));

    fm.setFilePath(QStringLiteral("/some/path/notes.txt"));
    QCOMPARE(fm.windowTitle(), QStringLiteral("*notes.txt - YANP"));

    fm.setModified(false);
    QCOMPARE(fm.windowTitle(), QStringLiteral("notes.txt - YANP"));
}

QTEST_MAIN(TestFileManager)
#include "test_filemanager.moc"
