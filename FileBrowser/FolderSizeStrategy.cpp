#include "FolderSizeStrategy.h"

int calcDirSize(const QString& path) {
    int dirSize = 0;
    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot); // Получение списка файлов и директорий в указанной директории

    // Проход по всем элементам в списке файлов и директорий
    for (auto it = list.constBegin(); it != list.constEnd(); ++it) {
        const QFileInfo& fileInfo = *it; // Получение ссылки на текущий элемент списка
        if (fileInfo.isDir()) {
            QString subDirPath = fileInfo.absoluteFilePath(); // Получение абсолютного пути к поддиректории
            dirSize += calcDirSize(subDirPath); // Рекурсивный вызов функции для вычисления размера поддиректории
        } else { // Если текущий элемент является файлом
            dirSize += fileInfo.size();
        }
    }
    return dirSize;
}

QMap<QString, int> FolderSizeStrategy::calculate(const QString& path) {
    QMap<QString, int> map; //
    int rootDirSize = calcDirSize(path); // Вычисление размера корневой директории
    QFileInfo file(path); // Получение информации о корневой директории
    int folder_size = 0;

    if (file.isDir()) {
        QDir dir(path); // Создание объекта QDir для работы с корневой директорией
        QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks); // Получение списка файлов в корневой директории

        // Проход по списку файлов в текущей директории
        for (auto it = fileList.constBegin(); it != fileList.constEnd(); ++it) {
            const QFileInfo& fileInfo = *it; // Получение ссылки на текущий элемент списка
            folder_size += fileInfo.size(); // Добавление размера файла к общему размеру текущей директории
        }

        QString currentDirName = dir.dirName();
        map.insert(currentDirName, folder_size); // Добавление записи в QMap: имя директории - ее размер

        QStringList subDirList = dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs); // Получение списка поддиректорий

        // Проход по списку поддиректорий текущей директории
        for (auto it = subDirList.constBegin(); it != subDirList.constEnd(); ++it) {
            QString subDirName = *it; // Получение имени поддиректории
            QString subDirPath = path + "/" + subDirName; // Формирование абсолютного пути к поддиректории
            int subDirSize = calcDirSize(subDirPath); // Вычисление размера поддиректории
            map.insert(subDirName, subDirSize); // Добавление записи в QMap: имя поддиректории - ее размер
        }

        map.insert(dir.dirName(), rootDirSize);
    }

    return map;
}
