#ifndef CONTEXT_H
#define CONTEXT_H

#include <QDir>
#include <QTextStream>
#include "ISizeCalculator.h"

class Context {
public:
    void setStrategy(ISizeCalculator *strategy) {
        this->strategy = strategy;
    }

    void executeStrategy(const QDir &dir, QTextStream &out) {
        if (strategy) {
            strategy->calculate(dir, out);
        }
    }

private:
    ISizeCalculator *strategy = nullptr;
};

#endif // CONTEXT_H
