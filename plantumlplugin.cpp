#include "plantumlplugin.h"
#include "outputpane.h"
#include "optionspage.h"
#include "optionform.h"

#include <coreplugin/editormanager/editormanager.h>

#include <QDebug>

namespace PlantUML {
namespace Internal {

PlantUMLPlugin::PlantUMLPlugin()
{
    // Create your members
}

PlantUMLPlugin::~PlantUMLPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool PlantUMLPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.

    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    // Create plantUML output pane
    _outputPane = new OutputPane();
    _optionsPage = new OptionsPage(&_plantuml);

    connect(Core::EditorManager::instance(), &Core::EditorManager::currentEditorChanged,
        this, &PlantUMLPlugin::currentEditorChanged);
    connect(Core::EditorManager::instance(), &Core::EditorManager::aboutToSave,
        this, &PlantUMLPlugin::aboutToSave);
    connect(&_plantuml, &Plantuml::incomingImage, _outputPane, &OutputPane::updateImage);
    connect(&_plantuml, &Plantuml::redrawing, _outputPane, &OutputPane::redrawing);
    connect(&_plantuml, &Plantuml::incomingError, _outputPane, &OutputPane::processError);

    return true;
}

void PlantUMLPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag PlantUMLPlugin::aboutToShutdown() {
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

void PlantUMLPlugin::currentEditorChanged(Core::IEditor *editor) {

    if (editor==0) {
        _currentDoc = 0;
        return;
    }
    _currentDoc = editor->document();
    if (_currentDoc==0) return;
    draw(_currentDoc->contents());
}

void PlantUMLPlugin::aboutToSave(Core::IDocument *doc) {
    if (_currentDoc!=0 && doc==_currentDoc) {
        draw(_currentDoc->contents());

    }

}

void PlantUMLPlugin::draw(const QByteArray &text) {
    if (!text.isEmpty()) _plantuml.draw(text);
}


} // namespace Internal
} // namespace PlantUML
