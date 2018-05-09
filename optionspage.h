#ifndef OPTIONSPAGE_H
#define OPTIONSPAGE_H

#include <coreplugin/dialogs/ioptionspage.h>
#include <QPointer>

class OptionForm;
class Plantuml;

class OptionsPage : public Core::IOptionsPage
{
public:
    OptionsPage(Plantuml* plantuml);

    // IOptionsPage interface
public:
    QWidget *widget();
    void apply();
    void finish();

private:

    QPointer<OptionForm> _optionForm;
    Plantuml* _plantuml;

};


#endif // OPTIONSPAGE_H
