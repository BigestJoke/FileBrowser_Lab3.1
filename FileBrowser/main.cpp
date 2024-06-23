#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QVector>
#include <QPair>
#include <QMap>
#include <QStringList>

// Функция для подсчета размеров файлов и директорий
qint64 getTotalSize(const QDir &dir, QVector<QPair<QString, qint64>> &fileSizes, QMap<QString, qint64> &fileTypes) {
    qint64 totalSize = 0;
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    foreach (QFileInfo fileInfo, list) {
        if (fileInfo.isDir()) {
            // Если это директория, добавляем ее размер как 0 и название
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
            // Если это файл, добавляем его размер
            qint64 fileSize = fileInfo.size();
            totalSize += fileSize;
            fileSizes.append(qMakePair(fileInfo.absoluteFilePath(), fileSize));

            // Подсчет размеров по типам файлов
            QString suffix = fileInfo.suffix().toLower();
            if (suffix.isEmpty()) {
                suffix = "no_extension";
            }
            fileTypes[suffix] += fileSize;
        }
    }

    return totalSize;
}

// Функция для вывода размеров по файлам
void printFileSizes(const QVector<QPair<QString, qint64>> &fileSizes, qint64 totalSize, QTextStream &out) {
    out << "File sizes as a percentage of the total size:" << Qt::endl;
    for (const auto &fileSizePair : fileSizes) {
        QString filePath = fileSizePair.first;
        qint64 fileSize = fileSizePair.second;
        double percentage = (double(fileSize) / totalSize) * 100.0;
        out << filePath << ": " << percentage << "%" << Qt::endl;
    }
}

// Функция для вывода размеров по типам файлов
void printFileTypeSizes(const QMap<QString, qint64> &fileTypes, qint64 totalSize, QTextStream &out) {
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

    out << "Choose calculation method (1 - by files, 2 - by file types): ";
    out.flush();
    QString methodChoice = in.readLine().trimmed();

    QVector<QPair<QString, qint64>> fileSizes;
    QMap<QString, qint64> fileTypes;
    qint64 totalSize = getTotalSize(dir, fileSizes, fileTypes);

    if (totalSize == 0) {
        out << "No files found in the directory!" << Qt::endl;
        return 1;
    }

    if (methodChoice == "1") {
        printFileSizes(fileSizes, totalSize, out);
    } else if (methodChoice == "2") {
        printFileTypeSizes(fileTypes, totalSize, out);
    } else {
        out << "Invalid choice!" << Qt::endl;
        return 1;
    }

    return a.exec();
}
