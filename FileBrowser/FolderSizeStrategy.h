#ifndef FOLDERSIZESTRATEGY_H
#define FOLDERSIZESTRATEGY_H

#include "ICalculationStrategy.h"
#include <QFileInfo>
#include <QDir>
#include <QMap>

class FolderSizeStrategy : public ICalculationStrategy {
public:
    QMap<QString, int> calculate(const QString& path) override;
};

int calcDirSize(const QString& path); // Объявление внешней функции calcDirSize для вычисления размера указанной директории

#endif // FOLDERSIZESTRATEGY_H
