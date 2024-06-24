#include <QCoreApplication>
#include <QDir>
#include <QTextStream>
#include "ISizeCalculator.h"
#include "FileSizeCalculator.h"
#include "FileTypeSizeCalculator.h"
#include "Context.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv); // Инициализация приложения.
    QTextStream out(stdout); // Поток для вывода данных в консоль.
    QTextStream in(stdin); // Поток для ввода данных из консоли.

    out << "Enter directory path: ";
    out.flush(); // Принудительная отправка данных в консоль.
    QString dirPath = in.readLine(); // Считывание пути к директории.

    QDir dir(dirPath); // Создание объекта QDir для работы с директориями.
    if (!dir.exists()) {
        out << "Directory does not exist!" << Qt::endl;
        return 1;
    }

    out << "Choose calculation method (1 - by files, 2 - by file types): ";
    out.flush();
    QString methodChoice = in.readLine().trimmed(); // Считывание выбора пользователя.

    Context context; // Создание объекта Context.
    ISizeCalculator *calculator = nullptr; // Указатель на стратегию.

    try {
        // Выбор стратегии в зависимости от выбора пользователя.
        if (methodChoice == "1") {
            calculator = new FileSizeCalculator();
        } else if (methodChoice == "2") {
            calculator = new FileTypeSizeCalculator();
        } else {
            out << "Invalid choice!" << Qt::endl;
            return 1;
        }

        context.setStrategy(calculator); // Установка стратегии в Context.
        context.executeStrategy(dir, out); // Выполнение стратегии.
    } catch (const std::exception &e) {
        out << "An error occurred: " << e.what() << Qt::endl;
    } catch (...) {
        out << "An unknown error occurred." << Qt::endl;
    }

    delete calculator; // Освобождение памяти, выделенной под стратегию.

    return a.exec(); // Запуск главного цикла приложения.
}
