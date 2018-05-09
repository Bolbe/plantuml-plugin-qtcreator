#include "outputpane.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>

OutputPane::OutputPane() :
    _mainWidget(new QWidget())
{   

    _statusLabel = new QLabel("Idle");
    _imageLabel = new QLabel();
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidget(_imageLabel);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(_statusLabel);
    layout->addWidget(scrollArea);
    _mainWidget->setLayout(layout);

}

QWidget *OutputPane::outputWidget(QWidget *parent) {
    Q_UNUSED(parent)
    return _mainWidget;
}

QList<QWidget *> OutputPane::toolBarWidgets() const {
    return {};
}

QString OutputPane::displayName() const {
    return "PlantUML";
}

int OutputPane::priorityInStatusBar() const {
    return 1;
}

void OutputPane::clearContents() {

}

void OutputPane::visibilityChanged(bool visible) {

}

void OutputPane::setFocus() {
    _mainWidget->setFocus();
}

bool OutputPane::hasFocus() const {
    _mainWidget->hasFocus();
}

bool OutputPane::canFocus() const {
    return true;
}

bool OutputPane::canNavigate() const {
    return false;
}

bool OutputPane::canNext() const {
    return false;
}

bool OutputPane::canPrevious() const {
    return false;
}

void OutputPane::goToNext() {

}

void OutputPane::goToPrev() {

}

void OutputPane::updateImage(const QByteArray &byteArray) {
    _statusLabel->setText("Idle");
    QPixmap pixmap;
    pixmap.loadFromData(byteArray);
    setPixmap(pixmap);
}

void OutputPane::redrawing() {
    _statusLabel->setText("Redrawing...");
    QPixmap pixmap(":/hourglass.png");
    setPixmap(pixmap);
}

void OutputPane::processError(QString errorString) {
    _statusLabel->setText(errorString);
}

void OutputPane::setPixmap(const QPixmap &pixmap) {
    _imageLabel->setPixmap(pixmap);
    _imageLabel->setFixedSize(pixmap.width(), pixmap.height());
}

