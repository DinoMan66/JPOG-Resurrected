// Z:\Toshi\Source\TKernel\TMath.cpp - only the simple static members are written.
// Skipped: everything using inline x87 transcendental instructions, __int64 arithmetic or named float globals.
#include <math.h>
#include <stdlib.h>
#include <float.h>
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include "TVector.h"
#include "TKernelMisc.h"

namespace Toshi {

int __stdcall TMath::FastMod(int value, int modulus)
{
    return value & (modulus - 1);
}

int __stdcall TMath::BitShiftMod(int value, int shift)
{
    return value - ((value >> shift) << shift);
}

float __stdcall TMath::IntToFloat(int value)
{
    return (float)value;
}

float __stdcall TMath::IntToFloatRaw(int bits)
{
    return *(float*)&bits;
}

int __stdcall TMath::FloatToIntRaw(float value)
{
    return *(int*)&value;
}

float __stdcall TMath::Abs(float value)
{
    return (float)fabs(value);
}

unsigned int __stdcall TMath::Abs(unsigned int value)
{
    return abs((int)value);
}

int __stdcall TMath::Abs(int value)
{
    return abs(value);
}

float __stdcall TMath::Sqrt(float value)
{
    return (float)sqrt(value);
}

float __stdcall TMath::RSqrt(float value)
{
    return 1.0f / (float)sqrt(value);
}

float __stdcall TMath::Sin(float angle)
{
    return (float)sin(angle);
}

float __stdcall TMath::Cos(float angle)
{
    return (float)cos(angle);
}

float __stdcall TMath::Tan(float angle)
{
    return (float)tan(angle);
}

float __stdcall TMath::ATan2(float y, float x)
{
    return (float)atan2(y, x);
}

// Largest float below |value|'s bit pattern: the raw bits minus one.
float __stdcall TMath::ShrinkFloat(float value)
{
    return IntToFloatRaw(FloatToIntRaw(value) - 1);
}

float __stdcall TMath::Ceil(float value)
{
    return (float)CeilToInt(value);
}

float __stdcall TMath::Floor(float value)
{
    return (float)FloorToInt(value);
}

float __stdcall TMath::Trunc(float value)
{
    return (float)TruncToInt(value);
}

// The integer conversion rounds to nearest here, so the correction compares the value with the rounded result.
int __stdcall TMath::TruncToInt(float value)
{
    int rounded = (int)value;
    if (value >= 0.0f) {
        return rounded - (value < (float)rounded);
    }
    return rounded + (value > (float)rounded);
}

int __stdcall TMath::FloorToInt(float value)
{
    int rounded = (int)value;
    return rounded - (value < (float)rounded);
}

int __stdcall TMath::CeilToInt(float value)
{
    int rounded = (int)value;
    return rounded + (value > (float)rounded);
}

void __stdcall TMath::SinCos(float angle, float& sine, float& cosine)
{
    sine = (float)sin(angle);
    cosine = (float)cos(angle);
}

// Not written: FloatToInt, RoundToInt, Round, SetFPUControlWord, GetFPUControlWord. The original is
// hand-written FPU code (fist/fistp, fldcw/fnstcw) that cannot be expressed in plain C++.

// Two spheres overlap when the squared centre distance does not exceed the squared radius sum.
// depth is the penetration (radius sum - distance); offset is the centre-to-centre vector scaled by depth / radius sum.
bool __stdcall TMath::SphereIntersection(const TVector3& centreA, float radiusA, const TVector3& centreB, float radiusB,
                                         float* distanceSqMinusRadiusSq, TVector3* offset, float* depth)
{
    float penetration = 0.0f;
    float radiusSum = radiusB + radiusA;
    TVector3 delta;
    delta.Subtract(centreB, centreA);
    float radiusSumSq = radiusSum * radiusSum;
    float distanceSq = delta.MagnitudeSq();
    if (distanceSq <= radiusSumSq) {
        if (depth != 0) {
            penetration = radiusSum - (float)sqrt(distanceSq);
            *depth = penetration;
        }
        if (offset != 0) {
            if (depth == 0) {
                penetration = radiusSum - (float)sqrt(distanceSq);
            }
            offset->Multiply(delta, penetration / radiusSum);
        }
        if (distanceSqMinusRadiusSq != 0) {
            *distanceSqMinusRadiusSq = distanceSq - radiusB * radiusB;
        }
        return true;
    }
    return false;
}

// Same test on the ground plane (x and z only); the offset has no height component.
bool __stdcall TMath::SphereIntersectionPlanar(const TVector3& centreA, float radiusA, const TVector3& centreB, float radiusB,
                                               float* distanceSqMinusRadiusSq, TVector3* offset, float* depth)
{
    float radiusSum = radiusB + radiusA;
    float dx = centreB.x - centreA.x;
    float dz = centreB.z - centreA.z;
    float distanceSq = dz * dz + dx * dx;
    if (distanceSq <= radiusSum * radiusSum) {
        float penetration = 0.0f;
        if (depth != 0) {
            penetration = radiusSum - (float)sqrt(distanceSq);
            *depth = penetration;
        }
        if (offset != 0) {
            if (depth == 0) {
                penetration = radiusSum - (float)sqrt(distanceSq);
            }
            offset->x = dx * (penetration / radiusSum);
            offset->z = (penetration / radiusSum) * dz;
            offset->y = 0.0f;
        }
        if (distanceSqMinusRadiusSq != 0) {
            *distanceSqMinusRadiusSq = distanceSq - radiusB * radiusB;
        }
        return true;
    }
    return false;
}

// Intersects a ray with an infinite line; t is only updated when the hit is in front of the ray and closer than t.
bool __stdcall TMath::RaySegmentVsLine2D(const TVector2& rayOrigin, const TVector2& rayDirection, const TVector2& linePoint,
                                         const TVector2& lineDirection, float& t)
{
    float determinant = lineDirection.y * rayDirection.x - lineDirection.x * rayDirection.y;
    if (determinant != 0.0f) {
        TVector2 toLine = rayOrigin;
        toLine.Subtract(linePoint);
        float hit = (-toLine.x * lineDirection.y + lineDirection.x * toLine.y) / determinant;
        if (hit < t && 0.0f <= hit) {
            t = hit;
            return true;
        }
    }
    return false;
}

// Outward normal of a capsule (segment start-end) at a surface point: radial around the nearer end cap,
// perpendicular to the segment along its side.
void __stdcall TMath::CalculateCapsuleNormal2D(const TVector2& capsuleStart, const TVector2& capsuleEnd, const TVector2& point,
                                               TVector2& normal)
{
    float t = ClosestPointOnLine2D(capsuleStart, capsuleEnd, point);
    if (t < 0.0f) {
        normal = point;
        normal.Subtract(capsuleStart);
        normal.Normalise();
    } else if (t > 1.0f) {
        normal = point;
        normal.Subtract(capsuleEnd);
        normal.Normalise();
    } else {
        normal = capsuleEnd;
        normal.Subtract(capsuleStart);
        normal.Normalise();
        normal.SetPerpendicular();
        if (!PointVsPlane2D(normal, capsuleStart, point)) {
            normal.Negate();
        }
    }
}

// Intersection of a ray with a circle. Returns the number of hits (0 or 2) and the two ray parameters.
int __stdcall TMath::RayVsCircle2D(const TVector2& rayOrigin, const TVector2& rayDirection, const TVector2& centre, float radius,
                                   float& t0, float& t1)
{
    TVector2 toCentre = centre;
    toCentre.Subtract(rayOrigin);
    float radiusSq = radius * radius;
    float distanceSq = toCentre.MagnitudeSq();
    if (radiusSq <= distanceSq) {
        float along = TVector2::DotProduct(toCentre, rayDirection);
        if (along < 0.0f) {
            return 0;
        }
        if (radiusSq < distanceSq - along * along) {
            return 0;
        }
    }
    toCentre.Multiply(-1.0f);
    float b = TVector2::DotProduct(toCentre, rayDirection);
    float twoB = b + b;
    float discriminant = (distanceSq - radiusSq) * -4.0f + twoB * twoB;
    if (discriminant < 0.0f) {
        return 0;
    }
    float root = (float)sqrt(discriminant);
    t0 = -(root + twoB) * 0.5f;
    t1 = 0.5f * (root - twoB);
    return 2;
}

int __stdcall TMath::RayVsCircle3D(const TVector3& rayOrigin, const TVector3& rayDirection, const TVector3& centre, float radius,
                                   float& t0, float& t1)
{
    TVector3 toCentre = centre;
    toCentre.Subtract(rayOrigin);
    float radiusSq = radius * radius;
    float distanceSq = toCentre.MagnitudeSq();
    if (radiusSq <= distanceSq) {
        float along = TVector3::DotProduct(toCentre, rayDirection);
        if (along < 0.0f) {
            return 0;
        }
        if (radiusSq < distanceSq - along * along) {
            return 0;
        }
    }
    toCentre.Multiply(-1.0f);
    float b = TVector3::DotProduct(toCentre, rayDirection);
    float twoB = b + b;
    float discriminant = (distanceSq - radiusSq) * -4.0f + twoB * twoB;
    if (discriminant < 0.0f) {
        return 0;
    }
    float root = (float)sqrt(discriminant);
    t0 = -(root + twoB) * 0.5f;
    t1 = 0.5f * (root - twoB);
    return 2;
}

bool __stdcall TMath::PointInsideCapsule2D(const TVector2& capsuleStart, const TVector2& capsuleEnd, float radius,
                                           const TVector2& point)
{
    float t = ClosestPointOnLine2D(capsuleStart, capsuleEnd, point);
    Clip(t, 0.0f, 1.0f);
    TVector2 closest;
    closest.Lerp(capsuleStart, capsuleEnd, t);
    TVector2 delta = closest - point;
    return delta.MagnitudeSq() <= radius * radius;
}

// Intersects two infinite lines; s and t are the parameters along a->b and c->d of the crossing point.
bool __stdcall TMath::LineVsLine2D(const TVector2& a, const TVector2& b, const TVector2& c, const TVector2& d, float& s, float& t)
{
    TVector2 ab = b;
    TVector2 cd = d;
    ab.Subtract(a);
    cd.Subtract(c);
    float determinant = cd.y * ab.x - cd.x * ab.y;
    if (determinant != 0.0f) {
        TVector2 ca = a;
        ca.Subtract(c);
        float inverse = 1.0f / determinant;
        s = (cd.x * ca.y - cd.y * ca.x) * inverse;
        t = (ca.y * ab.x - ca.x * ab.y) * inverse;
        return true;
    }
    return false;
}

bool __stdcall TMath::LineSegmentVsLineSegment2D(const TVector2& a, const TVector2& b, const TVector2& c, const TVector2& d, TVector2& hit)
{
    float s;
    float t;
    if (LineVsLine2D(a, b, c, d, s, t) && 0.0f <= s && 0.0f <= t && s <= 1.0f && t <= 1.0f) {
        hit = b;
        hit.Subtract(a);
        hit.Multiply(s);
        hit.Add(a);
        return true;
    }
    return false;
}

float __stdcall TMath::ClosestPointOnLineOverTime2D(const TVector2& a, const TVector2& b, const TVector2& c, const TVector2& d, float time)
{
    TVector2 ab = b;
    ab.Subtract(a);
    TVector2 negated = ab;
    negated.Negate();
    float alongC = TVector2::DotProduct(c, negated);
    float denominator = ab.MagnitudeSq() * (alongC + time);
    TVector2 offset = a;
    offset.Subtract(d);
    offset.Subtract(b);
    float alongA = TVector2::DotProduct(a, offset);
    float alongB = TVector2::DotProduct(b, d);
    return (time * (alongB + alongA)) / denominator;
}

// Which part of a capsule a point lies in: 0 = start cap, 1 = middle, 2 = end cap.
int __stdcall TMath::GetCapsuleZone(const TVector2& point, const TVector2& start, const TVector2& end, float radius)
{
    TVector2 axis = end;
    axis.Subtract(start);
    if (PointVsPlane2D(axis, end, point)) {
        return 2;
    }
    if (!PointVsPlane2D(axis, start, point)) {
        return 1;
    }
    return 0;
}

int __stdcall TMath::Sign(int value)
{
    if (value > 0) {
        return 1;
    }
    if (value < 0) {
        return -1;
    }
    return 0;
}

void __stdcall TMath::Clip(int& value, int minimum, int maximum)
{
    if (value > maximum) {
        value = maximum;
    } else if (value < minimum) {
        value = minimum;
    }
}

void __stdcall TMath::Clip(float& value, float minimum, float maximum)
{
    if (value > maximum) {
        value = maximum;
    } else if (value < minimum) {
        value = minimum;
    }
}

float __stdcall TMath::DecrMinf(float value, float amount, float minimum)
{
    float result = value - amount;
    if (result < minimum) {
        result = minimum;
    }
    return result;
}

float __stdcall TMath::IncrMaxf(float value, float amount, float maximum)
{
    float result = value + amount;
    if (result > maximum) {
        result = maximum;
    }
    return result;
}

float __stdcall TMath::DistancePointToLine(const TVector2& p, const TVector2& a, const TVector2& b)
{
    return (float)sqrt(DistancePointToLineSq(p, a, b));
}

float __stdcall TMath::FMod(float a, float b)
{
    return (float)fmod(a, b);
}

bool __stdcall TMath::IsNaN(float value)
{
    if (!_isnan(value)) {
        return false;
    }
    return true;
}

bool __stdcall TMath::IsFinite(float value)
{
    if (!_finite(value)) {
        return false;
    }
    return true;
}

int __stdcall TMath::IntLog2(int value)
{
    float f = (float)value;
    return (*(int*)&f >> 23) - 127;
}

int __stdcall TMath::IntLog2Up(int value)
{
    float f = (float)(value * 2 - 1);
    return (*(int*)&f >> 23) - 127;
}

int __stdcall TMath::RoundUpPow2(int value)
{
    float f = (float)(value * 2 - 1);
    return 1 << ((*(int*)&f >> 23) - 127);
}

int __stdcall TMath::RoundDownPow2(int value)
{
    float f = (float)value;
    return 1 << ((*(int*)&f >> 23) - 127);
}

float __stdcall TMath::LERP(float a, float b, float t)
{
    return (1.0f - t) * a + b * t;
}


float __stdcall TMath::RadToDeg(float radians)
{
    return 180.0f / PI * radians;
}

float __stdcall TMath::DegToRad(float degrees)
{
    return PI * (1.0f / 180.0f) * degrees;
}


void __stdcall TMath::NormaliseAngle(float& angle)
{
    if (!(angle > PI)) {
        if (angle < -3.1415927f) {
            angle = (float)fmod((double)(angle - PI), 6.2831854820251465) + PI;
        }
    } else {
        angle = (float)fmod((double)(angle + PI), 6.2831854820251465) - PI;
    }
}

float __stdcall TMath::GetAngleDifference(float from, float to)
{
    float difference = to - from;
    if (fabs(difference) > PI) {
        float wrapped = 6.2831855f - (float)fabs(difference);
        if (difference > 0.0f) {
            wrapped = -wrapped;
        }
        return wrapped;
    }
    return difference;
}


float __stdcall TMath::LERPAngle(float from, float to, float t)
{
    if (fabs(to - from) > PI) {
        float step = (6.2831855f - (float)fabs(to - from)) * t;
        if (from <= to) {
            step = -step;
        }
        float result = step + from;
        NormaliseAngle(result);
        return result;
    }
    return (1.0f - t) * from + to * t;
}

bool __stdcall TMath::PointVsPlane2D(const TVector2& normal, const TVector2& origin, const TVector2& point)
{
    TVector2 offset = point;
    offset.Subtract(origin);
    if (0.0f <= TVector2::DotProduct(normal, offset)) {
        return true;
    }
    return false;
}

float __stdcall TMath::PointVsPlane2DF(const TVector2& normal, const TVector2& origin, const TVector2& point)
{
    TVector2 offset = point;
    offset.Subtract(origin);
    return TVector2::DotProduct(normal, offset);
}

bool __stdcall TMath::PointVsPlane3D(const TVector3& normal, const TVector3& origin, const TVector3& point)
{
    TVector3 offset = point;
    offset.Subtract(origin);
    if (0.0f <= TVector3::DotProduct(normal, offset)) {
        return true;
    }
    return false;
}


bool __stdcall TMath::LineVsLine2D(const TVector2& a, const TVector2& b, const TVector2& c, const TVector2& d, float& t)
{
    TVector2 e = b;
    TVector2 f = d;
    e.Subtract(a);
    f.Subtract(c);
    float determinant = f.y * e.x - f.x * e.y;
    if (determinant != 0.0f) {
        TVector2 g = a;
        g.Subtract(c);
        t = (f.x * g.y - f.y * g.x) / determinant;
        return true;
    }
    return false;
}

bool __stdcall TMath::LineVsLine2D(const TVector2& a, const TVector2& b, const TVector2& c, const TVector2& d, TVector2& hit)
{
    float t;
    bool found = LineVsLine2D(a, b, c, d, t);
    if (found == true) {
        hit.x = b.x;
        hit.y = b.y;
        hit.Subtract(a);
        hit.Multiply(t);
        hit.Add(a);
        return true;
    }
    return false;
}

bool __stdcall TMath::LineSegmentVsLine2D(const TVector2& a, const TVector2& b, const TVector2& c, const TVector2& d, TVector2& hit)
{
    float t;
    if (LineVsLine2D(a, b, c, d, t) == true && t >= 0.0f && t <= 1.0f) {
        hit = b;
        hit.Subtract(a);
        hit.Multiply(t);
        hit.Add(a);
        return true;
    }
    return false;
}

float __stdcall TMath::ClosestPointOnLine2D(const TVector2& p, const TVector2& a, const TVector2& b)
{
    TVector2 u = b;
    TVector2 v = a;
    u.Subtract(p);
    v.Subtract(p);
    float dot = TVector2::DotProduct(u, v);
    return dot / v.MagnitudeSq();
}

float __stdcall TMath::Sign(float value)
{
    if (0.0f < value)
    {
        return 1.0f;
    }
    if (value < 0.0f)
    {
        return -1.0f;
    }
    return 0.0f;
}

// The compiler brackets every libm call with the 53-bit precision control word (0x27f) itself.
float __stdcall TMath::Pow(float base, float exponent)
{
    return (float)pow(base, exponent);
}

float __stdcall TMath::Log(float value)
{
    return (float)log(value);
}

float __stdcall TMath::Exp(float value)
{
    return (float)exp(value);
}

float __stdcall TMath::ATan(float value)
{
    return (float)atan(value);
}

float __stdcall TMath::ACos(float value)
{
    return (float)acos(value);
}

float __stdcall TMath::ASin(float value)
{
    return (float)asin(value);
}

// Signed angle from 'from' to 'to'; when the plain difference has the wrong sign for the requested
// direction the other way round the circle is returned.
float __stdcall TMath::GetDirectedAngleDifference(float from, float to, bool positive)
{
    float difference = to - from;
    if ((difference >= 0.0f) == positive)
    {
        return difference;
    }
    float wrapped = 6.2831855f - (float)fabs(difference);
    if (difference > 0.0f)
    {
        wrapped = -wrapped;
    }
    return wrapped;
}

// Symmetric bias curve: the lower half is a biased ramp, the upper half its mirror image.
float __stdcall TMath::Gain(float bias, float t)
{
    if (t < 0.5f)
    {
        return 0.5f * Bias(1.0f - bias, t + t);
    }
    return -0.5f * Bias(1.0f - bias, 2.0f - (t + t)) + 1.0f;
}

// Not written: Gain075 and Bias - they call libm, and the original brackets each libm call with the
// 53-bit precision control word (0x27f), which this build does not emit for plain pow/log calls.

float __stdcall TMath::DistancePointToLineSq(const TVector2& point, const TVector2& lineStart, const TVector2& lineEnd)
{
    TVector2 toPoint = point;
    TVector2 line = lineEnd;
    toPoint.Subtract(lineStart);
    line.Subtract(lineStart);
    float t = TVector2::DotProduct(toPoint, line) / line.MagnitudeSq();
    TVector2 closest = line;
    closest.Multiply(t);
    closest.Add(lineStart);
    closest.Subtract(point);
    return closest.MagnitudeSq();
}

} // namespace Toshi
