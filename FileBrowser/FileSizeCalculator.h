#ifndef FILESIZECALCULATOR_H
#define FILESIZECALCULATOR_H

#include "ISizeCalculator.h"

// Класс FileSizeCalculator реализует стратегию подсчета размеров по файлам.
class FileSizeCalculator : public ISizeCalculator {
public:
    // Реализация метода calculate для подсчета размеров файлов.
    void calculate(const QDir &dir, QTextStream &out) override;

private:
    // Метод для получения общего размера файлов в директории и заполнения вектора с размерами файлов.
    qint64 getTotalSize(const QDir &dir, QVector<QPair<QString, qint64>> &fileSizes);

    // Метод для вывода размеров файлов в процентах от общего размера.
    void printFileSizes(const QVector<QPair<QString, qint64>> &fileSizes, qint64 totalSize, QTextStream &out);
};

#endif // FILESIZECALCULATOR_H
