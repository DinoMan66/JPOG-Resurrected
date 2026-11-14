// Z:\Toshi\Source\TKernel\TISOFileSystem.cpp, TKernelInterface.cpp, TScheduler.cpp - accessors, the ISO directory records and the file system destructor.
#define TOSHI_API __declspec(dllexport)
#include "TKernelSystem.h"
#include "TKernelFileManager.h"
#include "TKernelFiles.h"
#include "TMemory.h"
#include "TNewDelete.h"

namespace Toshi {

// ---- TISOFileSystem
TISOFileSystem::ISO9660PVD::ISO9660PVD()
{
}

unsigned int TISOFileSystem::ISO9660PVD::GetPathTableBytePos() const
{
    return m_uPathTablePos * m_uSectorSize;
}

unsigned int TISOFileSystem::ISO9660PVD::GetBytePos(unsigned int sector) const
{
    return m_uSectorSize * sector;
}

unsigned int TISOFileSystem::ISO9660PVD::GetPathTableSize() const
{
    return m_uPathTableSize;
}

// The original returns the same address (+6) for these three and for the volume ID.
const char* TISOFileSystem::ISO9660PVD::GetBibliographicFileID() const
{
    return m_acVolumeID;
}

const char* TISOFileSystem::ISO9660PVD::GetAbstractFileID() const
{
    return m_acVolumeID;
}

const char* TISOFileSystem::ISO9660PVD::GetCopyrightFileID() const
{
    return m_acVolumeID;
}

const char* TISOFileSystem::ISO9660PVD::GetVolumeSetID() const
{
    return m_acVolumeSetID;
}

const char* TISOFileSystem::ISO9660PVD::GetVolumeID() const
{
    return m_acVolumeID;
}

unsigned int TISOFileSystem::ISO9660File::GetLength() const
{
    return m_uLength;
}

unsigned int TISOFileSystem::ISO9660File::GetLocation() const
{
    return m_uLocation;
}

const char* TISOFileSystem::ISO9660File::GetName() const
{
    return m_acName;
}

const char* TISOFileSystem::ISO9660Directory::GetName() const
{
    return m_acName;
}

TISOFileSystem::ISO9660Directory::ISO9660Directory()
{
    m_pSubDirs = 0;
    m_pFiles = 0;
    m_iFileCount = -1;
}

TISOFileSystem::ISO9660Directory::~ISO9660Directory()
{
    tfree(m_pFiles);
}

void TISOFileSystem::ISO9660Directory::SetSubDirs(ISO9660Directory* subDirs, unsigned char count)
{
    m_pSubDirs = subDirs;
    m_ucSubDirCount = count;
}

TISOFileSystem::~TISOFileSystem()
{
    TFileManager* manager = TFileManager::s_pFileManager;
    if (m_pISOFile != 0) {
        TFile::Destroy(m_pISOFile);
    }
    manager->UnmountFileSystem(this);
    delete[] m_pDirectories;
}

TFile* TISOFileSystem::CreateFile(const TCString& path, unsigned int flags)
{
    if (!(flags & 1)) {
        return 0;
    }
    TISOFile* file = new TISOFile(this);
    if (file != 0) {
        if (file->Open(path, flags)) {
            return file;
        }
        delete file;
    }
    return 0;
}

void TISOFileSystem::DestroyFile(TFile* file)
{
    if (file != 0) {
        TISOFile* isoFile = (TISOFile*)file;
        isoFile->Close();
        delete isoFile;
    }
}

TFile* TISOFileSystem::GetISOFile()
{
    return m_pISOFile;
}

const TISOFileSystem::ISO9660PVD& TISOFileSystem::GetPVD()
{
    return m_oPVD;
}

// ---- TKernelInterface
bool TKernelInterface::Pause(bool pause)
{
    bool previous = m_bPaused;
    m_bPaused = pause;
    return previous;
}

bool TKernelInterface::IsPaused()
{
    return m_bPaused;
}

TScheduler* TKernelInterface::GetScheduler() const
{
    return m_pScheduler;
}

HINSTANCE__* TKernelInterface::GetInstance()
{
    return m_hInstance;
}

void TKernelInterface::SetInstance(HINSTANCE__* instance)
{
    m_hInstance = instance;
}

bool TKernelInterface::Update()
{
    if (!m_bPaused) {
        m_oSystemTimer.Update();
        float delta = GetSystemTimer()->GetDelta();
        float framesPerSecond = 1.0f / delta;
        float timer = m_fFPSTimer + delta;
        // once a second the average frame rate is blended with the latest instantaneous value
        if (timer > 1.0f) {
            m_fAverageFPS = (framesPerSecond + m_fAverageFPS) * 0.5f;
            m_fFPSTimer = 0.0f;
        } else {
            m_fFPSTimer = timer;
        }
        m_pScheduler->Update();
    } else {
        m_pScheduler->UpdateKernelPaused();
    }
    return true;
}

float TKernelInterface::GetFPS()
{
    return 1.0f / m_oSystemTimer.GetDelta();
}

void __stdcall TKernelInterface::InitialiseStatic()
{
}

void __stdcall TKernelInterface::DeinitialiseStatic()
{
}

TObject* __stdcall TKernelInterface::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TKernelInterface::CreateObject()
{
    return 0;
}

float TKernelInterface::GetAverageFPS()
{
    return m_fAverageFPS;
}

THPTimer* TKernelInterface::GetSystemTimer()
{
    return &m_oSystemTimer;
}

// ---- TScheduler
int TScheduler::GetFrameCount()
{
    return m_iFrameCount;
}

float TScheduler::GetTotalTime()
{
    return m_fTotalTime;
}

float TScheduler::GetCurrentTimeDelta()
{
    return m_fTimeDelta;
}

TKernelInterface* TScheduler::GetKernelInterface()
{
    return m_pKernelInterface;
}

} // namespace Toshi
