#pragma once

#include <QtGlobal>

#if defined(PLANTUML_LIBRARY)
#  define PLANTUMLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PLANTUMLSHARED_EXPORT Q_DECL_IMPORT
#endif
