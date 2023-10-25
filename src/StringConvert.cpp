#include "ComLib/StringConvert.h"
#include <sstream>
#pragma warning (disable : 4996) // function or variable may be unsafe (deprecated)
#include <codecvt>
#include <Windows.h>
#include <algorithm>
#include <vector>


bool StringConvert::IsUtf8Text(const std::string_view& value)
{
    DWORD nBytes = 0;//UFT8可用1-6个字节编码,ASCII用一个字节
    UCHAR chr;
    bool bAllAscii = true; //如果全部都是ASCII, 说明不是UTF-8
    auto str = value.data();
    auto length = value.size();
        for (int i = 0; i < length; ++i)
        {
            chr = *(str + i);
            if ((chr & 0x80) != 0) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx
                bAllAscii = false;
            if (nBytes == 0) //如果不是ASCII码,应该是多字节符,计算字节数
            {
                if (chr >= 0x80)
                {
                    
                        if (chr >= 0xFC && chr <= 0xFD)
                            nBytes = 6;
                        else if (chr >= 0xF8)
                            nBytes = 5;
                        else if (chr >= 0xF0)
                            nBytes = 4;
                        else if (chr >= 0xE0)
                            nBytes = 3;
                        else if (chr >= 0xC0)
                            nBytes = 2;
                        else
                            return false;

                    nBytes--;
                }
            }
            else //多字节符的非首字节,应为 10xxxxxx
            {
                if ((chr & 0xC0) != 0x80)
                    return false;

                nBytes--;
            }
        }
    
        if (nBytes > 0) //违返规则
            return false;
    if (bAllAscii) //如果全部都是ASCII, 说明不是UTF-8
        return false;

    return true;
}

std::string StringConvert::Unicode2Ascii(std::wstring wstrsrc)
{
    int nLength = ::WideCharToMultiByte(CP_OEMCP, 0, wstrsrc.c_str(), -1, NULL, 0, NULL, NULL);
    if (nLength <= 0)
        return std::string("");
    char* szbuffer = new char[nLength + 2];
    memset(szbuffer, 0, nLength + 2);
    int len = ::WideCharToMultiByte(CP_OEMCP, 0, wstrsrc.c_str(), -1, szbuffer, nLength, NULL, NULL);
    if (len > 0) {
        szbuffer[len] = 0;
    }
    std::string strnew = szbuffer;
    delete[] szbuffer;
    return strnew;
}

std::wstring StringConvert::StrToWStr(const std::string& str)
{
    if (str.empty())
    {
        return TEXT("");
    }

    int bufSize = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
    if (bufSize <= 0)
    {
        return TEXT("");
    }

    wchar_t* pWideBuf = new wchar_t[bufSize + 1];
    memset(pWideBuf, 0, sizeof(wchar_t) * (bufSize + 1));
    ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pWideBuf, bufSize);
    std::wstring retStr(pWideBuf);
    delete[] pWideBuf;

    return retStr;
}


std::string StringConvert::ToUTF8Str(const std::wstring& data) {
    if (data.empty()) {
        return "";
    }

    std::string utf8;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t> > convert;
    try {
        utf8 = convert.to_bytes(data);
    }
    catch (const std::range_error&) {
        utf8 = convert.to_bytes(data.substr(0, convert.converted()));
    }

    return utf8;
}

std::wstring StringConvert::FromUTF8Str(const std::string& utf8) {
    if (utf8.empty()) {
        return L"";
    }

    std::wstring wdata;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t> > convert;
    try {
        wdata = convert.from_bytes(utf8);
    }
    catch (const std::range_error&) {
        wdata = convert.from_bytes(utf8.substr(0, convert.converted()));
    }

    return wdata;
}


int64_t StringConvert::Convert2Int64(const std::string& value) {

    std::stringstream str;
    str << value;

    int64_t result{};
    str >> result;

    return result;
}
int64_t StringConvert::Convert2Int64(const std::wstring& value)
{
    std::wstringstream str;
    str << value;

    int64_t result{};
    str >> result;

    return result;
}

std::string StringConvert::Convert2String(int64_t value) {

    std::stringstream str;
    str << value;

    return str.str();
}

std::wstring StringConvert::Convert2WString(int64_t value)
{
    std::wstringstream str;
    str << value;

    return str.str();
}


std::wstring StringConvert::Convert2Double(double value)
{
    std::wstringstream str;
    str << value;
    return str.str();
}

int32_t StringConvert::Convert2Int32(const std::string& value) {
    std::stringstream str;
    str << value;

    int32_t result{};
    str >> result;

    return result;
}

std::string StringConvert::Convert2String(int32_t value) {
    std::stringstream str;
    str << value;

    return str.str();
}
std::wstring StringConvert::Convert2WString(int32_t value)
{
    std::wstringstream str;
    str << value;

    return str.str();
}

void StringConvert::HexStrToByte(const char* pSrcText, unsigned char* pDestText, int nDataLen)
{
    unsigned char highByte, lowByte;
    for (short i = 0; i < nDataLen; i += 2)
    {
        highByte = toupper(pSrcText[i]);
        lowByte = toupper(pSrcText[i + 1]);
        highByte -= (highByte > 0x39) ? 0x37 : 0x30;
        lowByte -= (lowByte > 0x39) ? 0x37 : 0x30;
        pDestText[i / 2] = (highByte << 4) | lowByte;
    }
}

std::wstring StringConvert::ReplaceString(const std::wstring_view& originalStr, const std::wstring_view& oldStr, const std::wstring_view& newStr)
{
    if (originalStr.empty())
    {
        return std::wstring(L"");
    }

    size_t pos = 0;
    std::wstring tempStr{ originalStr };
    std::wstring::size_type newStrLen = newStr.length();
    std::wstring::size_type oldStrLen = oldStr.length();
    while (true)
    {
        pos = tempStr.find(oldStr, pos);
        if (pos == std::wstring::npos)
        {
            break;
        }

        tempStr.replace(pos, oldStrLen, newStr);
        pos += newStrLen;
    }

    return tempStr;
}

std::string StringConvert::ReplaceStringA(std::string_view strOriginal, std::string_view strOld, std::string_view strNew)
{
    size_t nPos{0};
    std::string strResult = strOriginal.data();
    std::string::size_type nNewLen = strNew.size();
    std::string::size_type nOldLen = strOld.size();
    for (;;)
    {
        nPos = strResult.find(strOld, nPos);
        if (nPos == strResult.npos)
        {
            break;
        }
        strResult.replace(nPos, nOldLen, strNew);
        nPos += nNewLen;
    }

    return strResult;
}

std::wstring StringConvert::ToUpper(const std::wstring& orignalStr)
{
    if (orignalStr.empty())
    {
        return std::wstring(L"");
    }

    std::wstring convertedStr = orignalStr;
    std::transform(convertedStr.begin(), convertedStr.end(), convertedStr.begin(), towupper);

    return convertedStr;
}

std::wstring StringConvert::ToLower(const std::wstring& orignalStr)
{
    if (orignalStr.empty())
    {
        return std::wstring(L"");
    }

    std::wstring convertedStr = orignalStr;
    std::transform(convertedStr.begin(), convertedStr.end(), convertedStr.begin(), towlower);

    return convertedStr;
}

std::string StringConvert::ToUpper(const std::string& orignalStr)
{
    if (orignalStr.empty())
    {
        return "";
    }

    std::string convertedStr = orignalStr;
    std::transform(convertedStr.begin(), convertedStr.end(), convertedStr.begin(), toupper);

    return convertedStr;
}

std::string StringConvert::ToLower(const std::string& orignalStr)
{
    if (orignalStr.empty())
    {
        return "";
    }

    std::string convertedStr = orignalStr;
    std::transform(convertedStr.begin(), convertedStr.end(), convertedStr.begin(), tolower);

    return convertedStr;
}

std::wstring StringConvert::Trim(const std::wstring& str)
{
    if (str.empty())
    {
        return std::wstring(L"");
    }

    std::wstring strResult = TrimLeft(str);

    strResult = TrimRight(strResult);

    return strResult;

}

std::wstring StringConvert::TrimLeft(const std::wstring& str, const std::wstring& trimChar)
{
    return TrimLeftT(str, trimChar);
}

std::string StringConvert::TrimLeft(const std::string& str, const std::string& trimChar)
{
    return TrimLeftT(str, trimChar);
}

std::wstring StringConvert::TrimRight(const std::wstring& str, const std::wstring& trimChar)
{
    return TrimRightT(str, trimChar);
}

std::string StringConvert::TrimRight(const std::string& str, const std::string& trimChar)
{
    return TrimRightT(str, trimChar);
}

std::string StringConvert::Format(std::string format, ...)
{
    if (format.empty())
    {
        return std::string("");
    }

    std::string formattedStr("");

    va_list argsList = NULL;

    // initialize variable arguments
    va_start(argsList, format);

    // Get formatted string length adding one for NULL
    size_t formattedStrLen = _vscprintf(format.c_str(), argsList) + 1;

    // Create a char vector to hold the formatted string.
    std::vector<char> buffer(formattedStrLen, '\0');

    int nWritten = _vsnprintf_s(&buffer[0], buffer.size(), formattedStrLen, format.c_str(), argsList);

    if (nWritten > 0)
    {
        formattedStr = &buffer[0];
    }

    // Reset variable arguments
    va_end(argsList);

    return formattedStr;
}

#undef min
template <typename stringview>
constexpr static int StrCompare(const stringview& left, const stringview& right, bool bICase)noexcept
{
    static_assert(std::is_same<std::string_view, stringview>() || std::is_same<std::wstring_view, stringview>(), "只支持std::string_view和std::wstring_view");
    if (!bICase)
    {
        return left.compare(right);
    }
    auto minSize = std::min(left.size(), right.size());

    for (size_t index = 0; index < minSize; ++index)
    {
        if (left[index] == right[index])
        {
            continue;
        }
        const auto lch = towlower(left[index]);
        const auto rch = towlower(right[index]);
        if (lch == rch)
        {
            continue;
        }
        return lch - rch;
    }
    return left.size() - right.size();
}

int StringConvert::Compare(const std::string_view& left, const std::string_view& right, bool bICase)noexcept
{
    return StrCompare(left, right, bICase);
}

int StringConvert::Compare(const std::wstring_view& left, const std::wstring_view& right, bool bICase)noexcept
{
    return StrCompare(left, right, bICase);
}

bool StringConvert::Equal(const std::string_view& left, const std::string_view& right, bool bICase)noexcept
{
    return Compare(left,right,bICase) == 0;
}

bool StringConvert::Equal(const std::wstring_view& left, const std::wstring_view& right, bool bICase)noexcept
{
    return Compare(left, right, bICase) == 0;
}
template <typename stringview>
constexpr static size_t StrFind(const stringview& src, size_t off, const stringview& subStr, bool bICase)noexcept
{
    static_assert(std::is_same<std::string_view, stringview>() || std::is_same<std::wstring_view, stringview>(), "只支持std::string_view和std::wstring_view");
    if (!bICase)
    {
        return src.find_first_of(subStr, off);
    }
    auto startIter = std::search(src.begin() + off, src.end(), subStr.begin(), subStr.end(), [](wchar_t l, wchar_t r) {return l == r || toupper(l) == toupper(r); });
    return startIter != src.end() ? startIter - src.begin(): src.npos;
}

size_t StringConvert::Find(const std::string_view& src, const std::string_view subStr, bool bICase) noexcept
{
    return StrFind(src, 0, subStr, bICase);
}

size_t StringConvert::Find(const std::wstring_view& src, const std::wstring_view subStr, bool bICase) noexcept
{
    return StrFind(src, 0, subStr, bICase);
}

size_t StringConvert::Find(const std::string_view& src, size_t off, const std::string_view subStr, bool bICase) noexcept
{
    return StrFind(src, off, subStr, bICase);
}

size_t StringConvert::Find(const std::wstring_view& src, size_t off, const std::wstring_view subStr, bool bICase) noexcept
{
    return StrFind(src, off, subStr, bICase);
}

void StringConvert::SafeCpy(wchar_t* dest, int cnt, const wchar_t* src)
{
    wcsncpy(dest, src, cnt);
}

bool StringConvert::StartWith(const std::string& str, const std::string& strStart)
{
	if (str.empty() || strStart.empty())
	{
		return false;
	}

	if (strStart.size() > str.size())
	{
		return false;
	}

	return str.compare(0, strStart.size(), strStart) == 0 ? true : false;
}

bool StringConvert::StartWith(const std::wstring& str, const std::wstring& strStart)
{
	if (str.empty() || strStart.empty())
	{
		return false;
	}

	if (strStart.size() > str.size())
	{
		return false;
	}

	return str.compare(0, strStart.size(), strStart) == 0 ? true : false;
}

bool StringConvert::EndWith(const std::string& str, const std::string& strEnd)
{
	if (str.empty() || strEnd.empty())
	{
		return false;
	}

	if (strEnd.size() > str.size())
	{
		return false;
	}

	return str.compare(str.size() - strEnd.size(), strEnd.size(), strEnd) == 0 ? true : false;
}

bool StringConvert::EndWith(const std::wstring& str, const std::wstring& strEnd)
{
	if (str.empty() || strEnd.empty())
	{
		return false;
	}

	if (strEnd.size() > str.size())
	{
		return false;
	}

	return str.compare(str.size() - strEnd.size(), strEnd.size(), strEnd) == 0 ? true : false;
}

std::wstring StringConvert::GetBetweenValue(const std::wstring& strOrg, const std::wstring& strFind1, const std::wstring& strFind2)
{
	INT nPos1 = strOrg.find(strFind1.c_str());
	if (nPos1 == std::wstring::npos)
	{
		return std::wstring();
	}

	nPos1 += strFind1.length() - 1;
	INT nPos2 = strOrg.find(strFind2.c_str(), nPos1 + 1);
	if (nPos2 == std::wstring::npos)
	{
		return std::wstring();
	}
	return strOrg.substr(nPos1 + 1, nPos2 - nPos1 - 1);
}

std::string StringConvert::GetBetweenValue(const std::string& strOrg, const std::string& strFind1, const std::string& strFind2)
{
	INT nPos1 = strOrg.find(strFind1.c_str());
	if (nPos1 == std::string::npos)
	{
		return std::string();
	}

	nPos1 += strFind1.length() - 1;
	INT nPos2 = strOrg.find(strFind2.c_str(), nPos1 + 1);
	if (nPos2 == std::string::npos)
	{
		return std::string();
	}
	return strOrg.substr(nPos1 + 1, nPos2 - nPos1 - 1);
}

std::wstring StringConvert::Format(std::wstring format, ...)
{
    if (format.empty())
    {
        return std::wstring(L"");
    }

    std::wstring retStr(L"");

    va_list marker = NULL;

    // initialize variable arguments
    va_start(marker, format);

    // Get formatted string length adding one for NULL
    size_t len = _vscwprintf(format.c_str(), marker) + 1;

    // Create a wchar vector to hold the formatted string.
    std::vector<wchar_t> buffer(len, '\0');
    int nWritten = _vsnwprintf_s(&buffer[0], buffer.size(), len, format.c_str(), marker);

    if (nWritten > 0)
    {
        retStr = &buffer[0];
    }

    // Reset variable arguments
    va_end(marker);

    return retStr;
}

template <class CharType>
static std::vector<std::basic_string<CharType>> SplitString(const std::basic_string_view<CharType>& str, const std::basic_string_view<CharType>& pattern)
{
    using string_t = std::basic_string<CharType>;
    std::vector<string_t>   li;
    string_t subStr;
    string_t tPattern;
    size_t   patternLen = pattern.length();

    //遍历字符串，将i位置的字符放入子串中，当遇到pattern子串时完成一次切割
    //遍历之后得到切割后的子串列表
    for (size_t i = 0; i < str.length(); i++)
    {
        if (pattern[0] == str[i])//遇到需要检测pattern的情况
        {
            tPattern = str.substr(i, patternLen);
            if (tPattern == pattern)//找到一个匹配的pattern，完成切割
            {
                i += patternLen - 1;
                if (!subStr.empty())
                {
                    li.push_back(subStr);
                    subStr.clear();
                }
            }
            else//不是匹配的pattern，将i位置的字符放入子串
            {
                subStr.push_back(str[i]);
            }
        }
        else//未遇到pattern，将i位置的字符放入子串
        {
            subStr.push_back(str[i]);
        }
    }

    if (!subStr.empty())//将子串中的剩余字符放入子字符串队列
    {
        li.push_back(subStr);
    }

    return li;
}

std::vector<std::string> StringConvert::SplitString(const std::string& str, const std::string& pattern)
{
    using ::SplitString;
    return SplitString<char>(str, pattern);
}

std::vector<std::basic_string<TCHAR>> StringConvert::SplitString(const std::basic_string<TCHAR>& str, const std::basic_string<TCHAR>& pattern)
{
    using ::SplitString;
    return SplitString<TCHAR>(str, pattern);
}

template <class CharType>
static std::list<std::basic_string<CharType>> SplitString(const std::basic_string_view<CharType>& str, CharType splitChar)
{
    using string_t = std::basic_string<CharType>;
    using list_t = std::list<string_t>;
    list_t osList = {};
    for (size_t idx = 0; idx < str.size(); ++idx)
    {
        if (str[idx] == splitChar)
        {
            continue;
        }
        auto end = str.find(splitChar, idx);
        if (end == idx)
        {
            continue;
        }
        if (end >= str.size())
        {
            osList.push_back(string_t{ str.substr(idx) });
            idx = str.size();
            break;
        }
        if (end > idx)
        {
            osList.push_back(string_t{ str.substr(idx, end - idx) });
            idx = end;
            continue;
        }

    }
    return osList;
}

std::list<std::string> StringConvert::SplitString(const std::string_view& str, char splitChar)
{
    using ::SplitString;
    return SplitString<char>(str, splitChar);
}

std::list<std::wstring> StringConvert::SplitString(const std::wstring_view& wstr, wchar_t splitChar)
{
    using ::SplitString;
    return SplitString<wchar_t>(wstr, splitChar);
}

bool StringConvert::HasWhilCard(const std::wstring_view& str)
{
    return str.find_first_of('*') != str.npos || str.find_first_of('?') != str.npos;
}

std::wstring StringConvert::WhilCard2Regex(const std::wstring& whilcard)
{
    std::wstring dest;
    auto li = StringConvert::SplitString(whilcard, L';');
    for (auto str : li)
    {
        if (str.empty())
        {
            continue;
        }
        if (str == L"*.*")
        {
            return L".*";
        }
        else
        {
            str = StringConvert::ReplaceString(str, L"\\", LR"(\\)");
            str = StringConvert::ReplaceString(str, L"{", LR"(\{)");
            str = StringConvert::ReplaceString(str, L"}", LR"(\})");
            str = StringConvert::ReplaceString(str, L"(", LR"(\()");
            str = StringConvert::ReplaceString(str, L")", LR"(\))");
            str = StringConvert::ReplaceString(str, L"+", LR"(\+)");
            str = StringConvert::ReplaceString(str, L"]", LR"(\])");
            str = StringConvert::ReplaceString(str, L"[", LR"(\[)");
            str = StringConvert::ReplaceString(str, L"/", LR"(\/)");
            str = StringConvert::ReplaceString(str, L".", LR"(\.)");
            str = StringConvert::ReplaceString(str, L"$", LR"(\$)");
            str = StringConvert::ReplaceString(str, L"^", LR"(\^)");
            str = StringConvert::ReplaceString(str, L"?", L".");
            str = StringConvert::ReplaceString(str, L"*", L".*");
        }
        if (dest.empty())
        {
            dest.append(L"^" + str + L"$");
        }
        else
        {
            dest.append(L"|").append(L"^" + str + L"$");
        }
    }
    return dest;
}

template<class T>
T StringConvert::TrimLeftT(const T& str, const T& trimChar)
{
    if (str.empty())
    {
        return T();
    }

    T strResult = str;
    bool endLeftTrim = false;

    while (!endLeftTrim)
    {
        T subStr = strResult.substr(0, 1);
        if (subStr == trimChar)
        {
            strResult = strResult.substr(1);
        }
        else
        {
            endLeftTrim = true;
        }
    }
    return strResult;
}

template<class T>
T StringConvert::TrimRightT(const T& str, const T& trimChar)
{
    if (str.empty())
    {
        return T();
    }

    T strResult = str;
    bool endRightTrim = false;

    while (!endRightTrim)
    {
        T subStr = strResult.substr(strResult.size() - 1, 1);
        if (subStr == trimChar)
        {
            strResult = strResult.substr(0, strResult.size() - 1);
        }
        else
        {
            endRightTrim = true;
        }
    }

    return strResult;
}
