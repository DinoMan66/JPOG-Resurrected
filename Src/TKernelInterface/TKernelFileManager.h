// TFileManager and TNativeFileSystem - kernel-internal declarations.
// TFileManager layout (from the constructor): path-valid flag (+0), system path (+4), working directory (+0xC),
// two lists of file systems (+0x14, +0x1C) and a mutex (+0x24).
#ifndef TKERNELFILEMANAGER_H
#define TKERNELFILEMANAGER_H
#include "TKernelFiles.h"
#include "TKernelThreads.h"

namespace Toshi {

class __declspec(dllexport) TFileManager
{
public:
    class __declspec(dllexport) TSysPathIter
    {
    public:
        TSysPathIter(const TCString& path);
        TSysPathIter(const TSysPathIter& other);
        bool First(TCString& result);
        bool Next(TCString& result);

    private:
        const TCString* m_pPath;    // +0x00
        int m_iPosition;            // +0x04
    };

    TFileManager();
    ~TFileManager();
    static TFileManager* __stdcall GetFileManager();
    TFile* CreateFile(const TCString& path, unsigned int flags);
    void DestroyFile(TFile* file);
    void MountFileSystem(TFileSystem* fileSystem);
    void UnmountFileSystem(TFileSystem* fileSystem);
    void SetWorkingDirectory(const TCString& directory);
    const TCString& GetWorkingDirectory() const;
    void SetSystemPath(const TCString& path);
    const TCString& GetSystemPath() const;
    TCString MakeAbsolutePath(const TCString& path) const;
    void FileSystemRelease();
    void FileSystemWait();
    TFileSystem* FindFileSystem(const TCString& name);

private:
    friend class TNativeFileSystem;
    friend class TFile;
    friend class TNullFileSystem;
    friend class TMemFile;
    friend class TMemFileSystem;
    friend class TISOFileSystem;

    void InvalidateSystemPath();
    void ValidateSystemPath();

    bool m_bSystemPathValid;                // +0x00
    TCString m_oSystemPath;                 // +0x04
    TCString m_oWorkingDirectory;           // +0x0C
    TGenericDList m_oPrefixedSystems;       // +0x14
    TGenericDList m_oMountedSystems;        // +0x1C
    TMutex m_oMutex;                        // +0x24
    static TFileManager* s_pFileManager;
};

class __declspec(dllexport) TNativeFileSystem : public TFileSystem
{
public:
    TNativeFileSystem(const char* name);
    virtual ~TNativeFileSystem();
    virtual TFile* CreateFile(const TCString& path, unsigned int flags);
    virtual void DestroyFile(TFile* file);
    virtual bool RemoveFile(const TCString& path);
    virtual TCString MakeInternalPath(const TCString& path) const;
    virtual bool GetFirstFile(const TCString& pattern, TCString& result, unsigned int flags);
    virtual bool GetNextFile(TCString& result, unsigned int flags);
    virtual bool MakeDirectory(const TCString& path);

private:
    void* m_hFind;                          // +0x1C
};

// File system that accepts everything and stores nothing; there is one instance, remembered in s_pFileSystem.
class __declspec(dllexport) TNullFileSystem : public TFileSystem
{
public:
    TNullFileSystem(const char* name);
    virtual ~TNullFileSystem();
    virtual TFile* CreateFile(const TCString& path, unsigned int flags);
    virtual void DestroyFile(TFile* file);
    virtual TCString MakeInternalPath(const TCString& path) const;
    static TNullFileSystem* __stdcall GetNullFileSystem();

private:
    static TNullFileSystem* s_pFileSystem;
};

// In-memory files: every file is a copy of a file read through a parent file system ("local").
class __declspec(dllexport) TMemFileSystem : public TFileSystem
{
public:
    TMemFileSystem(const char* name);
    virtual ~TMemFileSystem();
    virtual TFile* CreateFile(const TCString& path, unsigned int flags);
    virtual void DestroyFile(TFile* file);
    virtual TCString MakeInternalPath(const TCString& path) const;
    TFile* CreateFile(TFile* source);

private:
    TFileSystem* m_pParent;                 // +0x1C
};

// Buffered Win32 file. Reads go through a 0x800 byte block cache, writes through a write buffer.
class __declspec(dllexport) TNativeFile : public TFile
{
public:
    virtual int Read(void* buffer, int size);
    virtual int Write(const void* buffer, int size);
    virtual bool Seek(int offset, TSEEK origin);
    virtual int Tell();
    virtual int GetSize();
    virtual unsigned __int64 GetDate();
    virtual int GetCChar();
    virtual int GetWChar();
    virtual int PutCChar(char c);
    virtual int PutWChar(TWChar c);
    virtual int VCPrintf(const char* format, char* args);
    virtual int VWPrintf(const TWChar* format, char* args);

    TNativeFileSystem* GetFileSystem() const { return (TNativeFileSystem*)m_pFileSystem; }

protected:
    TNativeFile(TNativeFileSystem* fileSystem);
    virtual ~TNativeFile();

    bool Open(const TCString& path, unsigned int flags);
    void Close();

private:
    friend class TNativeFileSystem;

    int ReadUnbuffered(void* buffer, int size);
    bool LoadBuffer(int offset);
    int FlushWriteBuffer();

    void* m_hFile;                          // +0x08
    int m_iPosition;                        // +0x0C
    int m_iFilePointer;                     // +0x10
    int m_iBufferStart;                     // +0x14
    int m_iBufferLength;                    // +0x18
    unsigned char* m_pReadBuffer;           // +0x1C
    unsigned char* m_pWriteBuffer;          // +0x20
    int m_iWriteLength;                     // +0x24
    bool m_bBuffered;                       // +0x28
};

} // namespace Toshi
#endif
