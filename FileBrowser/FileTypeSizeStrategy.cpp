#include "FileTypeSizeStrategy.h"

QMap<QString, int> FileTypeSizeStrategy::calculate(const QString& path) {
    QMap<QString, int> map;
    QFileInfo file(path);

    if (file.isDir()) {
        QDir dir(path);  // Создание объекта QDir для работы с указанной директорией
        QFileInfoList filelist = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);  // Получение списка файлов в директории

        for (const QFileInfo& fileInfo : filelist) {  // Итерация по списку файлов в директории
            QString type = fileInfo.suffix();
            int file_size = fileInfo.size();
            map[type] += file_size;  // Добавление размера файла к существующему значению типа файла в QMap
        }

        QStringList subDirList = dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs);  // Получение списка поддиректорий
        for (const QString& subDirName : subDirList) {
            QString subDirPath = path + "/" + subDirName;
            QMap<QString, int> subDirMap = this->calculate(subDirPath);  // Рекурсивный вызов calculate для поддиректории
            for (auto it = subDirMap.begin(); it != subDirMap.end(); ++it) {  // Итерация по QMap поддиректории
                map[it.key()] += it.value();  // Добавление размеров поддиректорий к соответствующим типам файлов в текущем QMap
            }
        }
    }

    return map;
}
