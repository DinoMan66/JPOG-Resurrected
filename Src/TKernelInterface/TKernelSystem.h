// TISOFileSystem (ISO9660 helper structs), TKernelInterface and TScheduler - kernel-internal declarations.
// Only the members touched by the accessors in TKernelSystem.cpp are named; everything else is padding.
// TKernelInterface and TScheduler are TObject-derived: their first dword is the vtable pointer (m_pVTable here,
// because the object machinery is not reconstructed yet).
#ifndef TKERNELSYSTEM_H
#define TKERNELSYSTEM_H
#include "TKernelFiles.h"
#include "TKernelThreads.h"

struct HINSTANCE__;

namespace Toshi {

class TScheduler;
class TKernelInterface;

class __declspec(dllexport) TISOFileSystem : public TFileSystem
{
public:
    class __declspec(dllexport) ISO9660PVD
    {
    public:
        unsigned int GetPathTableBytePos() const;
        unsigned int GetBytePos(unsigned int sector) const;
        unsigned int GetPathTableSize() const;
        const char* GetBibliographicFileID() const;
        const char* GetAbstractFileID() const;
        const char* GetCopyrightFileID() const;
        const char* GetVolumeSetID() const;
        const char* GetVolumeID() const;

    private:
        char m_aPad0[6];                    // +0x00
        char m_acVolumeID[0x20];            // +0x06
        char m_acVolumeSetID[0xA8];         // +0x26
        unsigned short m_uSectorSize;       // +0xCE
        char m_aPadD0[4];                   // +0xD0
        unsigned int m_uPathTableSize;      // +0xD4
        char m_aPadD8[4];                   // +0xD8
        unsigned short m_uPathTablePos;     // +0xDC
        char m_aPadDE[6];                   // +0xDE
    };

    class __declspec(dllexport) ISO9660File
    {
    public:
        unsigned int GetLength() const;
        unsigned int GetLocation() const;
        const char* GetName() const;

    private:
        unsigned int m_uLocation;           // +0x00
        unsigned int m_uPad4;               // +0x04
        unsigned int m_uLength;             // +0x08
        unsigned int m_uPadC;               // +0x0C
        char m_acName[0x24];                // +0x10
    };

    class __declspec(dllexport) ISO9660Directory
    {
    public:
        ISO9660Directory();
        ~ISO9660Directory();
        const char* GetName() const;
        void SetSubDirs(ISO9660Directory* subDirs, unsigned char count);

    private:
        unsigned int m_uLocation;           // +0x00 first sector of the directory's extent
        ISO9660Directory* m_pSubDirs;       // +0x04
        unsigned char m_ucSubDirCount;      // +0x08
        ISO9660File* m_pFiles;              // +0x0C (tmalloc'd by ReadFileList)
        int m_iFileCount;                   // +0x10 (-1 until the file list has been read)
        char m_acName[0x24];                // +0x14
    };

    virtual ~TISOFileSystem();
    TFile* GetISOFile();
    const ISO9660PVD& GetPVD();

private:
    ISO9660PVD m_oPVD;                      // +0x1C
    TFile* m_pISOFile;                      // +0x100
    ISO9660Directory* m_pDirectories;       // +0x104 (one entry per path table record)
    int m_iDirectoryCount;                  // +0x108
};

inline TISOFileSystem* TISOFile::GetFileSystem() const
{
    return (TISOFileSystem*)m_pFileSystem;
}

class __declspec(dllexport) TKernelInterface
{
public:
    bool Pause(bool pause);
    bool IsPaused();
    TScheduler* GetScheduler() const;
    HINSTANCE__* GetInstance();
    void SetInstance(HINSTANCE__* instance);
    float GetAverageFPS();
    float GetFPS();
    THPTimer* GetSystemTimer();

private:
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();

    void* m_pVTable;                        // +0x00
    char m_aPad04[4];                       // +0x04
    THPTimer m_oSystemTimer;                // +0x08
    TScheduler* m_pScheduler;               // +0x30
    char m_aPad34[0x14];                    // +0x34
    float m_fAverageFPS;                    // +0x48
    char m_aPad4C[4];                       // +0x4C
    HINSTANCE__* m_hInstance;               // +0x50
    bool m_bPaused;                         // +0x54
};

class __declspec(dllexport) TScheduler
{
public:
    int GetFrameCount();
    float GetTotalTime();
    float GetCurrentTimeDelta();
    TKernelInterface* GetKernelInterface();

private:
    void* m_pVTable;                        // +0x00
    char m_aPad04[4];                       // +0x04
    TKernelInterface* m_pKernelInterface;   // +0x08
    char m_aPad0C[0x18];                    // +0x0C
    float m_fTimeDelta;                     // +0x24
    float m_fTotalTime;                     // +0x28
    char m_aPad2C[4];                       // +0x2C
    int m_iFrameCount;                      // +0x30
};

} // namespace Toshi
#endif
