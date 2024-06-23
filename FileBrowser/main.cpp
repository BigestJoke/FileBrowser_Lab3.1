#include <QCoreApplication>
#include <QDir>
#include <QTextStream>
#include "ISizeCalculator.h"
#include "FileSizeCalculator.h"
#include "FileTypeSizeCalculator.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QTextStream out(stdout);
    QTextStream in(stdin);

    out << "Enter directory path: ";
    out.flush();
    QString dirPath = in.readLine();

    QDir dir(dirPath);
    if (!dir.exists()) {
        out << "Directory does not exist!" << Qt::endl;
        return 1;
    }

    out << "Choose calculation method (1 - by files, 2 - by file types): ";
    out.flush();
    QString methodChoice = in.readLine().trimmed();

    ISizeCalculator *calculator = nullptr;

    if (methodChoice == "1") {
        calculator = new FileSizeCalculator();
    } else if (methodChoice == "2") {
        calculator = new FileTypeSizeCalculator();
    } else {
        out << "Invalid choice!" << Qt::endl;
        return 1;
    }

    calculator->calculate(dir, out);
    delete calculator;

    return a.exec();
}
