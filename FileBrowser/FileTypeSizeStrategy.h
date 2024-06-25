#ifndef FILETYPESIZESTRATEGY_H
#define FILETYPESIZESTRATEGY_H

#include "ICalculationStrategy.h"
#include <QFileInfo>
#include <QDir>
#include <QMap>

class FileTypeSizeStrategy : public ICalculationStrategy {
public:
    QMap<QString, int> calculate(const QString& path) override;
};

#endif // FILETYPESIZESTRATEGY_H
