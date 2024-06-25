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
    Context(unique_ptr<ICalculationStrategy> st) : strategy(std::move(st)) {}

    void setStrategy(unique_ptr<ICalculationStrategy> str) {
        this->strategy = std::move(str);
    }

    QMap<QString, int> calculate(const QString& path) {
        return strategy->calculate(path);
    }

private:
    unique_ptr<ICalculationStrategy> strategy;
};

#endif // CONTEXT_H
