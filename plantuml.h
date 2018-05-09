#ifndef PLANTUML_H
#define PLANTUML_H

#include <QObject>
#include <QProcess>

class QSettings;

class Plantuml : public QObject
{
    Q_OBJECT
public:
    explicit Plantuml();
    QString jarPath() { return _jarPath; }

signals:

    void incomingImage(QByteArray byteArray);
    void redrawing();
    void incomingError(QString errorString);

public slots:

    void draw(const QByteArray &plantuml);
    void setJarPath(const QString& jarPath);

private slots:

    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);    
    void errorOccurred(QProcess::ProcessError error);


private:

    QString _jarPath;
    QProcess* _process;
    QSettings* _settings;
    QByteArray _pendingPlantuml;

};

#endif // PLANTUML_H
