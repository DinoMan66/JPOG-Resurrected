// Z:\Toshi\Source\TKernel\TFileLexerUTF16.cpp - the Token members of the UTF-16 lexer.
// Everything but assign() is inline in TKernelLexer.h; this file only makes the compiler emit it.
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include "TNewDelete.h"
#include "TKernelLexer.h"

namespace Toshi {

TFileLexerUTF16::ParseError& TFileLexerUTF16::ParseError::operator=(const ParseError& other)
{
    m_iLine = other.m_iLine;
    m_szMessage = other.m_szMessage;
    return *this;
}

void TFileLexerUTF16::SetInputStream(TFile* file)
{
    m_pFile = file;
    m_iLine = 1;
    m_iIfDepth = 0;
    m_abIfStack[0] = true;
    m_bPreprocessorAllow = ComputePreprocessorAllow();
    SetCharacterLookaheadSize(3);
}

void TFileLexerUTF16::SetOutputComments(bool outputComments)
{
    m_bOutputComments = outputComments;
}

TEmitter<TFileLexerUTF16, TFileLexerUTF16::ParseError>* TFileLexerUTF16::GetParseErrorEmitter()
{
    return &m_oParseErrorEmitter;
}

void TFileLexerUTF16::ThrowError(const char* message)
{
    ParseError error;
    error.m_iLine = m_iLine;
    error.m_szMessage = message;
    m_oParseErrorEmitter.Throw(error);
}

void TFileLexerUTF16::advance()
{
    m_iHead = (m_iHead + 1) & m_iBufferMask;
    m_pBuffer[m_iTail] = m_pFile->GetWChar();
    m_iTail = m_iHead;
}

void TFileLexerUTF16::advance(int count)
{
    m_iHead = (m_iHead + count) & m_iBufferMask;
    fillLookAhead();
}

int TFileLexerUTF16::peek()
{
    return m_pBuffer[m_iHead];
}

int TFileLexerUTF16::peek(int ahead)
{
    return m_pBuffer[(m_iHead + ahead) & m_iBufferMask];
}

void TFileLexerUTF16::fillLookAhead()
{
    while (m_iTail != m_iHead) {
        m_pBuffer[m_iTail] = m_pFile->GetWChar();
        m_iTail = (m_iTail + 1) & m_iBufferMask;
    }
}

TClass& TFileLexerUTF16::GetClass() const
{
    return m_sClass;
}

void __stdcall TFileLexerUTF16::DeinitialiseStatic()
{
}

void __stdcall TFileLexerUTF16::InitialiseStatic()
{
}

TObject* __stdcall TFileLexerUTF16::CreateObjectInPlace(void* memory)
{
    return new (memory) TFileLexerUTF16;
}

TObject* __stdcall TFileLexerUTF16::CreateObject()
{
    return new TFileLexerUTF16;
}

TFileLexerUTF16::Token TFileLexerUTF16::GetLastToken()
{
    return m_oLastToken;
}

} // namespace Toshi
