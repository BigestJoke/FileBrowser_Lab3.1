#include "FileTypeSizeStrategy.h"

QMap<QString, int> FileTypeSizeStrategy::calculate(const QString& path) {
    QMap<QString, int> map;
    QFileInfo file(path);

    if (file.isDir()) {
        QDir dir(path);
        QFileInfoList filelist = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

        for (const QFileInfo& fileInfo : filelist) {
            QString type = fileInfo.suffix();
            int file_size = fileInfo.size();
            map[type] += file_size;
        }

        QStringList subDirList = dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs);
        for (const QString& subDirName : subDirList) {
            QString subDirPath = path + "/" + subDirName;
            QMap<QString, int> subDirMap = this->calculate(subDirPath);
            for (auto it = subDirMap.begin(); it != subDirMap.end(); ++it) {
                map[it.key()] += it.value();
            }
        }
    }
    return map;
}
