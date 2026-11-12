// Toshi::TSortedArray<T, Comparator> - a TArray whose elements are kept in the order Comparator gives
// (TGuiInterface.dll: the GUI classes' ms_oPropertySetOrdered, TGUIWidgetInfo's state variables).
// Only construction and destruction are reconstructed so far; they are TArray's.
#ifndef TSORTEDARRAY_H
#define TSORTEDARRAY_H
#include "TArray.h"

namespace Toshi {

template <class T, class Comparator>
class TSortedArray : public TArray<T>
{
public:
    TSortedArray() {}
    explicit TSortedArray(int grow) : TArray<T>(grow) {}
};

} // namespace Toshi
#endif
