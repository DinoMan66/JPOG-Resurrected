// Z:\Toshi\Source\TKernel\TFileLexerUTF8.cpp - the Token class of TFileLexerUTF8.
// Everything but assign() is inline in TKernelLexer.h; the class is exported, so the compiler emits it here.
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include "TNewDelete.h"
#include "TKernelLexer.h"

namespace Toshi {

TFileLexerUTF8::ParseError& TFileLexerUTF8::ParseError::operator=(const ParseError& other)
{
    m_iLine = other.m_iLine;
    m_szMessage = other.m_szMessage;
    return *this;
}

void TFileLexerUTF8::SetInputStream(TFile* file)
{
    m_pFile = file;
    m_iLine = 1;
    m_iIfDepth = 0;
    m_abIfStack[0] = true;
    m_bPreprocessorAllow = ComputePreprocessorAllow();
    SetCharacterLookaheadSize(3);
}

void TFileLexerUTF8::SetOutputComments(bool outputComments)
{
    m_bOutputComments = outputComments;
}

TEmitter<TFileLexerUTF8, TFileLexerUTF8::ParseError>* TFileLexerUTF8::GetParseErrorEmitter()
{
    return &m_oParseErrorEmitter;
}

void TFileLexerUTF8::ThrowError(const char* message)
{
    ParseError error;
    error.m_iLine = m_iLine;
    error.m_szMessage = message;
    m_oParseErrorEmitter.Throw(error);
}

void TFileLexerUTF8::advance()
{
    m_iHead = (m_iHead + 1) & m_iBufferMask;
    m_pBuffer[m_iTail] = m_pFile->GetCChar();
    m_iTail = m_iHead;
}

void TFileLexerUTF8::advance(int count)
{
    m_iHead = (m_iHead + count) & m_iBufferMask;
    fillLookAhead();
}

int TFileLexerUTF8::peek()
{
    return m_pBuffer[m_iHead];
}

int TFileLexerUTF8::peek(int ahead)
{
    return m_pBuffer[(m_iHead + ahead) & m_iBufferMask];
}

void TFileLexerUTF8::fillLookAhead()
{
    while (m_iTail != m_iHead) {
        m_pBuffer[m_iTail] = m_pFile->GetCChar();
        m_iTail = (m_iTail + 1) & m_iBufferMask;
    }
}

TClass& TFileLexerUTF8::GetClass() const
{
    return m_sClass;
}

void __stdcall TFileLexerUTF8::DeinitialiseStatic()
{
}

void __stdcall TFileLexerUTF8::InitialiseStatic()
{
}

TObject* __stdcall TFileLexerUTF8::CreateObjectInPlace(void* memory)
{
    return new (memory) TFileLexerUTF8;
}

TObject* __stdcall TFileLexerUTF8::CreateObject()
{
    return new TFileLexerUTF8;
}

TFileLexerUTF8::Token TFileLexerUTF8::GetLastToken()
{
    return m_oLastToken;
}

} // namespace Toshi
