#include "FileTypeSizeCalculator.h"

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

void FileTypeSizeCalculator::printFileTypeSizes(const QMap<QString, qint64> &fileTypes, qint64 totalSize, QTextStream &out) {
    out << "File type sizes as a percentage of the total size:" << Qt::endl;
    QMapIterator<QString, qint64> i(fileTypes);
    while (i.hasNext()) {
        i.next();
        QString fileType = i.key();
        qint64 fileSize = i.value();
        double percentage = (double(fileSize) / totalSize) * 100.0;
        out << fileType << ": " << percentage << "%" << Qt::endl;
    }
}

void FileTypeSizeCalculator::calculate(const QDir &dir, QTextStream &out) {
    QMap<QString, qint64> fileTypes;
    qint64 totalSize = getTotalSize(dir, fileTypes);

    if (totalSize == 0) {
        out << "No files found in the directory!" << Qt::endl;
        return;
    }

    printFileTypeSizes(fileTypes, totalSize, out);
}
