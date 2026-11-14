// TMath, TBitArray and TRandom - kernel-internal declarations (no other Toshi DLL source uses them yet).
// Member lists follow the export table; only the members implemented in the .cpp files are used here.
#ifndef TKERNELMISC_H
#define TKERNELMISC_H

namespace Toshi {

template <class T>
inline const T& Min(const T& a, const T& b)
{
    return a < b ? a : b;
}

class TVector2;
class TVector3;

class __declspec(dllexport) TMath
{
public:
    static int __stdcall FastMod(int value, int modulus);          // modulus is a power of two
    static int __stdcall BitShiftMod(int value, int shift);
    static float __stdcall IntToFloat(int value);
    static int __stdcall FloatToInt(float value);
    static float __stdcall IntToFloatRaw(int bits);
    static int __stdcall FloatToIntRaw(float value);
    static float __stdcall Abs(float value);
    static unsigned int __stdcall Abs(unsigned int value);
    static int __stdcall Abs(int value);
    static float __stdcall Sqrt(float value);
    static float __stdcall RSqrt(float value);
    static float __stdcall Sin(float angle);
    static float __stdcall Cos(float angle);
    static float __stdcall Tan(float angle);
    static float __stdcall ATan2(float y, float x);
    static float __stdcall Round(float value);
    static float __stdcall Ceil(float value);
    static float __stdcall Floor(float value);
    static float __stdcall Trunc(float value);
    static int __stdcall CeilToInt(float value);
    static int __stdcall FloorToInt(float value);
    static int __stdcall TruncToInt(float value);
    static float __stdcall Pow(float base, float exponent);
    static float __stdcall Log(float value);
    static float __stdcall Exp(float value);
    static float __stdcall ATan(float value);
    static float __stdcall ACos(float value);
    static float __stdcall ASin(float value);
    static float __stdcall ShrinkFloat(float value);
    static int __stdcall RoundToInt(float value);
    static void __stdcall SetFPUControlWord(unsigned short controlWord);
    static unsigned short __stdcall GetFPUControlWord();
    static int __stdcall Sign(int value);
    static float __stdcall Sign(float value);
    static void __stdcall Clip(int& value, int minimum, int maximum);
    static void __stdcall Clip(float& value, float minimum, float maximum);
    static float __stdcall DecrMinf(float value, float amount, float minimum);
    static float __stdcall IncrMaxf(float value, float amount, float maximum);
    static float __stdcall DistancePointToLineSq(const TVector2& p, const TVector2& a, const TVector2& b);
    static float __stdcall DistancePointToLine(const TVector2& p, const TVector2& a, const TVector2& b);
    static float __stdcall FMod(float a, float b);
    static bool __stdcall IsNaN(float value);
    static bool __stdcall IsFinite(float value);
    static int __stdcall RoundUpPow2(int value);
    static int __stdcall RoundDownPow2(int value);
    static int __stdcall IntLog2Up(int value);
    static int __stdcall IntLog2(int value);
    static float __stdcall LERPAngle(float from, float to, float t);
    static bool __stdcall PointVsPlane2D(const TVector2& normal, const TVector2& origin, const TVector2& point);
    static float __stdcall PointVsPlane2DF(const TVector2& normal, const TVector2& origin, const TVector2& point);
    static bool __stdcall PointVsPlane3D(const TVector3& normal, const TVector3& origin, const TVector3& point);
    static bool __stdcall LineVsLine2D(const TVector2& a, const TVector2& b, const TVector2& c, const TVector2& d, float& t);
    static bool __stdcall LineVsLine2D(const TVector2& a, const TVector2& b, const TVector2& c, const TVector2& d, TVector2& hit);
    static bool __stdcall LineSegmentVsLine2D(const TVector2& a, const TVector2& b, const TVector2& c, const TVector2& d, TVector2& hit);
    static float __stdcall ClosestPointOnLine2D(const TVector2& p, const TVector2& a, const TVector2& b);
    static void __stdcall NormaliseAngle(float& angle);
    static float __stdcall GetAngleDifference(float from, float to);
    static float __stdcall GetDirectedAngleDifference(float from, float to, bool positive);
    static bool __stdcall SphereIntersection(const TVector3& centreA, float radiusA, const TVector3& centreB, float radiusB, float* distanceSqMinusRadiusSq, TVector3* offset, float* depth);
    static bool __stdcall SphereIntersectionPlanar(const TVector3& centreA, float radiusA, const TVector3& centreB, float radiusB, float* distanceSqMinusRadiusSq, TVector3* offset, float* depth);
    static bool __stdcall RaySegmentVsLine2D(const TVector2& rayOrigin, const TVector2& rayDirection, const TVector2& linePoint, const TVector2& lineDirection, float& t);
    static void __stdcall CalculateCapsuleNormal2D(const TVector2& capsuleStart, const TVector2& capsuleEnd, const TVector2& point, TVector2& normal);
    static bool __stdcall PointInsideCapsule2D(const TVector2& capsuleStart, const TVector2& capsuleEnd, float radius, const TVector2& point);
    static int __stdcall RayVsCircle2D(const TVector2& rayOrigin, const TVector2& rayDirection, const TVector2& centre, float radius, float& t0, float& t1);
    static int __stdcall RayVsCircle3D(const TVector3& rayOrigin, const TVector3& rayDirection, const TVector3& centre, float radius, float& t0, float& t1);
    static bool __stdcall LineVsLine2D(const TVector2& a, const TVector2& b, const TVector2& c, const TVector2& d, float& s, float& t);
    static bool __stdcall LineSegmentVsLineSegment2D(const TVector2& a, const TVector2& b, const TVector2& c, const TVector2& d, TVector2& hit);
    static float __stdcall ClosestPointOnLineOverTime2D(const TVector2& a, const TVector2& b, const TVector2& c, const TVector2& d, float time);
    static void __stdcall SinCos(float angle, float& sine, float& cosine);
    static float __stdcall LERP(float a, float b, float t);
    static float __stdcall RadToDeg(float radians);
    static float __stdcall DegToRad(float degrees);

    static float __stdcall Gain(float bias, float t);

    static const float PI;

private:
    static float __stdcall Bias(float bias, float t);
    static int __stdcall GetCapsuleZone(const TVector2& point, const TVector2& start, const TVector2& end, float radius);
};

typedef unsigned short TSysWChar;

class TCString;
class TCStringPool;
class TWStringPool;
class TLocale;

// Local wall-clock time as returned by TSystem::GetLocalTime (month is the C runtime's 0-based value).
struct __declspec(dllexport) TDateTime
{
    // Packs the date as year/month/day and the time as hour/minute/second into two words and back.
    void Pack(unsigned int& date, unsigned int& time);
    void UnPack(unsigned int& date, unsigned int& time);

    unsigned short year;
    unsigned char month;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
    unsigned char day;
};

class __declspec(dllexport) TSystem
{
public:
    static bool __stdcall GetLocalTime(TDateTime& dateTime);
    static void __stdcall StringFormatDateTime(const TDateTime& dateTime, TCString& result);
    static TSysWChar* __stdcall GetTempWString();
    static char* __stdcall GetTempCString() { return (char*)ms_aScratchMem; }
    static unsigned char* __stdcall GetScratchMem();
    static const char* __stdcall StringFindChar(const char* s, char c);
    static unsigned int __stdcall HashString(const char* s);
    static unsigned int __stdcall BCDToInteger(unsigned int value);
    static const TSysWChar* __stdcall StringFindChar(const TSysWChar* s, TSysWChar c);
    static unsigned int __stdcall HashString(const TSysWChar* s);
    static int __cdecl StringFormat(TSysWChar* buffer, const TSysWChar* fmt, ...);
    static int __stdcall StringLength(const TSysWChar* s);
    static const TSysWChar* __stdcall StringCopy(TSysWChar* dst, const TSysWChar* src, int count);
    static int __stdcall StringCompareNoCase(const TSysWChar* a, const TSysWChar* b, int count);
    static int __stdcall StringCompare(const TSysWChar* a, const TSysWChar* b, int count);
    static int __cdecl StringFormat(char* buffer, const char* fmt, ...);
    static int __stdcall StringLength(const char* s);
    static const char* __stdcall StringCopy(char* dst, const char* src, int count);
    static int __stdcall StringCompareNoCase(const char* a, const char* b, int count);
    static int __stdcall StringCompare(const char* a, const char* b, int count);
    static const TSysWChar* __stdcall StringCharToUnicode(TSysWChar* dst, const char* src, int count);
    static const char* __stdcall StringUnicodeToChar(char* dst, const TSysWChar* src, int count);
    static const char* __stdcall StringIntToString(int value, char* buffer, int radix);
    static void* __stdcall MemSet(void* dst, int value, int count);
    static void* __stdcall MemCopy(void* dst, const void* src, unsigned int count);

    static TCStringPool* __stdcall CreateCStringPoolExplicit(int a, int b);
    static TCStringPool* __stdcall CreateCStringPoolExplicit(const char* name, int a, int b);
    static TCStringPool* __stdcall GetCStringPool();
    static TLocale* __stdcall GetLocale();
    static TWStringPool* __stdcall GetWStringPool();

    static unsigned char ms_aScratchMem[0x400];

private:
    static TLocale* ms_poLocale;
    static TWStringPool* ms_poTWStringPool;
    static TCStringPool* ms_poTCStringPool;
};

class __declspec(dllexport) TBitArray
{
public:
    TBitArray();
    TBitArray(int size, int initialValue);
    ~TBitArray();
    bool Create(int size, int initialValue);
    void Reset();
    void SetBit(int index, int value);
    void Destroy();
    void ToggleBit(int index);
    void ClearBit(int index);
    void SetBit(int index);
    int GetBit(int index);

    unsigned int* m_pBuffer;    // +0
    int m_iSize;                // +4
    unsigned int m_uFill;       // +8 (all ones or zero)
};

class __declspec(dllexport) TRandom
{
public:
    TRandom();
    ~TRandom();
    int GetInt();
    int GetInt(int range);
    int GetInt(int minimum, int maximum);
    float GetFloat();
    float GetFloat2();
    float GetFloatMinMax(float minimum, float maximum);
    float GetFloatMinRange(float minimum, float range);
    unsigned int GetSeed();
    void SetSeed(unsigned int seed);

private:
    void Isaac();
    void RandInit();
    unsigned int RandRaw();

    unsigned int m_uSeed;       // +0
    int m_iCount;               // +4
    unsigned int m_aResult[16]; // +8
    unsigned int m_aMemory[16]; // +0x48 ISAAC internal state
    unsigned int m_uAccumulator;// +0x88
    unsigned int m_uLastResult; // +0x8c
    unsigned int m_uCounter;    // +0x90 (total size 0x94)
};

} // namespace Toshi
#endif
