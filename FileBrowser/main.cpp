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

    // Выбор стратегии в зависимости от выбора пользователя.
    if (methodChoice == "1") {
        calculator = new FileSizeCalculator();
    } else if (methodChoice == "2") {
        calculator = new FileTypeSizeCalculator();
    } else {
        out << "Invalid choice!" << Qt::endl;
        return 1; // Возвращаем код ошибки, если выбор пользователя некорректен.
    }

    // Проверка на nullptr перед установкой стратегии
    if (calculator) {
        context.setStrategy(calculator); // Установка стратегии в Context.
        context.executeStrategy(dir, out); // Выполнение стратегии.
    } else {
        out << "Failed to create calculator object." << Qt::endl;
        return 1; // Возвращаем код ошибки, если не удалось создать объект стратегии.
    }

    delete calculator; // Освобождение памяти, выделенной под стратегию.


    return a.exec(); // Запуск главного цикла приложения.
}
