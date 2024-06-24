#ifndef FILETYPESIZECALCULATOR_H
#define FILETYPESIZECALCULATOR_H

#include "ISizeCalculator.h"

// Класс FileTypeSizeCalculator реализует стратегию подсчета размеров по типам файлов.
class FileTypeSizeCalculator : public ISizeCalculator {
public:
    // Реализация метода calculate для подсчета размеров по типам файлов.
    void calculate(const QDir &dir, QTextStream &out) override;

private:
    // Метод для получения общего размера файлов по типам в директории и заполнения карты с размерами файлов.
    qint64 getTotalSize(const QDir &dir, QMap<QString, qint64> &fileTypes);

    // Метод для вывода размеров типов файлов в процентах от общего размера.
    void printFileTypeSizes(const QMap<QString, qint64> &fileTypes, qint64 totalSize, QTextStream &out);
};

#endif // FILETYPESIZECALCULATOR_H
