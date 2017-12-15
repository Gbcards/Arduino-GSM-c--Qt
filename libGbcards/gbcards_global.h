#ifndef GBCARDS_GLOBAL_H
#define GBCARDS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GBCARDS_LIBRARY)
#  define GBCARDSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GBCARDSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GBCARDS_GLOBAL_H
