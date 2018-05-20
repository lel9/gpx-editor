#ifndef TURNS_GLOBAL_H
#define TURNS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TURNS_LIBRARY)
#  define TURNSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TURNSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TURNS_GLOBAL_H
