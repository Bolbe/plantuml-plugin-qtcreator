#include "optionform.h"
#include "ui_optionform.h"
#include <QDebug>
#include <QFileDialog>
#include <QPixmap>
#include "plantuml.h"
#include "javatest.h"

OptionForm::OptionForm(Plantuml *plantuml) :
    _plantuml(plantuml),
    ui(new Ui::OptionForm)
{
    ui->setupUi(this);

    // click browse
    connect(ui->browseButton, &QPushButton::clicked, [this]() {
        QString jarFileName = QFileDialog::getOpenFileName(this, "Where is plantuml.jar ?",
                                                        "",
                                                        tr("jar (*.jar);;All files (*.*)"));

        if (!jarFileName.isNull() && !jarFileName.isEmpty()) {
            ui->pathLineEdit->setText(jarFileName);
            _plantuml->setJarPath(jarFileName);
        }

    });
    // click plantUML test
    connect(ui->plantumlButton, &QPushButton::clicked, [this]() {
        disconnect(_plantuml, 0, this, 0); // first clear all existing connections between plantuml and this
        connect(_plantuml, &Plantuml::redrawing, this, &OptionForm::testing);
        connect(_plantuml, &Plantuml::incomingImage, this, &OptionForm::testImage);
        connect(_plantuml, &Plantuml::incomingError, [this](QString string) {
            ui->testingLabel->setText(string);
            setPixmap(QPixmap());
        });
        _plantuml->draw(QByteArray("TestPlantUML -> OK"));
    });

    // java test
    JavaTest* javaTest = new JavaTest(this); // destroyed when parent destroyed
    connect(javaTest, &JavaTest::version, ui->javaVersionLabel, &QLabel::setText);
    javaTest->requestVersion();


}

OptionForm::~OptionForm() {
    qDebug() << "Deleting OptionForm";
    delete ui;

}

void OptionForm::testing() {
    ui->testingLabel->setText("Testing...");
    QPixmap pixmap(":/hourglass.png");
    setPixmap(pixmap);
}

void OptionForm::testImage(const QByteArray &byteArray) {
    disconnect(_plantuml, 0, this, 0); // clear connections
    ui->testingLabel->setText("");
    QPixmap pixmap;
    pixmap.loadFromData(byteArray);
    setPixmap(pixmap);
}

void OptionForm::setPixmap(const QPixmap &pixmap) {
    ui->plantumlLabel->setPixmap(pixmap);

}

