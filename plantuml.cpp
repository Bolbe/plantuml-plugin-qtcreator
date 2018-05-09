#include "plantuml.h"
#include <QSettings>
#include <QProcess>
#include <coreplugin/icore.h>

#define JAR_PATH_KEY "jarPath"

Plantuml::Plantuml() : QObject(),
    _process(new QProcess(this)),
    _settings(Core::ICore::settings())
{
    connect(_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished(int,QProcess::ExitStatus)));
    connect(_process, &QProcess::errorOccurred, this, &Plantuml::errorOccurred);
    _settings->beginGroup("PlantUMLPlugin");
    _jarPath = _settings->value(JAR_PATH_KEY, QVariant("path/to/plantuml.jar")).toString();

}

void Plantuml::setJarPath(const QString &jarPath) {
    _jarPath = jarPath;
    _settings->setValue(JAR_PATH_KEY, jarPath);
    _settings->sync();
}



void Plantuml::draw(const QByteArray &plantuml) {
    if (_process->state()!=QProcess::NotRunning) { // we are already drawing something, we'll handle this new one once finished
        _pendingPlantuml = plantuml;
        return;
    }
    emit redrawing();
    _process->start("java", QStringList() << "-Djava.awt.headless=true" << "-jar" << _jarPath << "-p");
    _process->write(plantuml);
    _process->closeWriteChannel();
    _pendingPlantuml = QByteArray(); // no more pending plantuml to draw
}

void Plantuml::processFinished(int exitCode, QProcess::ExitStatus exitStatus) {

    QByteArray errorByteArray = _process->readAllStandardError();
    if (!errorByteArray.isEmpty()) {
        emit incomingError(QString::fromLocal8Bit(errorByteArray));
    }
    else {
        QByteArray byteArray = _process->readAllStandardOutput();
        if (!byteArray.isEmpty()) emit incomingImage(byteArray);
    }

    if (!_pendingPlantuml.isEmpty()) {
        draw(_pendingPlantuml); // draw the pending plantuml if not empty
    }
}

void Plantuml::errorOccurred(QProcess::ProcessError error) {
    emit incomingError(tr("Error while starting Java VM process. Is it in your PATH environment variable ?"));
}

