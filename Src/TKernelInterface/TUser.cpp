// Z:\Toshi\Source\TKernel\TUser.cpp
#define TOSHI_API __declspec(dllexport)
#include "TKernelMisc.h"
#include "TKernelUsers.h"

namespace Toshi {

TUserHandler TUserHandler::ms_oSingleton;

TUserHandler::TUserHandler()
{
    m_iUserCount = 0;
    TSystem::MemSet(m_apUsers, 0, sizeof(m_apUsers));
}

TUser::TUser(const char* name)
{
    m_pName = name;
    m_sUserID = -1;
    m_sNameLength = (short)TSystem::StringLength(name);
}

TUser::TUser(const TUser& other)
{
    m_pName = other.m_pName;
    m_sNameLength = other.m_sNameLength;
    m_sUserID = other.m_sUserID;
}

short TUser::GetUserID()
{
    return m_sUserID;
}

short TUser::GetNameLength()
{
    return m_sNameLength;
}

const char* TUser::GetName()
{
    return m_pName;
}

bool TUser::IsRegistered()
{
    if (m_sUserID == -1)
    {
        return false;
    }
    return true;
}

short TUser::Register()
{
    return TUserHandler::ms_oSingleton.RegisterUser(*this);
}

void TUser::Deregister()
{
    if (IsRegistered() == true) {
        TUserHandler::ms_oSingleton.m_apUsers[m_sUserID] = 0;
    }
    m_sUserID = -1;
}

short TUserHandler::RegisterUser(TUser& user)
{
    short result;
    int count = m_iUserCount;
    if (count < MAX_USERS)
    {
        m_iUserCount = count + 1;
        short id = (short)count;
        user.m_sUserID = id;
        m_apUsers[id] = &user;
        result = user.m_sUserID;
    }
    else
    {
        result = -1;
        user.m_sUserID = -1;
    }
    return result;
}

void TUserHandler::DeregisterUser(TUser& user)
{
    if (user.IsRegistered() == true)
    {
        m_apUsers[user.m_sUserID] = 0;
    }
    user.m_sUserID = -1;
}

TUser* TUserHandler::FindUser(const char* name)
{
    int length = TSystem::StringLength(name);
    for (int i = 0; i < MAX_USERS; i++)
    {
        TUser* user = m_apUsers[i];
        if (user != 0 && length == user->m_sNameLength
            && TSystem::StringCompareNoCase(user->m_pName, name, -1) == 0)
        {
            return user;
        }
    }
    return 0;
}

TUser* TUserHandler::GetUser(int index)
{
    return m_apUsers[index];
}

int TUserHandler::GetUserCount()
{
    return m_iUserCount;
}

TUserHandler& __stdcall TUserHandler::GetSingleton()
{
    return ms_oSingleton;
}

TRefCounted::TRefCounted()
{
    m_iRefCount = 0;
}

TRefCounted::TRefCounted(const TRefCounted& other)
{
    m_iRefCount = 0;
}

TRefCounted::~TRefCounted()
{
}

int TRefCounted::IncRefCount(void* owner)
{
    return ++m_iRefCount;
}

int TRefCounted::DecRefCount(void* owner)
{
    return --m_iRefCount;
}

int TRefCounted::GetRefCount() const
{
    return m_iRefCount;
}

} // namespace Toshi
