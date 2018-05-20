#ifndef SLOPES_GLOBAL_H
#define SLOPES_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SLOPES_LIBRARY)
#  define SLOPESSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SLOPESSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SLOPES_GLOBAL_H
