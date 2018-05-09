#include "optionform.h"
#include "ui_optionform.h"
#include <QFileDialog>
#include <QPixmap>
#include "plantuml.h"
#include "javatest.h"

OptionForm::OptionForm(Plantuml *plantuml) :
    _plantuml(plantuml),
    ui(new Ui::OptionForm)
{
    ui->setupUi(this);
    connect(_plantuml, &Plantuml::redrawing, this, &OptionForm::testing);
    connect(_plantuml, &Plantuml::incomingImage, this, &OptionForm::testImage);
    connect(_plantuml, &Plantuml::incomingError, this, &OptionForm::processError);

    // click browse
    connect(ui->browseButton, &QPushButton::clicked, [this]() {
        QString jarFileName = QFileDialog::getOpenFileName(this, tr("Where is plantuml.jar ?"),
                                                        "",
                                                        tr("jar (*.jar);;All files (*.*)"));

        if (!jarFileName.isNull() && !jarFileName.isEmpty()) {
            ui->pathLineEdit->setText(jarFileName);
        }

    });
    // when the path changes in this input component, notify _plantuml
    ui->pathLineEdit->setText(_plantuml->jarPath());
    connect(ui->pathLineEdit, &QLineEdit::textChanged, _plantuml, &Plantuml::setJarPath);
    // click plantUML test
    connect(ui->plantumlButton, &QPushButton::clicked, [this]() {
        _plantuml->draw(QByteArray("TestPlantUML -> OK"));
    });

    // java test
    JavaTest* javaTest = new JavaTest(this); // destroyed when parent destroyed
    connect(javaTest, &JavaTest::version, ui->javaVersionLabel, &QLabel::setText);
    javaTest->requestVersion();


}

OptionForm::~OptionForm() {
    disconnect(_plantuml, 0, this, 0); // clear connections
    delete ui;

}

void OptionForm::testing() {
    ui->testingLabel->setText(tr("Testing..."));
    QPixmap pixmap(":/hourglass.png");
    setPixmap(pixmap);
}

void OptionForm::testImage(const QByteArray &byteArray) {
    ui->testingLabel->setText("");
    QPixmap pixmap;
    pixmap.loadFromData(byteArray);
    setPixmap(pixmap);
}

void OptionForm::processError(QString errorString) {
    ui->testingLabel->setText(errorString);
    setPixmap(QPixmap());
}

void OptionForm::setPixmap(const QPixmap &pixmap) {
    ui->plantumlLabel->setPixmap(pixmap);

}

