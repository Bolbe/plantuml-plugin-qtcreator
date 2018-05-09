#ifndef OPTIONFORM_H
#define OPTIONFORM_H

#include <QWidget>

class Plantuml;
class JavaTest;

namespace Ui {
class OptionForm;
}

class OptionForm : public QWidget
{
    Q_OBJECT

public:
    explicit OptionForm(Plantuml* plantuml);
    ~OptionForm();

private slots:

    void testing();
    void testImage(const QByteArray& byteArray);

private:
    Ui::OptionForm *ui;
    Plantuml* _plantuml;

    void setPixmap(const QPixmap& pixmap);

};

#endif // OPTIONFORM_H
