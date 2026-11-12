// Toshi::TGUIFunction and its three implementations (TGuiInterface.dll): a 1-D function used to animate GUI values.
//   Compute(x) = ComputeNormalised(x * m_fInputScale + m_fInputOffset) * m_fOutputScale + m_fOutputOffset
// Vtable: [0] GetClass [1] Delete [2] destructor [3] Deserialise [4] Serialise [5] Clone [6] ComputeNormalised.
// The constructors, destructors, Compute, Clone and ComputeNormalised are inline (the binary keeps their exported
// copies together with the other header inlines); the derived classes' copy constructors are compiler-generated.
#ifndef TGUIFUNCTION_H
#define TGUIFUNCTION_H
#include <math.h>
#include "TGUIAPI.h"
#include "TObject.h"
#include "TMath.h"

class PProperties;

namespace Toshi {

class TGUI_API TGUIFunction : public TObject
{
public:
    TGUIFunction()
    {
        m_fInputScale = 1.0f;
        m_fInputOffset = 0.0f;
        m_fOutputScale = 1.0f;
        m_fOutputOffset = 0.0f;
    }
    TGUIFunction(float inputScale, float inputOffset, float outputScale, float outputOffset)
    {
        m_fInputScale = inputScale;
        m_fInputOffset = inputOffset;
        m_fOutputScale = outputScale;
        m_fOutputOffset = outputOffset;
    }
    virtual ~TGUIFunction() {}

    virtual TClass& GetClass() const;                           // slot 0
    virtual bool Deserialise(const PProperties* properties);    // slot 3
    virtual bool Serialise(PProperties* properties);            // slot 4
    virtual TGUIFunction* Clone() const = 0;                    // slot 5
    virtual float ComputeNormalised(float x) const = 0;         // slot 6

    float Compute(float x) const
    {
        return ComputeNormalised(x * m_fInputScale + m_fInputOffset) * m_fOutputScale + m_fOutputOffset;
    }

    static TClass m_sClass;

protected:
    TGUIFunction(const TGUIFunction& other)
        : TObject(other)
        , m_fInputScale(other.m_fInputScale)
        , m_fInputOffset(other.m_fInputOffset)
        , m_fOutputScale(other.m_fOutputScale)
        , m_fOutputOffset(other.m_fOutputOffset)
    {
    }

    float m_fInputScale;    // +0x04
    float m_fInputOffset;   // +0x08
    float m_fOutputScale;   // +0x0C
    float m_fOutputOffset;  // +0x10

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();
};

// ComputeNormalised is constant: the function is only its output offset
class TGUI_API TGUIConstantFunction : public TGUIFunction
{
public:
    TGUIConstantFunction() {}
    TGUIConstantFunction(float inputScale, float inputOffset, float outputScale, float outputOffset)
        : TGUIFunction(inputScale, inputOffset, outputScale, outputOffset)
    {
    }
    virtual ~TGUIConstantFunction() {}

    virtual TClass& GetClass() const;
    virtual TGUIConstantFunction* Clone() const { return new TGUIConstantFunction(*this); }
    virtual float ComputeNormalised(float x) const
    {
        return 0.0f;
    }

    static TClass m_sClass;

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();
};

// ComputeNormalised is sin(x * PI)
class TGUI_API TGUISineFunction : public TGUIFunction
{
public:
    TGUISineFunction() {}
    TGUISineFunction(float inputScale, float inputOffset, float outputScale, float outputOffset)
        : TGUIFunction(inputScale, inputOffset, outputScale, outputOffset)
    {
    }
    virtual ~TGUISineFunction() {}

    virtual TClass& GetClass() const;
    virtual TGUISineFunction* Clone() const { return new TGUISineFunction(*this); }
    virtual float ComputeNormalised(float x) const
    {
        return (float)sin(x * TMath::PI);
    }

    static TClass m_sClass;

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();
};

// ComputeNormalised ramps from -1 to 1 once per unit of x
class TGUI_API TGUISawtoothFunction : public TGUIFunction
{
public:
    TGUISawtoothFunction() {}
    TGUISawtoothFunction(float inputScale, float inputOffset, float outputScale, float outputOffset)
        : TGUIFunction(inputScale, inputOffset, outputScale, outputOffset)
    {
    }
    virtual ~TGUISawtoothFunction() {}

    virtual TClass& GetClass() const;
    virtual TGUISawtoothFunction* Clone() const { return new TGUISawtoothFunction(*this); }
    virtual float ComputeNormalised(float x) const
    {
        double fraction = fmod(x, 1.0);
        return -1.0f + fraction + fraction;
    }

    static TClass m_sClass;

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();
};

} // namespace Toshi
#endif
