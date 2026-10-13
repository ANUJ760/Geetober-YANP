#include "FileManager.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QStringDecoder>
#include <QStringEncoder>
#include <QSaveFile>

namespace YANP {

FileManager::FileManager(QObject* parent)
    : QObject(parent)
{
#if defined(Q_OS_WIN)
    m_lineEnding = LineEnding::CRLF;
#else
    m_lineEnding = LineEnding::LF;
#endif
}

void FileManager::reset() {
    m_filePath.clear();
    m_isModified = false;
    m_encoding = FileEncoding::UTF8;
#if defined(Q_OS_WIN)
    m_lineEnding = LineEnding::CRLF;
#else
    m_lineEnding = LineEnding::LF;
#endif
    emit modifiedChanged(false);
    emit fileChanged(QString());
}

FileResult FileManager::openFile(const QString& filePath) {
    FileResult result;
    QFile file(filePath);

    if (!file.exists()) {
        result.success = false;
        result.errorMessage = tr("File does not exist: %1").arg(filePath);
        return result;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        result.success = false;
        result.errorMessage = tr("Cannot open file for reading: %1\nError: %2")
            .arg(filePath, file.errorString());
        return result;
    }

    QByteArray rawData = file.readAll();
    file.close();

    // Detect BOM and encoding
    FileEncoding detectedEncoding = FileEncoding::UTF8;
    QString decodedContent;

    if (rawData.size() >= 3 &&
        static_cast<unsigned char>(rawData[0]) == 0xEF &&
        static_cast<unsigned char>(rawData[1]) == 0xBB &&
        static_cast<unsigned char>(rawData[2]) == 0xBF) {
        detectedEncoding = FileEncoding::UTF8_BOM;
        decodedContent = QString::fromUtf8(rawData.constData() + 3, rawData.size() - 3);
    } else if (rawData.size() >= 2 &&
               static_cast<unsigned char>(rawData[0]) == 0xFF &&
               static_cast<unsigned char>(rawData[1]) == 0xFE) {
        detectedEncoding = FileEncoding::UTF16_LE;
        auto decoder = QStringDecoder(QStringDecoder::Utf16LE);
        decodedContent = decoder(rawData.mid(2));
    } else if (rawData.size() >= 2 &&
               static_cast<unsigned char>(rawData[0]) == 0xFE &&
               static_cast<unsigned char>(rawData[1]) == 0xFF) {
        detectedEncoding = FileEncoding::UTF16_BE;
        auto decoder = QStringDecoder(QStringDecoder::Utf16BE);
        decodedContent = decoder(rawData.mid(2));
    } else {
        // Try UTF-8 first
        auto decoder = QStringDecoder(QStringDecoder::Utf8, QStringDecoder::Flag::Stateless);
        decodedContent = decoder(rawData);
        if (decoder.hasError()) {
            // Fallback to local 8-bit
            detectedEncoding = FileEncoding::SystemLocale;
            decodedContent = QString::fromLocal8Bit(rawData);
        } else {
            detectedEncoding = FileEncoding::UTF8;
        }
    }

    // Detect line ending from raw bytes or content
    if (rawData.contains("\r\n")) {
        m_lineEnding = LineEnding::CRLF;
    } else if (rawData.contains("\n")) {
        m_lineEnding = LineEnding::LF;
    }

    m_encoding = detectedEncoding;
    m_filePath = QFileInfo(filePath).absoluteFilePath();
    m_isModified = false;

    result.success = true;
    result.content = decodedContent;

    emit modifiedChanged(false);
    emit fileChanged(m_filePath);

    return result;
}

FileResult FileManager::saveFile(const QString& filePath, const QString& content) {
    FileResult result;

    // Use QSaveFile for safe atomic writing (does not overwrite/corrupt original on error)
    QSaveFile saveFile(filePath);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        result.success = false;
        result.errorMessage = tr("Cannot open file for writing: %1\nError: %2")
            .arg(filePath, saveFile.errorString());
        return result;
    }

    // Normalize newlines based on line ending setting
    QString normalizedContent = content;
    normalizedContent.replace(QStringLiteral("\r\n"), QStringLiteral("\n"));
    normalizedContent.replace(QStringLiteral("\r"), QStringLiteral("\n"));

    if (m_lineEnding == LineEnding::CRLF) {
        normalizedContent.replace(QStringLiteral("\n"), QStringLiteral("\r\n"));
    }

    QByteArray encodedData;
    switch (m_encoding) {
    case FileEncoding::UTF8_BOM: {
        encodedData.append("\xEF\xBB\xBF");
        encodedData.append(normalizedContent.toUtf8());
        break;
    }
    case FileEncoding::UTF16_LE: {
        encodedData.append("\xFF\xFE");
        auto encoder = QStringEncoder(QStringEncoder::Utf16LE);
        encodedData.append(encoder(normalizedContent));
        break;
    }
    case FileEncoding::UTF16_BE: {
        encodedData.append("\xFE\xFF");
        auto encoder = QStringEncoder(QStringEncoder::Utf16BE);
        encodedData.append(encoder(normalizedContent));
        break;
    }
    case FileEncoding::SystemLocale: {
        encodedData.append(normalizedContent.toLocal8Bit());
        break;
    }
    case FileEncoding::UTF8:
    default: {
        encodedData.append(normalizedContent.toUtf8());
        break;
    }
    }

    qint64 bytesWritten = saveFile.write(encodedData);
    if (bytesWritten != encodedData.size()) {
        saveFile.cancelWriting();
        result.success = false;
        result.errorMessage = tr("Failed to write all data to file: %1").arg(filePath);
        return result;
    }

    if (!saveFile.commit()) {
        result.success = false;
        result.errorMessage = tr("Failed to finalize file: %1\nError: %2")
            .arg(filePath, saveFile.errorString());
        return result;
    }

    m_filePath = QFileInfo(filePath).absoluteFilePath();
    m_isModified = false;

    result.success = true;
    result.content = content;

    emit modifiedChanged(false);
    emit fileChanged(m_filePath);

    return result;
}

QString FileManager::filePath() const {
    return m_filePath;
}

void FileManager::setFilePath(const QString& path) {
    m_filePath = path;
    emit fileChanged(m_filePath);
}

bool FileManager::isModified() const {
    return m_isModified;
}

void FileManager::setModified(bool modified) {
    if (m_isModified != modified) {
        m_isModified = modified;
        emit modifiedChanged(m_isModified);
    }
}

QString FileManager::fileName() const {
    if (m_filePath.isEmpty()) {
        return tr("Untitled");
    }
    return QFileInfo(m_filePath).fileName();
}

QString FileManager::windowTitle() const {
    QString title = fileName();
    if (m_isModified) {
        title.prepend(QStringLiteral("*"));
    }
    title.append(QStringLiteral(" - YANP"));
    return title;
}

FileEncoding FileManager::encoding() const {
    return m_encoding;
}

QString FileManager::encodingName() const {
    switch (m_encoding) {
    case FileEncoding::UTF8:
        return QStringLiteral("UTF-8");
    case FileEncoding::UTF8_BOM:
        return QStringLiteral("UTF-8 with BOM");
    case FileEncoding::UTF16_LE:
        return QStringLiteral("UTF-16 LE");
    case FileEncoding::UTF16_BE:
        return QStringLiteral("UTF-16 BE");
    case FileEncoding::SystemLocale:
        return QStringLiteral("System Locale");
    }
    return QStringLiteral("UTF-8");
}

void FileManager::setEncoding(FileEncoding enc) {
    m_encoding = enc;
}

LineEnding FileManager::lineEnding() const {
    return m_lineEnding;
}

QString FileManager::lineEndingName() const {
    switch (m_lineEnding) {
    case LineEnding::CRLF:
        return QStringLiteral("Windows (CRLF)");
    case LineEnding::LF:
        return QStringLiteral("Unix (LF)");
    }
    return QStringLiteral("Unix (LF)");
}

void FileManager::setLineEnding(LineEnding le) {
    m_lineEnding = le;
}

} // namespace YANP
