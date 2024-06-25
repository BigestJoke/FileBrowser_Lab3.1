#include "FolderSizeStrategy.h"

int calcDirSize(const QString& path) {
    int dirSize = 0;
    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    for (auto it = list.constBegin(); it != list.constEnd(); ++it) {
        const QFileInfo& fileInfo = *it;
        if (fileInfo.isDir()) {
            QString subDirPath = fileInfo.absoluteFilePath();
            dirSize += calcDirSize(subDirPath);
        } else {
            dirSize += fileInfo.size();
        }
    }
    return dirSize;
}

QMap<QString, int> FolderSizeStrategy::calculate(const QString& path) {
    QMap<QString, int> map;
    int rootDirSize = calcDirSize(path); // Размер корневой директории
    QFileInfo file(path);
    int folder_size = 0;

    if (file.isDir()) {
        QDir dir(path);
        QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

        for (auto it = fileList.constBegin(); it != fileList.constEnd(); ++it) {
            const QFileInfo& fileInfo = *it;
            folder_size += fileInfo.size();
        }

        QString currentDirName = dir.dirName();
        map.insert(currentDirName, folder_size);

        QStringList subDirList = dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs);
        for (auto it = subDirList.constBegin(); it != subDirList.constEnd(); ++it) {
            QString subDirName = *it;
            QString subDirPath = path + "/" + subDirName;
            int subDirSize = calcDirSize(subDirPath);
            map.insert(subDirName, subDirSize);
        }

        // Добавляем корневую директорию как 100% от ее собственного размера
        map.insert(dir.dirName(), rootDirSize);
    }
    return map;
}
