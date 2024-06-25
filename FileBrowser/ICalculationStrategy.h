#ifndef ICALCULATIONSTRATEGY_H
#define ICALCULATIONSTRATEGY_H

#include <QString>
#include <QMap>

class ICalculationStrategy {
public:
    virtual ~ICalculationStrategy() = default;
    virtual QMap<QString, int> calculate(const QString& path) = 0;
};

#endif // ICALCULATIONSTRATEGY_H
