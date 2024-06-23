#ifndef ISIZECALCULATOR_H
#define ISIZECALCULATOR_H

#include <QDir>
#include <QTextStream>
#include <QMap>
#include <QVector>
#include <QPair>

class ISizeCalculator {
public:
    virtual ~ISizeCalculator() {}
    virtual void calculate(const QDir &dir, QTextStream &out) = 0;
};

#endif // ISIZECALCULATOR_H
