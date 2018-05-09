#pragma once

#include "plantuml_global.h"
#include <extensionsystem/iplugin.h>

#include <coreplugin/editormanager/ieditor.h>
#include <coreplugin/idocument.h>
#include "plantuml.h"
#include "javatest.h"

class OptionsPage;
class OutputPane;


namespace PlantUML {
namespace Internal {

class PlantUMLPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "PlantUML.json")

public:
    PlantUMLPlugin();
    ~PlantUMLPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

public slots:

    void currentEditorChanged(Core::IEditor *editor);
    void aboutToSave(Core::IDocument* doc);

private:

    OutputPane* _outputPane;
    OptionsPage* _optionsPage;
    Core::IDocument* _currentDoc;
    Plantuml _plantuml;

    void draw(const QByteArray& text);

};

} // namespace Internal
} // namespace PlantUML
