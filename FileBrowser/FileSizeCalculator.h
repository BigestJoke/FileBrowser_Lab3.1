#ifndef FILESIZECALCULATOR_H
#define FILESIZECALCULATOR_H

#include "ISizeCalculator.h"

class FileSizeCalculator : public ISizeCalculator {
public:
    void calculate(const QDir &dir, QTextStream &out) override;

private:
    qint64 getTotalSize(const QDir &dir, QVector<QPair<QString, qint64>> &fileSizes);
    void printFileSizes(const QVector<QPair<QString, qint64>> &fileSizes, qint64 totalSize, QTextStream &out);
};

#endif // FILESIZECALCULATOR_H
