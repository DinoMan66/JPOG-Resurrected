// TUser / TUserHandler / TRefCounted - kernel-internal declarations.
#ifndef TKERNELUSERS_H
#define TKERNELUSERS_H

namespace Toshi {

class TUserHandler;

// A named user slot; the handler hands out ids (indices into its table) on registration.
class __declspec(dllexport) TUser
{
public:
    TUser(const char* name);
    TUser(const TUser& other);
    short GetUserID();
    short GetNameLength();
    const char* GetName();
    bool IsRegistered();
    short Register();
    void Deregister();

private:
    friend class TUserHandler;

    const char* m_pName;        // +0x00
    short m_sNameLength;        // +0x04
    short m_sUserID;            // +0x06  -1 while not registered
};

class __declspec(dllexport) TUserHandler
{
public:
    enum { MAX_USERS = 50 };

    TUserHandler();
    ~TUserHandler() {}

    short RegisterUser(TUser& user);
    void DeregisterUser(TUser& user);
    TUser* FindUser(const char* name);
    TUser* GetUser(int index);
    int GetUserCount();
    static TUserHandler& __stdcall GetSingleton();

private:
    friend class TUser;

    int m_iUserCount;                   // +0x00
    TUser* m_apUsers[MAX_USERS];        // +0x04
    static TUserHandler ms_oSingleton;
};

// Reference count only (no vtable): the count is the first and only member.
class __declspec(dllexport) TRefCounted
{
public:
    TRefCounted();
    ~TRefCounted();
    int IncRefCount(void* owner);
    int DecRefCount(void* owner);
    int GetRefCount() const;

private:
    TRefCounted(const TRefCounted& other);
    TRefCounted& operator=(const TRefCounted& other);

    int m_iRefCount;                    // +0x00
};

} // namespace Toshi
#endif
