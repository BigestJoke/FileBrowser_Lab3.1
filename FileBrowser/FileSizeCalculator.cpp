#include "FileSizeCalculator.h"

qint64 FileSizeCalculator::getTotalSize(const QDir &dir, QVector<QPair<QString, qint64>> &fileSizes) {
    qint64 totalSize = 0;
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    foreach (QFileInfo fileInfo, list) {
        if (fileInfo.isDir()) {
            QString dirPath = fileInfo.absoluteFilePath();
            qint64 dirSize = 0;
            QDir subDir(dirPath);
            QFileInfoList subList = subDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
            foreach (QFileInfo subFileInfo, subList) {
                dirSize += subFileInfo.size();
            }
            totalSize += dirSize;
            fileSizes.append(qMakePair(dirPath, dirSize));
        } else {
            qint64 fileSize = fileInfo.size();
            totalSize += fileSize;
            fileSizes.append(qMakePair(fileInfo.absoluteFilePath(), fileSize));
        }
    }

    return totalSize;
}

void FileSizeCalculator::printFileSizes(const QVector<QPair<QString, qint64>> &fileSizes, qint64 totalSize, QTextStream &out) {
    out << "File sizes as a percentage of the total size:" << Qt::endl;
    for (const auto &fileSizePair : fileSizes) {
        QString filePath = fileSizePair.first;
        qint64 fileSize = fileSizePair.second;
        double percentage = (double(fileSize) / totalSize) * 100.0;
        out << filePath << ": " << percentage << "%" << Qt::endl;
    }
}

void FileSizeCalculator::calculate(const QDir &dir, QTextStream &out) {
    QVector<QPair<QString, qint64>> fileSizes;
    qint64 totalSize = getTotalSize(dir, fileSizes);

    if (totalSize == 0) {
        out << "No files found in the directory!" << Qt::endl;
        return;
    }

    printFileSizes(fileSizes, totalSize, out);
}
