#ifndef JAVATEST_H
#define JAVATEST_H

#include <QObject>
#include <QProcess>

class JavaTest : public QObject
{
    Q_OBJECT
public:
    explicit JavaTest(QObject *parent = nullptr);
    void requestVersion();

signals:

    void version(QString ver);

private slots:

    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void errorOccurred(QProcess::ProcessError error);

private:

    QProcess* _process;

};

#endif // JAVATEST_H
