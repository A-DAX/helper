#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "../../qhelper.h"

#define TRUC_USE_int USELESS,int
#define TRUC_int(A) qWarning() << "AAA" << A
#define TRUC_ALL(A) qWarning() << "BBB" << A
#define TRUC(type, A) KEYWORD_ADRESSER(TRUC, type, A)

#define TRUCA_USE_int USELESS,int
#define TRUCA_int() qWarning() << "AAA"
#define TRUCA_ALL() qWarning() << "BBB"
#define TRUCA(type) KEYWORD_ADRESSER(TRUCA, type)

int main(int argc, char *argv[])
{
    qWarning() << "1" << AxTYPED_EQ_COMPARATOR(int, 1, 1);
    qWarning() << "2" <<  AxTYPED_EQ_COMPARATOR(int, 2, 1);
    qWarning() << "3" <<  AxTYPED_EQ_COMPARATOR(int, QVariant(1), QVariant(1));
    qWarning() << "4" <<  AxTYPED_EQ_COMPARATOR(int, QVariant("1"), QVariant(1));
    qWarning() << "5" <<  AxTYPED_EQ_COMPARATOR(QVariant, QVariant(1), QVariant(1));
    qWarning() << "6" <<  AxTYPED_EQ_COMPARATOR(QVariant, QVariant("1"), QVariant(1));

    TRUC(int, "CCC");
    TRUC(float, "CCC");
    TRUCA(int);
    TRUCA(float);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("test_qhelper", "Main");

    return app.exec();
}
