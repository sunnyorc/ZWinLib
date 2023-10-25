#ifndef STRING_CONVERT_H
#define STRING_CONVERT_H

#include <string>
#include <list>
#include <vector>
#include <wtypes.h>

class StringConvert {

public:
    static bool IsUtf8Text(const std::string_view& value);
    static std::string Unicode2Ascii(std::wstring wstrsrc);
    static std::wstring StrToWStr(const std::string& str);
    static std::string ToUTF8Str(const std::wstring& data);
    static std::wstring FromUTF8Str(const std::string& utf8);

    static int64_t Convert2Int64(const std::string& value);
    static int64_t Convert2Int64(const std::wstring& value);
    static std::string Convert2String(int64_t value);
    static std::wstring Convert2WString(int64_t value);
    static int32_t Convert2Int32(const std::string& value);
    static std::string Convert2String(int32_t value);
    static std::wstring Convert2WString(int32_t value);

    static std::wstring Convert2Double(double value);

    static void HexStrToByte(const char* pSrcText, unsigned char* pDestText, int nDataLen);

    /**
    * @brief   实现字符串替换
    * @param   originalStr 源串
    * @param   oldStr  查找的串
    * @param   newStr  替换的新串
    * @return  返回修改后的串
    * @example
    wstring originalStr=L"a,b,c";
    wstring replacedStr = Replace(originalStr, L",", L".");
    // replacedStr = L"a.b.c"
    */
    static std::wstring ReplaceString(const std::wstring_view& originalStr, const std::wstring_view& oldStr, const std::wstring_view& newStr);
    static std::string ReplaceStringA(std::string_view strOriginal, std::string_view strOld, std::string_view strNew);
    //字符串拆分
    static std::vector<std::string> SplitString(const std::string& str, const std::string& pattern);
    static std::vector<std::basic_string<TCHAR>> SplitString(const std::basic_string<TCHAR>& str, const std::basic_string<TCHAR>& pattern);
    //字符串拆分，连续的多个分隔符只作为 1 个
    static std::list<std::string> SplitString(const std::string_view& str, char splitChar = ' ');
    static std::list<std::wstring> SplitString(const std::wstring_view& wstr, wchar_t splitChar = L' ');

    // 通配符转 正则表达式
    static bool HasWhilCard(const std::wstring_view& str);
    static std::wstring WhilCard2Regex(const std::wstring& whilcard);

    /**
    * @brief   将字符串转为大写
    * @param   orignalStr 源字符串
    * @return  std::wstring 转换后的字符串
    */
    static std::wstring ToUpper(const std::wstring& orignalStr);
    static std::string ToUpper(const std::string& orignalStr);
    /**
    * @brief   将字符串转为小写
    * @param   const wstring & orignalStr
    * @return  std::wstring 转换后的字符串
    */
    static std::wstring ToLower(const std::wstring& orignalStr);
    static std::string ToLower(const std::string& orignalStr);
    /**
    * @brief 去除首位空格
    * @param const wstring & str
    * @return std::wstring
    * @note
    */
    static std::wstring Trim(const std::wstring& str);

    /**
     * @brief 去除头部指定的字符（默认去掉空格）
     * @param str 源字符串
     * @param trimChar 需要去除的字符(只能是一个字符)
     * @return 去除后的字符串
     * @note
     */
    static std::wstring TrimLeft(const std::wstring& str, const std::wstring& trimChar = L" ");
    static std::string TrimLeft(const std::string& str, const std::string& trimChar = " ");
    /**
     * @brief 去除尾部指定的字符（默认去掉空格）
     * @param str 源字符串
     * @param trimChar 需要去除的字符(只能是一个字符)
     * @return 去除后的字符串
     * @note
     */
    static std::wstring TrimRight(const std::wstring& str, const std::wstring& trimChar = L" ");
    static std::string TrimRight(const std::string& str, const std::string& trimChar = " ");
    /**
    * @brief 格式字符串
     * @param wstring format
    * @param ...
    * @return std::wstring
    * @note 注意！后面...参数不能直接传wstring，因为原生的...只支持wchar_t，不支持wstring。
    *因此使用时，必须记得在wstring后面加c_str()方法。如：
    *wstring fileName;
    *KStringConvert.Format(L"%s", fileName.c_str());
    */
    static std::wstring Format(std::wstring format, ...);

    /**
     * @brief 格式字符串
     * @param string format
     * @param ...
     * @return string
     * @note 注意！后面...参数不能直接传string，因为原生的...只支持char，不支持string。
     *因此使用时，必须记得在string后面加c_str()方法。如：
     *string fileName;
     *KStringConvert.Format("%s", fileName.c_str());
     */
    static std::string Format(std::string format, ...);
    
    /**
    * 字符串比较函数，指定是否忽略大小写，如果 bICase == true，忽略大小写，否则不忽略大小写
    **/ 
    static int Compare(const std::string_view& left, const std::string_view& right, bool bICase) noexcept;
    /**
    * 字符串比较函数，指定是否忽略大小写，如果 bICase == true，忽略大小写，否则不忽略大小写
    **/
    static int Compare(const std::wstring_view& left, const std::wstring_view& right, bool bICase)noexcept;
    /**
    * 字符串比较函数，指定是否忽略大小写，如果 bICase == true，忽略大小写，否则不忽略大小写
    **/
    static bool Equal(const std::string_view& left, const std::string_view& right, bool bICase)noexcept;
    /**
    * 字符串比较函数，指定是否忽略大小写，如果 bICase == true，忽略大小写，否则不忽略大小写
    **/
    static bool Equal(const std::wstring_view& left, const std::wstring_view& right, bool bICase)noexcept;

    /**
    * 字符串查找函数，指定是否忽略大小写，如果 bICase == true，忽略大小写，否则不忽略大小写
    **/
    static size_t Find(const std::string_view& src, const std::string_view subStr, bool bICase)noexcept;
    /**
    * 字符串查找函数，指定是否忽略大小写，如果 bICase == true，忽略大小写，否则不忽略大小写
    **/
    static size_t Find(const std::wstring_view& src, const std::wstring_view subStr, bool bICase)noexcept;

    /**
    * 字符串查找函数，指定是否忽略大小写，如果 bICase == true，忽略大小写，否则不忽略大小写
    **/
    static size_t Find(const std::string_view& src, size_t off, const std::string_view subStr, bool bICase)noexcept;
    /**
    * 字符串查找函数，指定是否忽略大小写，如果 bICase == true，忽略大小写，否则不忽略大小写
    **/
    static size_t Find(const std::wstring_view& src, size_t off, const std::wstring_view subStr, bool bICase)noexcept;

    /** 字符串安全拷贝
    */
    static void SafeCpy(wchar_t* dest, int cnt, const wchar_t* src);

    /** 字符串开始于某个字符串
    */
	static bool StartWith(const std::string& str, const std::string& strStart);
    static bool StartWith(const std::wstring& str, const std::wstring& strStart);

    /** 字符串结束于某个字符串
    */
	static bool EndWith(const std::string& str, const std::string& strEnd);
	static bool EndWith(const std::wstring& str, const std::wstring& strEnd);

    /** 查找在某两个字符串中间的字符串
    */
	static std::string  GetBetweenValue(const std::string& strOrg, const std::string& strFind1, const std::string& strFind2);
	static std::wstring GetBetweenValue(const std::wstring& strOrg, const std::wstring& strFind1, const std::wstring& strFind2);
private:
    /**
     * @brief 去除头部指定的字符（默认去掉空格）
     * @param str 源字符串
     * @param trimChar 需要去除的字符(只能是一个字符)
     * @return 去除后的字符串
     * @note
     */
    template <class T>
    static T TrimLeftT(const T& str, const T& trimChar);

    /**
     * @brief 去除尾部指定的字符（默认去掉空格）
     * @param str 源字符串
     * @param trimChar 需要去除的字符(只能是一个字符)
     * @return 去除后的字符串
     * @note
     */
    template <class T>
    static T TrimRightT(const T& str, const T& trimChar);
};


#endif //STRING_CONVERT_H
