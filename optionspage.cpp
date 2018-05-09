#include "optionspage.h"
#include "optionform.h"
#include "plantuml.h"

OptionsPage::OptionsPage(Plantuml* plantuml):
    _optionForm(0),
    _plantuml(plantuml)
{
    setId("PlantUML");
    setDisplayName(tr("PlantUML"));
    setCategory("PlantUML");
    setDisplayCategory("PlantUML");
    setCategoryIcon(Utils::Icon(":/logo.png"));
}

QWidget *OptionsPage::widget() {
    if (!_optionForm) {
        _optionForm = new OptionForm(_plantuml);
    }
    return _optionForm;
}

void OptionsPage::apply() {

}

void OptionsPage::finish() {
    delete _optionForm;
}
