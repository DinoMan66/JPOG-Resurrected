// TISOFileSystem (ISO9660 helper structs), TKernelInterface and TScheduler - kernel-internal declarations.
// Only the members touched by the accessors in TKernelSystem.cpp are named; everything else is padding.
// TKernelInterface and TScheduler are TObject-derived: their first dword is the vtable pointer (m_pVTable here,
// because the object machinery is not reconstructed yet).
#ifndef TKERNELSYSTEM_H
#define TKERNELSYSTEM_H
#include "TKernelObject.h"
#include "TKernelFiles.h"
#include "TKernelThreads.h"

struct HINSTANCE__;

namespace Toshi {

class TScheduler;
class TTask;
class TKernelInterface;

class __declspec(dllexport) TISOFileSystem : public TFileSystem
{
public:
    class __declspec(dllexport) ISO9660PVD
    {
    public:
        ISO9660PVD();
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
    virtual TFile* CreateFile(const TCString& path, unsigned int flags);
    virtual void DestroyFile(TFile* file);
    bool GetSubISOFile(TISOFile* file, const TCString& path);
    TFile* GetISOFile();
    const ISO9660PVD& GetPVD();

private:
    friend class TISOFile;

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
    bool Update();
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
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);

    void* m_pVTable;                        // +0x00
    char m_aPad04[4];                       // +0x04
    THPTimer m_oSystemTimer;                // +0x08
    TScheduler* m_pScheduler;               // +0x30
    char m_aPad34[0x10];                    // +0x34
    float m_fFPSTimer;                      // +0x44 (seconds since the average was last updated)
    float m_fAverageFPS;                    // +0x48
    char m_aPad4C[4];                       // +0x4C
    HINSTANCE__* m_hInstance;               // +0x50
    bool m_bPaused;                         // +0x54
};

class __declspec(dllexport) TScheduler : public TObject
{
public:
    TScheduler(TKernelInterface* kernelInterface);
    virtual TClass& GetClass() const;

    void Update();
    void DestroyTask(TTask& task);
    void DestroyAllTasks();
    void DestroyDyingTasks(TTask* task);
    void SetDebugSlowTime(bool slow);
    void UpdateKernelPaused();
    void Debug_PrintTaskTree() const;
    int GetFrameCount();
    float GetTotalTime();
    float GetCurrentTimeDelta();
    TKernelInterface* GetKernelInterface();

    static TClass m_sClass;

private:
    template <class T> friend class TRef;

    void UpdateActiveTasks(TTask* task);
    void UpdateActiveTasksKernelPaused(TTask* task);
    void DestroyTaskRecurse(TTask* task);
    void DeleteTaskRecurse(TTask* task);
    void DeleteTaskAtomic(TTask* task);
    void DeleteTask(TTask* task);

    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();

    int m_refCount;                         // +0x04 (the two list pointers below point here while the list is empty)
    TKernelInterface* m_pKernelInterface;   // +0x08
    int m_unk0C;                            // +0x0C
    int* m_unk10;                           // +0x10
    int* m_unk14;                           // +0x14
    int m_unk18;                            // +0x18
    TTask* m_pRootTask;                     // +0x1C
    int m_unk20;                            // +0x20
    float m_fTimeDelta;                     // +0x24
    float m_fTotalTime;                     // +0x28
    float m_fDebugSlowTime;                 // +0x2C (1.0, or 0.01 while the slow-time debug mode is on)
    int m_iFrameCount;                      // +0x30
};

} // namespace Toshi
#endif
