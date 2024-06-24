#include "FileTypeSizeCalculator.h"

// Метод для получения общего размера файлов по типам в директории и заполнения карты с размерами файлов.
qint64 FileTypeSizeCalculator::getTotalSize(const QDir &dir, QMap<QString, qint64> &fileTypes) {
    qint64 totalSize = 0;
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

    foreach (QFileInfo fileInfo, list) {
        qint64 fileSize = fileInfo.size();
        totalSize += fileSize;

        QString suffix = fileInfo.suffix().toLower();
        if (suffix.isEmpty()) {
            suffix = "no_extension";
        }
        fileTypes[suffix] += fileSize;
    }

    return totalSize;
}

// Метод для вывода размеров типов файлов в процентах от общего размера.
void FileTypeSizeCalculator::printFileTypeSizes(const QMap<QString, qint64> &fileTypes, qint64 totalSize, QTextStream &out) {
    out << "File type sizes as a percentage of the total size:" << Qt::endl;
    QMapIterator<QString, qint64> i(fileTypes);
    while (i.hasNext()) {
        i.next();
        QString fileType = i.key();
        qint64 fileSize = i.value();
        double percentage = (double(fileSize) / totalSize) * 100.0;
        if (percentage < 0.01 && fileSize > 0) {
            out << fileType << ": < 0.01%" << Qt::endl;
        } else {
            out << fileType << ": " << QString::number(percentage, 'f', 2) << "%" << Qt::endl;
        }
    }
}

// Реализация метода calculate для подсчета размеров по типам файлов.
void FileTypeSizeCalculator::calculate(const QDir &dir, QTextStream &out) {
    try {
        QMap<QString, qint64> fileTypes;
        qint64 totalSize = getTotalSize(dir, fileTypes);

        if (totalSize == 0) {
            out << "No files found in the directory!" << Qt::endl;
            return;
        }

        printFileTypeSizes(fileTypes, totalSize, out);
    } catch (const std::exception &e) {
        out << "An error occurred: " << e.what() << Qt::endl;
    } catch (...) {
        out << "An unknown error occurred." << Qt::endl;
    }
}
