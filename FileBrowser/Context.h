#ifndef CONTEXT_H
#define CONTEXT_H

#include <QDir>
#include <QTextStream>
#include "ISizeCalculator.h"

// Класс Context хранит указатель на стратегию и делегирует ей выполнение.
class Context {
public:
    // Метод для установки стратегии.
    void setStrategy(ISizeCalculator *strategy) {
        this->strategy = strategy;
    }

    // Метод для выполнения стратегии.
    void executeStrategy(const QDir &dir, QTextStream &out) {
        if (strategy) {
            strategy->calculate(dir, out);
        }
    }

private:
    ISizeCalculator *strategy = nullptr; // Указатель на текущую стратегию.
};

#endif // CONTEXT_H
