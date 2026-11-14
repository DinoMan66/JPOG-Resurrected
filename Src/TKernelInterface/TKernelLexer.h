// Toshi::TFileLexerUTF16 and TFileLexerUTF8 - kernel-internal declarations. Only the Token classes so far.
// A Token is 12 bytes: type +0, line +4, value +8 (a pooled string for the string-like types).
// Its small members are inline in the class, as in the original (the kernel exports them because the
// class is dllexport); assign() is the one real function.
#ifndef TKERNELLEXER_H
#define TKERNELLEXER_H
#include "TPString.h"
#include "TKernelObject.h"
#include "TKernelEmitter.h"
#include "TKernelFiles.h"
#include <new.h>

namespace Toshi {

class TFileLexer : public TObject
{
public:
    // The values are the ones the binaries test (see MATCHING_NOTES #22 for the spellings).
    enum TokenType
    {
        TOKEN_EOF = 0,
        TOKEN_SEMICOLON = 1, TOKEN_COLON = 2, TOKEN_COMMA = 3, TOKEN_DOT = 4, TOKEN_ASTERISK = 5,
        TOKEN_DOLLAR = 6, TOKEN_OPENSQR = 7, TOKEN_CLOSESQR = 8, TOKEN_OPENBRACE = 9,
        TOKEN_CLOSEBRACE = 10, TOKEN_OPENPAREN = 11, TOKEN_CLOSEPAREN = 12, TOKEN_LESSTHAN = 13,
        TOKEN_GREATERTHAN = 14, TOKEN_EQUAL = 15,
        TOKEN_IDENT = 0x10, TOKEN_STRING = 0x11, TOKEN_INTEGER = 0x12, TOKEN_UINTEGER = 0x13,
        TOKEN_FLOAT = 0x14, TOKEN_COMMENT = 0x15
    };
};

class __declspec(dllexport) TFileLexerUTF16 : public TFileLexer
{
public:
    class __declspec(dllexport) Token
    {
    public:
        Token()
        {
            m_type = TOKEN_EOF;
            m_line = 0;
        }
        Token(int line)
        {
            m_type = TOKEN_EOF;
            m_line = line;
        }
        Token(TokenType type, int line)
        {
            m_type = type;
            m_line = line;
        }
        Token(int line, int integer)
        {
            m_type = TOKEN_INTEGER;
            m_line = line;
            m_value.i = integer;
        }
        Token(int line, unsigned int integer)
        {
            m_type = TOKEN_UINTEGER;
            m_line = line;
            m_value.u = integer;
        }
        Token(int line, float number)
        {
            m_type = TOKEN_FLOAT;
            m_line = line;
            m_value.f = number;
        }
        Token(TokenType type, int line, const TPWString& text)
        {
            m_type = type;
            m_line = line;
            new (&m_value) TPWString(text);
        }
        Token(const Token& other)
        {
            m_type = TOKEN_EOF;
            assign(other);
        }
        ~Token()
        {
            if (m_type == TOKEN_IDENT || m_type == TOKEN_STRING || m_type == TOKEN_COMMENT) {
                GetString().~TPWString();
            }
        }
        Token& operator=(const Token& other)
        {
            assign(other);
            return *this;
        }
        void assign(const Token& other);

        TokenType GetType() const { return m_type; }
        int GetLine() const { return m_line; }
        float GetFloat() const { return m_value.f; }
        unsigned int GetUInteger() const { return m_value.u; }
        int GetInteger() const { return m_value.i; }
        const TPWString& GetString() const { return *(const TPWString*)&m_value; }
        TPWString& GetString() { return *(TPWString*)&m_value; }

    private:
        TokenType m_type;   // +0
        int m_line;         // +4
        union
        {
            int i;
            unsigned int u;
            float f;
            void* p;
        } m_value;         // +8
    };

    class __declspec(dllexport) ParseError
    {
    public:
        ParseError& operator=(const ParseError& other);

        int m_iLine;                // +0x00
        const char* m_szMessage;    // +0x04
    };

    TFileLexerUTF16();
    TFileLexerUTF16(TFile* file, int lookahead);
    virtual ~TFileLexerUTF16();
    virtual TClass& GetClass() const;

    void SetInputStream(TFile* file);
    void SetCharacterLookaheadSize(int size);
    void SetOutputComments(bool outputComments);
    TEmitter<TFileLexerUTF16, ParseError>* GetParseErrorEmitter();
    Token GetLastToken();

    static TClass m_sClass;

protected:
    void ThrowError(const char* message);
    void advance();
    void advance(int count);
    int peek();
    int peek(int ahead);
    void fillLookAhead();

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();

    bool ComputePreprocessorAllow();

    // the look-ahead characters sit in a ring buffer: m_iHead is the next one to read, m_iTail the next to fill
    TFile* m_pFile;                 // +0x04
    bool m_bOutputComments;         // +0x08
    int m_iBufferSize;              // +0x0C (a power of two)
    int m_iBufferMask;              // +0x10
    int* m_pBuffer;                 // +0x14
    int m_iHead;                    // +0x18
    int m_iTail;                    // +0x1C
    int m_iLine;                    // +0x20
    unsigned char m_unk24[8];       // +0x24
    Token m_oLastToken;             // +0x2C (returned by GetLastToken)
    unsigned char m_unk38[0x10];    // +0x38
    int m_iIfDepth;                 // +0x48 (nesting depth of the conditional-compilation directives)
    bool m_abIfStack[0x20];         // +0x4C
    bool m_bPreprocessorAllow;      // +0x6C
    unsigned char m_unk6D[0x13];    // +0x6D
    TEmitter<TFileLexerUTF16, ParseError> m_oParseErrorEmitter;    // +0x80
};

class __declspec(dllexport) TFileLexerUTF8 : public TFileLexer
{
public:
    class __declspec(dllexport) Token
    {
    public:
        Token()
        {
            m_type = TOKEN_EOF;
            m_line = 0;
        }
        Token(int line)
        {
            m_type = TOKEN_EOF;
            m_line = line;
        }
        Token(TokenType type, int line)
        {
            m_type = type;
            m_line = line;
        }
        Token(int line, int integer)
        {
            m_type = TOKEN_INTEGER;
            m_line = line;
            m_value.i = integer;
        }
        Token(int line, unsigned int integer)
        {
            m_type = TOKEN_UINTEGER;
            m_line = line;
            m_value.u = integer;
        }
        Token(int line, float number)
        {
            m_type = TOKEN_FLOAT;
            m_line = line;
            m_value.f = number;
        }
        Token(TokenType type, int line, const TPCString& text)
        {
            m_type = type;
            m_line = line;
            new (&m_value) TPCString(text);
        }
        Token(const Token& other)
        {
            m_type = TOKEN_EOF;
            assign(other);
        }
        ~Token()
        {
            if (m_type == TOKEN_IDENT || m_type == TOKEN_STRING || m_type == TOKEN_COMMENT) {
                GetString().~TPCString();
            }
        }
        Token& operator=(const Token& other)
        {
            assign(other);
            return *this;
        }
        void assign(const Token& other);

        TokenType GetType() const { return m_type; }
        int GetLine() const { return m_line; }
        float GetFloat() const { return m_value.f; }
        unsigned int GetUInteger() const { return m_value.u; }
        int GetInteger() const { return m_value.i; }
        const TPCString& GetString() const { return *(const TPCString*)&m_value; }
        TPCString& GetString() { return *(TPCString*)&m_value; }

    private:
        TokenType m_type;   // +0
        int m_line;         // +4
        union
        {
            int i;
            unsigned int u;
            float f;
            void* p;
        } m_value;         // +8
    };

    class __declspec(dllexport) ParseError
    {
    public:
        ParseError& operator=(const ParseError& other);

        int m_iLine;                // +0x00
        const char* m_szMessage;    // +0x04
    };

    TFileLexerUTF8();
    TFileLexerUTF8(TFile* file, int lookahead);
    virtual ~TFileLexerUTF8();
    virtual TClass& GetClass() const;

    void SetInputStream(TFile* file);
    void SetCharacterLookaheadSize(int size);
    void SetOutputComments(bool outputComments);
    TEmitter<TFileLexerUTF8, ParseError>* GetParseErrorEmitter();
    Token GetLastToken();

    static TClass m_sClass;

protected:
    void ThrowError(const char* message);
    void advance();
    void advance(int count);
    int peek();
    int peek(int ahead);
    void fillLookAhead();

private:
    static TObject* __stdcall CreateObject();
    static TObject* __stdcall CreateObjectInPlace(void* memory);
    static void __stdcall InitialiseStatic();
    static void __stdcall DeinitialiseStatic();

    bool ComputePreprocessorAllow();

    // the look-ahead characters sit in a ring buffer: m_iHead is the next one to read, m_iTail the next to fill
    TFile* m_pFile;                 // +0x04
    bool m_bOutputComments;         // +0x08
    int m_iBufferSize;              // +0x0C (a power of two)
    int m_iBufferMask;              // +0x10
    int* m_pBuffer;                 // +0x14
    int m_iHead;                    // +0x18
    int m_iTail;                    // +0x1C
    int m_iLine;                    // +0x20
    unsigned char m_unk24[8];       // +0x24
    Token m_oLastToken;             // +0x2C (returned by GetLastToken)
    unsigned char m_unk38[0x10];    // +0x38
    int m_iIfDepth;                 // +0x48 (nesting depth of the conditional-compilation directives)
    bool m_abIfStack[0x20];         // +0x4C
    bool m_bPreprocessorAllow;      // +0x6C
    unsigned char m_unk6D[0x13];    // +0x6D
    TEmitter<TFileLexerUTF8, ParseError> m_oParseErrorEmitter;    // +0x80
};

} // namespace Toshi
#endif
