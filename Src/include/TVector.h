// Toshi math value types - import declarations generated from TKernelInterface.dll's export
// table by tools/genhdr.py --import (every member, even the copy constructors, is a kernel function).
// Data members: public, layouts from usage.
#ifndef TVECTOR_H
#define TVECTOR_H
#include "TMemory.h"
// Round 33: the original copies these with the implicit (block) copy, so no user-defined copy
// operators by default; define TVECTOR_USER_COPY to bring the old explicit ones back.
#ifndef TVECTOR_USER_COPY
#define TVECTOR_IMPLICIT_COPY
#endif
// Rule used here: kernel functions that no JPOG module imports are inline in the original headers
// (their bodies come from the kernel itself); everything else is an import.

// Inside TKernelInterface.dll (TOSHI_KERNEL_BUILD) these classes are exported as a whole, so the compiler
// also emits the members that are written inline in the class body. Every other module sees plain inline code.
#ifdef TOSHI_KERNEL_BUILD
#define TOSHI_EXPORT __declspec(dllexport)
#else
#define TOSHI_EXPORT
#endif

namespace Toshi {

class TVector2;
class TVector3;
class TVector4;
class TQuaternion;
class TPlane;
class TSphere;
class TAABox;
class TMatrix44;

class TVector2
{
public:
#ifndef TVECTOR_IMPLICIT_COPY
    TVector2& operator=(const TVector2& o) { x = o.x; y = o.y; return *this; }
#endif
    TOSHI_API float CrossProduct(const TVector2&) const;
    TOSHI_API float DotProduct(const TVector2&) const;
    void Set(float _x, float _y) { x = _x; y = _y; }
    TOSHI_API bool operator!=(const TVector2&) const;
    TOSHI_API bool operator==(const TVector2&) const;
    TOSHI_API TVector2& operator/=(float);
    TOSHI_API TVector2& operator/=(const TVector2&);
    TOSHI_API TVector2& operator*=(float);
    TOSHI_API TVector2& operator*=(const TVector2&);
    TOSHI_API TVector2& operator-=(const TVector2&);
    TOSHI_API TVector2& operator+=(const TVector2&);
    TOSHI_API const float& operator()(unsigned int) const;
    TOSHI_API float& operator()(unsigned int);
    TOSHI_API TVector2(const float*const);
    TVector2(float _x, float _y) { x = _x; y = _y; }
#ifndef TVECTOR_IMPLICIT_COPY
    TVector2(const TVector2& o) { x = o.x; y = o.y; }
#endif
    TVector2() {}
    TOSHI_API void Normalise();
    TOSHI_API bool IsNormalised(float) const;
    TOSHI_API static float __stdcall Distance(const TVector2&, const TVector2&);
    TOSHI_API void Lerp(const TVector2&, const TVector2&, float);
    TOSHI_API void Rotate(float);
    TOSHI_API static void __stdcall SubXZ(TVector3&, const TVector3&, const TVector2&);
    TOSHI_API TVector3 GetVector3XZ() const;
    TOSHI_API TVector3 GetVector3XY() const;
    TOSHI_API void SetXZFromVector3(const TVector3&);
    TOSHI_API void SetXYFromVector3(const TVector3&);
    TOSHI_API static void __stdcall AddXZ(TVector3&, const TVector3&, const TVector2&);
    TOSHI_API void SetPerpendicular();
    TOSHI_API static float __stdcall DistanceSq(const TVector2&, const TVector2&);
    TOSHI_API static float __stdcall CrossProduct(const TVector2&, const TVector2&);
    TOSHI_API static float __stdcall DotProduct(const TVector2&, const TVector2&);
    TOSHI_API float Magnitude() const;
    TOSHI_API float MagnitudeSq() const;
    TOSHI_API bool IsEqual(const TVector2&) const;
    TOSHI_API void Divide(float);
    TOSHI_API void Divide(const TVector2&);
    TOSHI_API void Multiply(float);
    TOSHI_API void Multiply(const TVector2&);
    TOSHI_API void Subtract(const TVector2&);
    TOSHI_API void Add(const TVector2&);
    TOSHI_API void Negate();
    TOSHI_API void Abs();
    TOSHI_API void Divide(const TVector2&, float);
    TOSHI_API void Divide(const TVector2&, const TVector2&);
    TOSHI_API void Multiply(const TVector2&, float);
    TOSHI_API void Multiply(const TVector2&, const TVector2&);
    TOSHI_API void Subtract(const TVector2&, const TVector2&);
    TOSHI_API void Add(const TVector2&, const TVector2&);
    TOSHI_API void Negate(const TVector2&);
    TOSHI_API void Abs(const TVector2&);
    TOSHI_API void Set(const float*const);
    TOSHI_API TVector2 operator/(float) const;
    TOSHI_API TVector2 operator/(const TVector2&) const;
    TOSHI_API TVector2 operator*(float) const;
    TOSHI_API TVector2 operator*(const TVector2&) const;
    TOSHI_API TVector2 operator-(const TVector2&) const;
    TOSHI_API TVector2 operator+(const TVector2&) const;
    TOSHI_API static TVector2 const VEC_ZERO;
    TOSHI_API static TVector2 const VEC_POSX;
    TOSHI_API static TVector2 const VEC_POSY;
    TOSHI_API static TVector2 const VEC_NEGX;
    TOSHI_API static TVector2 const VEC_NEGY;
public:
    float x, y;
};

class TVector3
{
public:
#ifndef TVECTOR_IMPLICIT_COPY
    TVector3& operator=(const TVector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
#endif
    TOSHI_API float DotProduct(const TVector3&) const;
    void Set(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
    TOSHI_API bool operator!=(const TVector3&) const;
    TOSHI_API bool operator==(const TVector3&) const;
    TOSHI_API TVector3& operator/=(float);
    TOSHI_API TVector3& operator/=(const TVector3&);
    TOSHI_API TVector3& operator*=(float);
    TOSHI_API TVector3& operator*=(const TVector3&);
    TOSHI_API TVector3& operator-=(const TVector3&);
    TOSHI_API TVector3& operator+=(const TVector3&);
    TOSHI_API const float& operator()(unsigned int) const;
    TOSHI_API float& operator()(unsigned int);
    TOSHI_API TVector3(const float*const);
    TVector3(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
#ifndef TVECTOR_IMPLICIT_COPY
    TVector3(const TVector3& o) { x = o.x; y = o.y; z = o.z; }
#endif
    TVector3() {}
    TOSHI_API void Abs(const TVector3&);
    TOSHI_API void Add(const TVector3&, const TVector3&);
    TOSHI_API void Subtract(const TVector3&, const TVector3&);
    TOSHI_API void Multiply(const TVector3&, const TVector3&);
    TOSHI_API void Divide(const TVector3&, const TVector3&);
    TOSHI_API void Abs();
    TOSHI_API void Subtract(const TVector3&);
    TOSHI_API void Divide(const TVector3&);
    TOSHI_API void Normalise();
    TOSHI_API bool IsNormalised(float) const;
    TOSHI_API bool IsReasonable(float) const;
    TOSHI_API static float __stdcall DistanceSq(const TVector3&, const TVector3&);
    TOSHI_API static float __stdcall Distance(const TVector3&, const TVector3&);
    TOSHI_API void CrossProduct(const TVector3&, const TVector3&);
    TOSHI_API void Lerp(const TVector3&, const TVector3&, float);
    TOSHI_API void Lerp(const TVector3&, float);
    TOSHI_API void Clip(float, float);
    TOSHI_API void RotateX(float);
    TOSHI_API void RotateY(float);
    TOSHI_API void RotateZ(float);
    TOSHI_API float GetScalarProjectionOnUnit(TVector3&);
    TOSHI_API float GetScalarProjection(TVector3&);
    TOSHI_API void SetUnitVectorProjection(TVector3&);
    TOSHI_API void SetVectorProjection(TVector3&);
    TOSHI_API static float __stdcall DotProduct(const TVector3&, const TVector3&);
    TOSHI_API float Magnitude() const;
    TOSHI_API float MagnitudeSq() const;
    TOSHI_API bool IsEqual(const TVector3&) const;
    TOSHI_API void Divide(float);
    TOSHI_API void Multiply(float);
    TOSHI_API void Multiply(const TVector3&);
    TOSHI_API void Add(const TVector3&);
    TOSHI_API void Negate();
    TOSHI_API void Divide(const TVector3&, float);
    TOSHI_API void Multiply(const TVector3&, float);
    TOSHI_API void Negate(const TVector3&);
    TOSHI_API void Set(const float*const);
    TOSHI_API TVector3 operator/(float) const;
    TOSHI_API TVector3 operator/(const TVector3&) const;
    TOSHI_API TVector3 operator*(float) const;
    TOSHI_API TVector3 operator*(const TVector3&) const;
    TOSHI_API TVector3 operator-(const TVector3&) const;
    TOSHI_API TVector3 operator+(const TVector3&) const;
    TOSHI_API static TVector3 const VEC_ZERO;
    TOSHI_API static TVector3 const VEC_POSX;
    TOSHI_API static TVector3 const VEC_POSY;
    TOSHI_API static TVector3 const VEC_POSZ;
    TOSHI_API static TVector3 const VEC_NEGX;
    TOSHI_API static TVector3 const VEC_NEGY;
    TOSHI_API static TVector3 const VEC_NEGZ;
    TOSHI_API static TVector3 const VEC_POSXPOSZ;
    TOSHI_API static TVector3 const VEC_POSXNEGZ;
    TOSHI_API static TVector3 const VEC_NEGXPOSZ;
    TOSHI_API static TVector3 const VEC_NEGXNEGZ;
public:
    float x, y, z;
};

class TVector4
{
public:
#ifndef TVECTOR_IMPLICIT_COPY
    TVector4& operator=(const TVector4& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
#endif
    TOSHI_API const TVector3& AsVector3() const;
    TOSHI_API TVector3& AsVector3();
    TOSHI_API float DotProduct(const TVector4&) const;
    TOSHI_API float DotProduct4(const TVector4&) const;
    TOSHI_API float DotProduct3(const TVector4&) const;
    TOSHI_API void Lerp3(const TVector4&, float);
    TOSHI_API void Lerp(const TVector4&, float);
    TOSHI_API static float __stdcall DotProduct(const TVector4&, const TVector4&);
    TOSHI_API void Negate();
    TOSHI_API void Negate(const TVector4&);
    TOSHI_API void Set(const TVector3&);
    void Set(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }
    TOSHI_API bool operator!=(const TVector4&) const;
    TOSHI_API bool operator==(const TVector4&) const;
    TOSHI_API TVector4& operator/=(float);
    TOSHI_API TVector4& operator/=(const TVector4&);
    TOSHI_API TVector4& operator*=(float);
    TOSHI_API TVector4& operator*=(const TVector4&);
    TOSHI_API TVector4& operator-=(const TVector4&);
    TOSHI_API TVector4& operator+=(const TVector4&);
    TOSHI_API const float& operator()(unsigned int) const;
    TOSHI_API float& operator()(unsigned int);
    TOSHI_API TVector4(const float*const);
    TVector4(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }
#ifndef TVECTOR_IMPLICIT_COPY
    TVector4(const TVector4& o) { x = o.x; y = o.y; z = o.z; w = o.w; }
#endif
    TVector4() {}
    TOSHI_API void Set(const float*const);
    TOSHI_API void Abs(const TVector4&);
    TOSHI_API void Negate4(const TVector4&);
    TOSHI_API void Add(const TVector4&, const TVector4&);
    TOSHI_API void Subtract(const TVector4&, const TVector4&);
    TOSHI_API void Subtract4(const TVector4&, const TVector4&);
    TOSHI_API void Multiply(const TVector4&, const TVector4&);
    TOSHI_API void Multiply(const TVector4&, float);
    TOSHI_API void Divide(const TVector4&, const TVector4&);
    TOSHI_API void Divide(const TVector4&, float);
    TOSHI_API void Max(const TVector4&, const TVector4&);
    TOSHI_API void Max(const TVector4&, float);
    TOSHI_API void Min(const TVector4&, const TVector4&);
    TOSHI_API void Min(const TVector4&, float);
    TOSHI_API void Sin(const TVector4&);
    TOSHI_API void Cos(const TVector4&);
    TOSHI_API void Abs();
    TOSHI_API void Negate4();
    TOSHI_API void Subtract(const TVector4&);
    TOSHI_API void Multiply4(const TVector4&);
    TOSHI_API void Divide(const TVector4&);
    TOSHI_API void Max(const TVector4&);
    TOSHI_API void Max(float);
    TOSHI_API void Min(const TVector4&);
    TOSHI_API void Min(float);
    TOSHI_API bool IsEqual(const TVector4&) const;
    TOSHI_API void Normalise();
    TOSHI_API static float __stdcall DistanceSq(const TVector4&, const TVector4&);
    TOSHI_API static float __stdcall Distance(const TVector4&, const TVector4&);
    TOSHI_API void CrossProduct(const TVector4&, const TVector4&);
    TOSHI_API void Lerp(const TVector4&, const TVector4&, float);
    TOSHI_API void Lerp3(const TVector4&, const TVector4&, float);
    TOSHI_API void RotateX(float);
    TOSHI_API void RotateY(float);
    TOSHI_API void RotateZ(float);
    TOSHI_API static float __stdcall DotProduct4(const TVector4&, const TVector4&);
    TOSHI_API static float __stdcall DotProduct3(const TVector4&, const TVector4&);
    TOSHI_API float Magnitude() const;
    TOSHI_API float MagnitudeSq() const;
    TOSHI_API void Divide(float);
    TOSHI_API void Multiply(float);
    TOSHI_API void Multiply(const TVector4&);
    TOSHI_API void Add(const TVector4&);
    TOSHI_API void Negate3();
    TOSHI_API void Negate3(const TVector4&);
    TOSHI_API TVector4 operator/(float) const;
    TOSHI_API TVector4 operator/(const TVector4&) const;
    TOSHI_API TVector4 operator*(float) const;
    TOSHI_API TVector4 operator*(const TVector4&) const;
    TOSHI_API TVector4 operator-(const TVector4&) const;
    TOSHI_API TVector4 operator+(const TVector4&) const;
    TOSHI_API static TVector4 const VEC_ZERO;
    TOSHI_API static TVector4 const VEC_POSX;
    TOSHI_API static TVector4 const VEC_POSY;
    TOSHI_API static TVector4 const VEC_POSZ;
    TOSHI_API static TVector4 const VEC_NEGX;
    TOSHI_API static TVector4 const VEC_NEGY;
    TOSHI_API static TVector4 const VEC_NEGZ;
public:
    float x, y, z, w;
};

class TQuaternion
{
public:
#ifndef TVECTOR_IMPLICIT_COPY
    TQuaternion& operator=(const TQuaternion& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
#endif
    TOSHI_API void DebugPrint(const char*) const;
    TOSHI_API const TVector4& AsVector4() const;
    TOSHI_API TVector4& AsVector4();
    TOSHI_API void GetVectorDirection(TVector3&) const;
    TOSHI_API void Slerp(const TQuaternion&, float);
    TOSHI_EXPORT void SetInverse() { AsVector4().Negate3(); }
    TOSHI_EXPORT void SetConjugate() { AsVector4().Negate3(); }
    TOSHI_API void Normalise();
    TOSHI_API float Magnitude() const;
    TOSHI_API float MagnitudeSq() const;
    TOSHI_API void SetIdentity();
    void Set(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }
#ifndef TVECTOR_IMPLICIT_COPY
    TQuaternion(const TQuaternion& o) { x = o.x; y = o.y; z = o.z; w = o.w; }
#endif
    TOSHI_API TQuaternion(const TVector3&, float);
    TQuaternion(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }
    TQuaternion() {}
    TOSHI_API TQuaternion& operator*=(const TQuaternion&);
    TOSHI_API TQuaternion& operator*=(float);
    TOSHI_API TQuaternion& operator/=(const TQuaternion&);
    TOSHI_API TQuaternion& operator+=(const TQuaternion&);
    TOSHI_API TQuaternion& operator-=(const TQuaternion&);
    TOSHI_API bool operator==(const TQuaternion&) const;
    TOSHI_API bool operator!=(const TQuaternion&) const;
    TOSHI_API void RotateAroundAxis(const TVector3&, float);
    TOSHI_API void SetRotation(const TVector3&, float);
    TOSHI_API void Negate();
    TOSHI_API void MakePrincple();
    TOSHI_API void Slerp(const TQuaternion&, const TQuaternion&, float);
    TOSHI_API void Lerp(const TQuaternion&, const TQuaternion&, float);
    TOSHI_API static void __stdcall RotateVector(TVector3&, const TQuaternion&, const TVector3&);
    TOSHI_API static void __stdcall RotateVector(TVector4&, const TQuaternion&, const TVector4&);
    TOSHI_API void SetVectorDirection(const TVector3&, const TVector3&);
    TOSHI_API void GetEulerXYZ(float*) const;
    TOSHI_API void SetFromEulerYX(const float*);
    TOSHI_API void SetFromEulerRollPitchYaw(float, float, float);
    TOSHI_API static void __stdcall Divide(TQuaternion&, const TQuaternion&, const TQuaternion&);
    TOSHI_API static void __stdcall Multiply(TQuaternion&, const TQuaternion&, const TQuaternion&);
    TOSHI_API static void __stdcall Subtract(TQuaternion&, const TQuaternion&, const TQuaternion&);
    TOSHI_API static void __stdcall Add(TQuaternion&, const TQuaternion&, const TQuaternion&);
    TOSHI_API TQuaternion operator/(float) const;
    TOSHI_API TQuaternion operator/(const TQuaternion&) const;
    TOSHI_API TQuaternion operator*(float) const;
    TOSHI_API TQuaternion operator*(const TQuaternion&) const;
    TOSHI_API TQuaternion operator-(const TQuaternion&) const;
    TOSHI_API TQuaternion operator+(const TQuaternion&) const;
    TOSHI_API TQuaternion& operator/=(float);
    TOSHI_API static TVector3 const VEC3_ZERO_ROTATION;
    TOSHI_API static TQuaternion const IDENTITY;
    TOSHI_API static float const DELTA;
public:
    float x, y, z, w;
};

class TOSHI_EXPORT TPlane
{
public:
    // Return values of ComparePlane; the names are invented, the values are the constants in the binary.
    enum PlaneComparison { PLANE_NEGATIVE = -1, PLANE_CROSSING = 0, PLANE_POSITIVE = 1 };
    // Accessors first: the inline constructors and Set below inline them, as in the original.
    void SetD(float d) { m_oPlane.w = d; }
    float GetD() const { return m_oPlane.w; }
    void SetNormal(float x, float y, float z) { m_oPlane.x = x; m_oPlane.y = y; m_oPlane.z = z; }
    void SetNormal(const TVector3& n) { m_oPlane.x = n.x; m_oPlane.y = n.y; m_oPlane.z = n.z; }
    const TVector3& GetNormal() const { return *(const TVector3*)&m_oPlane; }
    const TVector3& AsNormal() const { return *(const TVector3*)&m_oPlane; }
    TVector3& AsNormal() { return *(TVector3*)&m_oPlane; }
    const TVector4& AsVector4() const { return m_oPlane; }
    TVector4& AsVector4() { return m_oPlane; }
    TPlane() {}
    TPlane(float x, float y, float z, float d) { m_oPlane.Set(x, y, z, d); }
    TPlane(const TVector4& v) { m_oPlane = v; }
    TPlane(const TVector3& n, float d) { SetNormal(n); SetD(d); }
    TOSHI_API TPlane(const TVector3& n, const TVector3& point);
    void Set(float x, float y, float z, float d) { m_oPlane.Set(x, y, z, d); }
    void Set(const TVector4& v) { m_oPlane = v; }
    void Set(const TVector3& n, float d) { SetNormal(n); SetD(d); }
    TOSHI_API void Set(const TVector3& n, const TVector3& point);
    void Set(const TPlane& p) { m_oPlane = p.m_oPlane; }
    TOSHI_API void Negate();
    TOSHI_API void Negate(const TPlane& p);
    TOSHI_API void SetPoint(const TVector3& point);     // d = normal . point
    TOSHI_API void GetPoint(TVector3& point) const;     // point = normal * d

    TVector4 m_oPlane;          // normal xyz, distance w
};

class TSphere
{
public:
    // No JPOG module imports TSphere's members except ComparePlane/Union (kernel code): the rest is inline.
    TOSHI_API void Union(TSphere&, TSphere&);
    TOSHI_API TPlane::PlaneComparison ComparePlane(TPlane&);
    TSphere() {}
    TSphere(const TVector4& v) { m_oSphere = v; }
    TSphere(const TVector3& c, float r) { m_oSphere.Set(c.x, c.y, c.z, r); }
    TSphere(float x, float y, float z, float r) { m_oSphere.Set(x, y, z, r); }
    // The kernel exports exactly these inline members (see TSphere.cpp).
    TOSHI_EXPORT void Set(const TSphere& s) { m_oSphere = s.m_oSphere; }
    TOSHI_EXPORT void Set(const TVector4& v) { m_oSphere = v; }
    TOSHI_EXPORT void Set(const TVector3& c, float r) { *(TVector3*)&m_oSphere = c; m_oSphere.w = r; }
    TOSHI_EXPORT void Set(float x, float y, float z, float r) { m_oSphere.Set(x, y, z, r); }
    TOSHI_EXPORT const TVector4& AsVector4() const { return m_oSphere; }
    TOSHI_EXPORT TVector4& AsVector4() { return m_oSphere; }
    const TVector3& GetOrigin() const { return *(const TVector3*)&m_oSphere; }
    float GetRadius() const { return m_oSphere.w; }

    TVector4 m_oSphere;         // origin xyz, radius w
};

class TOSHI_EXPORT TAABox
{
public:
    TOSHI_API TPlane::PlaneComparison ComparePlane(TPlane&);
    TOSHI_API void BoxUnion(TAABox*, unsigned int);
    TOSHI_API TAABox();
    TOSHI_API void SetBox(const float&, const float&, const float&, const float&, const float&, const float&);
    TOSHI_API void SetBounds(const TVector3&);
    TOSHI_API void SetCentre(const TVector3&);
    TOSHI_API const TVector3& GetBounds() const;
    TOSHI_API const TVector3& GetCentre() const;
    TOSHI_API TAABox& operator=(const TAABox&);
    TOSHI_API TAABox(const TAABox&);
    TOSHI_API TAABox(const float&, const float&, const float&, const float&, const float&, const float&);
    // imported inline: TDImp::BoneSpaceTransform builds one in place
    TOSHI_API TAABox(const TVector3& centre, const TVector3& bounds) : m_oCentre(centre), m_oBounds(bounds) {}
public:
    TVector3 m_oCentre;         // +0x00 (SetCentre / GetCentre)
    TVector3 m_oBounds;         // +0x0C (SetBounds / GetBounds)
};

class TMatrix44
{
public:
    TOSHI_API void Identity();
    TOSHI_API float Determinant4() const;
    TOSHI_API float Determinant() const;
    TOSHI_API bool Invert4(const TMatrix44&);
    TOSHI_API bool Invert(const TMatrix44&);
    TOSHI_API bool InvertArbitrary(const TMatrix44&);
    TOSHI_API void InvertOrthogonal(const TMatrix44&);
    TOSHI_API void Transpose(const TMatrix44&);
    TOSHI_API void Add(const TMatrix44&, const TMatrix44&);
    TOSHI_API void Subtract(const TMatrix44&, const TMatrix44&);
    TOSHI_API void Multiply(const TMatrix44&, const TMatrix44&);
    TOSHI_API void Multiply(const TMatrix44&, float);
    TOSHI_API void InvertOrthogonal();
    TOSHI_API void Multiply(const TMatrix44&);
    TOSHI_API bool IsEqual(const TMatrix44&) const;
    TOSHI_API bool IsOrthogonal() const;
    TOSHI_API bool IsOrthonormal() const;
    TOSHI_API bool IsReflected() const;
    TOSHI_API void Scale(float, float, float);
    TOSHI_API void Scale(const TVector4&);
    TOSHI_API void RotateX(float);
    TOSHI_API void RotateY(float);
    TOSHI_API void RotateZ(float);
    TOSHI_API void LookAtTarget(TVector3&, TVector3&);
    TOSHI_API void Translate(float, float, float);
    TOSHI_API static void __stdcall TransformVector(TVector3&, const TMatrix44&, const TVector3&);
    TOSHI_API static void __stdcall TransformVector(TVector4&, const TMatrix44&, const TVector4&);
    TOSHI_API static void __stdcall RotateVector(TVector3&, const TMatrix44&, const TVector3&);
    TOSHI_API static void __stdcall RotateVector(TVector4&, const TMatrix44&, const TVector4&);
    TOSHI_API static void __stdcall TransformPlane(TPlane&, const TMatrix44&, const TPlane&);
    TOSHI_API static void __stdcall TransformPlaneOrthogonal(TPlane&, const TMatrix44&, const TPlane&);
    TOSHI_API static void __stdcall MatToQuat(TQuaternion&, const TMatrix44&);
    TOSHI_API TMatrix44& SetFromQuaternion(const TQuaternion&);
    TOSHI_API TMatrix44& PushQuaternion(const TQuaternion&, const TMatrix44&, const TVector3&);
    TOSHI_API TPlane operator*(const TPlane&) const;
    TOSHI_API TVector4 operator*(const TVector4&) const;
    TOSHI_API TVector3 operator*(const TVector3&) const;
    TOSHI_API void GetTranslate(TVector4&) const;
    TOSHI_API void GetTranslate(TVector3&) const;
    TOSHI_API void SetTranslate(float, float, float);
    TOSHI_API void SetTranslate(const TVector4&);
    TOSHI_API void SetTranslate(const TVector3&);
    TOSHI_API void Translate(const TVector4&);
    TOSHI_API void Translate(const TVector3&);
    TOSHI_API void LookAtTarget(TVector3&);
    TOSHI_API void Rotate(float, float, float);
    TOSHI_API void Scale(float);
    TOSHI_API bool IsIdentity() const;
    TOSHI_API void Divide(float);
    TOSHI_API void Multiply(float);
    TOSHI_API void Subtract(const TMatrix44&);
    TOSHI_API void Add(const TMatrix44&);
    TOSHI_API bool Invert();
    TOSHI_API void Divide(const TMatrix44&, float);
    TOSHI_API TMatrix44 operator/(float) const;
    TOSHI_API TMatrix44 operator*(float) const;
    TOSHI_API TMatrix44 operator*(const TMatrix44&) const;
    TOSHI_API TMatrix44 operator-(const TMatrix44&) const;
    TOSHI_API TMatrix44 operator+(const TMatrix44&) const;
    // operator= and the copy constructor are inline memberwise copies (implicit)
    TOSHI_API void DebugPrint(const char*) const;
    // Row 'index' of the matrix (4 floats per row).
    TOSHI_API const TVector4& AsBasisVector4(int index) const { return ((const TVector4*)&m_f11)[index]; }
    TOSHI_API TVector4& AsBasisVector4(int index) { return ((TVector4*)&m_f11)[index]; }
    // The first three floats of row 'index'.
    TOSHI_API const TVector3& AsBasisVector3(int index) const { return *(const TVector3*)(&m_f11 + index * 4); }
    TOSHI_API TVector3& AsBasisVector3(int index) { return *(TVector3*)(&m_f11 + index * 4); }
    TOSHI_API void SetBasisVector4(int index, const TVector4& v)
    {
        TVector4& d = AsBasisVector4(index);
        d.x = v.x;
        d.y = v.y;
        d.z = v.z;
        d.w = v.w;
    }
    TOSHI_API void GetBasisVector4(int index, TVector4& v) const
    {
        const TVector4& s = AsBasisVector4(index);
        v.x = s.x;
        v.y = s.y;
        v.z = s.z;
        v.w = s.w;
    }
    TOSHI_API void SetBasisVector3(int index, const TVector3& v)
    {
        TVector3& d = AsBasisVector3(index);
        d.x = v.x;
        d.y = v.y;
        d.z = v.z;
    }
    TOSHI_API void GetBasisVector3(int index, TVector3& v) const
    {
        const TVector3& s = AsBasisVector3(index);
        v.x = s.x;
        v.y = s.y;
        v.z = s.z;
    }
    TOSHI_API void Set(float f11, float f12, float f13, float f14, float f21, float f22, float f23, float f24,
                       float f31, float f32, float f33, float f34, float f41, float f42, float f43, float f44)
    {
        m_f11 = f11; m_f12 = f12; m_f13 = f13; m_f14 = f14;
        m_f21 = f21; m_f22 = f22; m_f23 = f23; m_f24 = f24;
        m_f31 = f31; m_f32 = f32; m_f33 = f33; m_f34 = f34;
        m_f41 = f41; m_f42 = f42; m_f43 = f43; m_f44 = f44;
    }
    TOSHI_API bool operator!=(const TMatrix44& other) const { return !IsEqual(other); }
    TOSHI_API bool operator==(const TMatrix44& other) const { return IsEqual(other); }
    TOSHI_API TMatrix44& operator/=(float s) { Divide(s); return *this; }
    TOSHI_API TMatrix44& operator*=(float s) { Multiply(s); return *this; }
    TOSHI_API TMatrix44& operator*=(const TMatrix44& m) { Multiply(m); return *this; }
    TOSHI_API TMatrix44& operator-=(const TMatrix44& m) { Subtract(m); return *this; }
    TOSHI_API TMatrix44& operator+=(const TMatrix44& m) { Add(m); return *this; }
    TOSHI_API const float& operator()(unsigned int row, unsigned int col) const { return (&m_f11)[row * 4 + col]; }
    TOSHI_API float& operator()(unsigned int row, unsigned int col) { return (&m_f11)[row * 4 + col]; }
    // The original calls the out-of-line Set from here.
    TMatrix44(float f11, float f12, float f13, float f14, float f21, float f22, float f23, float f24,
              float f31, float f32, float f33, float f34, float f41, float f42, float f43, float f44)
    {
        Set(f11, f12, f13, f14, f21, f22, f23, f24, f31, f32, f33, f34, f41, f42, f43, f44);
    }

    TMatrix44() {}
    const TVector3& GetTranslation3() const { return *(const TVector3*)&m_f41; }
#ifdef TMAT_USER_COPY
    TMatrix44(const TMatrix44& m)
    {
        m_f11 = m.m_f11; m_f12 = m.m_f12; m_f13 = m.m_f13; m_f14 = m.m_f14;
        m_f21 = m.m_f21; m_f22 = m.m_f22; m_f23 = m.m_f23; m_f24 = m.m_f24;
        m_f31 = m.m_f31; m_f32 = m.m_f32; m_f33 = m.m_f33; m_f34 = m.m_f34;
        m_f41 = m.m_f41; m_f42 = m.m_f42; m_f43 = m.m_f43; m_f44 = m.m_f44;
    }
#endif
    TOSHI_API static TMatrix44 const IDENTITY;
    TOSHI_API static float const MAX_ORTHODEVIATION;
    TOSHI_API static float const QUATSCALAR;
public:
    float m_f11, m_f12, m_f13, m_f14;
    float m_f21, m_f22, m_f23, m_f24;
    float m_f31, m_f32, m_f33, m_f34;
    float m_f41, m_f42, m_f43, m_f44;
};

} // namespace Toshi
#endif
