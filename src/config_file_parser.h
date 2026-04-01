#ifndef CONFIG_FILE_PARSER_H
#define CONFIG_FILE_PARSER_H

#include "qdir.h"
#include <QRegularExpression>

#include "src/wire_connection.h"
#include "cable.h"

namespace util {

using namespace domain;

class ConfigFileParser {
public:
    ConfigFileParser();

    static std::optional<Cable> parseWireFile(const QString &fileName) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Не удалось открыть файл:" << fileName;
            return std::nullopt;
        }

        QTextStream in(&file);
        int lineNumber = 0;
        Cable cable;

        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            ++lineNumber;

            // Пропускаем пустые строки и комментарии
            if (line.isEmpty() || line[0] == '#') {
                continue;
            }

            // Парсим строку и создаём WireConnection
            domain::WireConnection conn = parseLine(line, lineNumber);
            if (conn.GetFrom() != -1) { // Проверка на успешность парсинга
                cable.AddConnection(conn);
            }
        }

        file.close();
        return cable;
    }

private:
    static WireConnection parseLine(const QString &line, int lineNumber) {
        WireConnection conn;
        conn.SetFrom(-1);

        // Разбиваем строку по пробелам ИЛИ запятым, пропускаем пустые части
        QStringList parts = line.split(QRegularExpression("[,\\s]+"), Qt::SkipEmptyParts);

        if (parts.isEmpty()) {
            return conn;
        }

        bool ok;
        int fromPin = parts[0].toInt(&ok);
        if (!ok) {
            qDebug() << "Ошибка в строке" << lineNumber
                     << ": неверное значение контакта FROM:" << parts[0];
            return conn;
        }
        conn.SetFrom(fromPin);

        // Обрабатываем все оставшиеся части как toPins
        for (int i = 1; i < parts.size(); ++i) {
            bool targetOk;
            int pin = parts[i].toInt(&targetOk);
            if (targetOk) {
                conn.AddTo(pin);
            } else {
                qDebug() << "Ошибка в строке" << lineNumber
                         << ": неверное значение контакта TO:" << parts[i];
                conn.SetFrom(-1);
                return conn;
            }
        }

        return conn;
    }
};

} // namespace util

#endif // CONFIG_FILE_PARSER_H
