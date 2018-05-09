#include "javatest.h"
#include <QDebug>

#define JAVA_NOT_FOUND "<font color='#F00'>Java VM not found. Check it is correctly set in your PATH environment variable."

JavaTest::JavaTest(QObject *parent) : QObject(parent)
{
    _process = new QProcess(this);
    connect(_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished(int,QProcess::ExitStatus)));
    connect(_process, &QProcess::errorOccurred, this, &JavaTest::errorOccurred);
}

void JavaTest::requestVersion() {
    _process->start("java", QStringList() << "-version");
}

void JavaTest::processFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    QByteArray byteArray = _process->readAllStandardOutput();
    if (byteArray.isEmpty()) byteArray = _process->readAllStandardError();
    if (byteArray.isEmpty()) {
        emit version(JAVA_NOT_FOUND);
        return;
    }
    QString string = QString::fromLocal8Bit(byteArray);
    QString ver = string.left(string.indexOf('\n'));
    qDebug() << "Java version: " << ver;
    emit version(ver);

}

void JavaTest::errorOccurred(QProcess::ProcessError error) {
    emit version(JAVA_NOT_FOUND);
}
