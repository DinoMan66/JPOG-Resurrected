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

// Not written: FloatToInt, RoundToInt, Round, SetFPUControlWord, GetFPUControlWord. The original is
// hand-written FPU code (fist/fistp, fldcw/fnstcw) that cannot be expressed in plain C++.

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
