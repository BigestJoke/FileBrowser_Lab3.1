#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QVector>
#include <QPair>

qint64 getTotalSize(const QDir &dir, QVector<QPair<QString, qint64>> &fileSizes) {
    qint64 totalSize = 0;
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::AllDirs);

    foreach (QFileInfo fileInfo, list) {
        if (fileInfo.isDir()) {
            totalSize += getTotalSize(QDir(fileInfo.absoluteFilePath()), fileSizes);
        } else {
            qint64 fileSize = fileInfo.size();
            totalSize += fileSize;
            fileSizes.append(qMakePair(fileInfo.absoluteFilePath(), fileSize));
        }
    }

    return totalSize;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QTextStream out(stdout);
    QTextStream in(stdin);

    out << "Enter directory path: ";
    out.flush();
    QString dirPath = in.readLine();

    QDir dir(dirPath);
    if (!dir.exists()) {
        out << "Directory does not exist!" << Qt::endl;
        return 1;
    }

    QVector<QPair<QString, qint64>> fileSizes;
    qint64 totalSize = getTotalSize(dir, fileSizes);

    if (totalSize == 0) {
        out << "No files found in the directory!" << Qt::endl;
        return 1;
    }

    out << "File sizes as a percentage of the total size:" << Qt::endl;
    for (const auto &fileSizePair : fileSizes) {
        QString filePath = fileSizePair.first;
        qint64 fileSize = fileSizePair.second;
        double percentage = (double(fileSize) / totalSize) * 100.0;
        out << filePath << ": " << percentage << "%" << Qt::endl;
    }

    return a.exec();
}
