#ifndef OUTPUTPANE_H
#define OUTPUTPANE_H

#include <coreplugin/ioutputpane.h>
#include "plantuml.h"

class QLabel;

class OutputPane : public Core::IOutputPane
{
public:
    OutputPane();

    // IOutputPane interface
public:
    QWidget *outputWidget(QWidget* parent);
    QList<QWidget*> toolBarWidgets() const;
    QString displayName() const;
    int priorityInStatusBar() const;
    void clearContents();
    void visibilityChanged(bool visible);
    void setFocus();
    bool hasFocus() const;
    bool canFocus() const;
    bool canNavigate() const;
    bool canNext() const;
    bool canPrevious() const;
    void goToNext();
    void goToPrev();

public slots:

    void updateImage(const QByteArray& byteArray);
    void redrawing();
    void processError(QString errorString);


private:

    QWidget* _mainWidget;
    QLabel* _statusLabel;
    QLabel* _imageLabel;

    void setPixmap(const QPixmap& pixmap);

};

#endif // OUTPUTPANE_H
