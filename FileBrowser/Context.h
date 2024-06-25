#ifndef CONTEXT_H
#define CONTEXT_H

#include <QString>
#include <QMap>
#include <memory>
#include "ICalculationStrategy.h"

using namespace std;

class Context
{
public:
    Context(unique_ptr<ICalculationStrategy> st) : strategy(std::move(st)) {}  // Конструктор класса Context, принимающий умный указатель на объект типа ICalculationStrategy и перемещающий его во внутреннее поле strategy

    void setStrategy(unique_ptr<ICalculationStrategy> str) {  // Метод для установки стратегии вычислений
        this->strategy = std::move(str);  // Перемещение переданного умного указателя во внутреннее поле strategy
    }

    QMap<QString, int> calculate(const QString& path) {  // Метод для вычисления с использованием текущей стратегии
        return strategy->calculate(path);
    }

private:
    unique_ptr<ICalculationStrategy> strategy;  // Умный указатель, используемый для хранения текущей стратегии вычислений
};

#endif // CONTEXT_H
