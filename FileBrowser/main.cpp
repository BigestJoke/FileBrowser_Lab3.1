#include <iostream>
#include "Context.h"
#include "FolderSizeStrategy.h"
#include "FileTypeSizeStrategy.h"
#include <memory>
#include <QString>
#include <QDir>

using namespace std;

QString percentageCalc(int size, int total_size) {
    if (total_size != 0 && size != 0) {
        double percent = 100.0 * size / total_size;
        if (percent < 0.01) return "< 0.01 %";
        else return QString::number(percent, 'f', 2) + " %";
    }
    else {
        return "0.00 %";
    }
}

int main() {
    cout << "Enter the path to the directory: ";
    string path;
    getline(cin, path);

    cout << "Select a strategy for calculating file sizes: 1 - grouping by folders, 2 - grouping by types. ";
    int strategy;
    cin >> strategy;

    unique_ptr<Context> calculator;
    switch (strategy) {
    case 1:
        calculator = make_unique<Context>(make_unique<FolderSizeStrategy>());
        break;
    case 2:
        calculator = make_unique<Context>(make_unique<FileTypeSizeStrategy>());
        break;
    default:
        cout << "Wrong strategy." << endl;
        return 1;
    }

    QString qPath = QString::fromStdString(path);
    QDir dir(qPath);
    if (!dir.exists()) {
        cout << "Directory doesn't exist." << endl;
        return 1;
    }

    QMap<QString, int> result = calculator->calculate(qPath);
    int totalSize = calcDirSize(qPath);

    if (result.isEmpty()) {
        cout << "Current Directory: " << qPath.toStdString() << "  Size: 0 KB " << " Percentage: 0.00%" << endl;
    } else {
        for (auto it = result.begin(); it != result.end(); ++it) {
            QString name = it.key();
            int size = it.value();
            QString percentage = percentageCalc(size, totalSize);
            cout << "Name: " << name.toStdString()
                 << "  Size: " << size / 1024 << " KB"
                 << "  Percentage: " << percentage.toStdString() << endl;
        }
    }

    return 0;
}
