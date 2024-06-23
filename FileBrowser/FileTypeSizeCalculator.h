#ifndef FILETYPESIZECALCULATOR_H
#define FILETYPESIZECALCULATOR_H

#include "ISizeCalculator.h"

class FileTypeSizeCalculator : public ISizeCalculator {
public:
    void calculate(const QDir &dir, QTextStream &out) override;

private:
    qint64 getTotalSize(const QDir &dir, QMap<QString, qint64> &fileTypes);
    void printFileTypeSizes(const QMap<QString, qint64> &fileTypes, qint64 totalSize, QTextStream &out);
};

#endif // FILETYPESIZECALCULATOR_H
