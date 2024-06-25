#ifndef ISIZECALCULATOR_H
#define ISIZECALCULATOR_H

#include <QDir>
#include <QTextStream>
#include <QMap>
#include <QVector>
#include <QPair>

// Интерфейс для стратегий подсчета размеров файлов.
class ISizeCalculator {
public:
    virtual ~ISizeCalculator() {}
    // Метод для подсчета размеров, который будет реализован в конкретных стратегиях.
    virtual void calculate(const QDir &dir, QTextStream &out) = 0;
};

#endif // ISIZECALCULATOR_H
