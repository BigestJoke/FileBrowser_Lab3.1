#include "FileSizeCalculator.h"
#include <QFileInfo>
#include <QDirIterator>

// Метод для получения общего размера файлов в директории и заполнения вектора с размерами файлов.
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

// Метод для вывода размеров файлов в процентах от общего размера.
void FileSizeCalculator::printFileSizes(const QVector<QPair<QString, qint64>> &fileSizes, qint64 totalSize, QTextStream &out) {
    out << "File sizes as a percentage of the total size:" << Qt::endl;
    for (const auto &fileSizePair : fileSizes) {
        QString filePath = fileSizePair.first;
        qint64 fileSize = fileSizePair.second;
        double percentage = (double(fileSize) / totalSize) * 100.0;
        if (percentage < 0.01 && fileSize > 0) {
            out << filePath << ": < 0.01%" << Qt::endl;
        } else {
            out << filePath << ": " << QString::number(percentage, 'f', 2) << "%" << Qt::endl;
        }
    }
}

// Реализация метода calculate для подсчета размеров файлов.
void FileSizeCalculator::calculate(const QDir &dir, QTextStream &out) {
    try {
        QVector<QPair<QString, qint64>> fileSizes;
        qint64 totalSize = getTotalSize(dir, fileSizes);

        if (totalSize == 0) {
            out << "No files found in the directory!" << Qt::endl;
            return;
        }

        printFileSizes(fileSizes, totalSize, out);
    } catch (const std::exception &e) {
        out << "An error occurred: " << e.what() << Qt::endl;
    } catch (...) {
        out << "An unknown error occurred." << Qt::endl;
    }
}
