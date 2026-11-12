// Z:\Toshi\Source\TKernel\TObject.cpp - the TObject constructor, kept in a file of its own: the original
// CreateObject/CreateObjectInPlace call it out of line, and our compiler build would inline it from the same file.
#define TOSHI_API __declspec(dllexport)
#include "TKernelObject.h"

namespace Toshi {

TObject::TObject()
{
}

} // namespace Toshi
