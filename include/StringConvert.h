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
    * @brief   ʵ���ַ����滻
    * @param   originalStr Դ��
    * @param   oldStr  ���ҵĴ�
    * @param   newStr  �滻���´�
    * @return  �����޸ĺ�Ĵ�
    * @example
    wstring originalStr=L"a,b,c";
    wstring replacedStr = Replace(originalStr, L",", L".");
    // replacedStr = L"a.b.c"
    */
    static std::wstring ReplaceString(const std::wstring_view& originalStr, const std::wstring_view& oldStr, const std::wstring_view& newStr);
    static std::string ReplaceStringA(std::string_view strOriginal, std::string_view strOld, std::string_view strNew);
    //�ַ������
    static std::vector<std::string> SplitString(const std::string& str, const std::string& pattern);
    static std::vector<std::basic_string<TCHAR>> SplitString(const std::basic_string<TCHAR>& str, const std::basic_string<TCHAR>& pattern);
    //�ַ�����֣������Ķ���ָ���ֻ��Ϊ 1 ��
    static std::list<std::string> SplitString(const std::string_view& str, char splitChar = ' ');
    static std::list<std::wstring> SplitString(const std::wstring_view& wstr, wchar_t splitChar = L' ');

    // ͨ���ת ������ʽ
    static bool HasWhilCard(const std::wstring_view& str);
    static std::wstring WhilCard2Regex(const std::wstring& whilcard);

    /**
    * @brief   ���ַ���תΪ��д
    * @param   orignalStr Դ�ַ���
    * @return  std::wstring ת������ַ���
    */
    static std::wstring ToUpper(const std::wstring& orignalStr);
    static std::string ToUpper(const std::string& orignalStr);
    /**
    * @brief   ���ַ���תΪСд
    * @param   const wstring & orignalStr
    * @return  std::wstring ת������ַ���
    */
    static std::wstring ToLower(const std::wstring& orignalStr);
    static std::string ToLower(const std::string& orignalStr);
    /**
    * @brief ȥ����λ�ո�
    * @param const wstring & str
    * @return std::wstring
    * @note
    */
    static std::wstring Trim(const std::wstring& str);

    /**
     * @brief ȥ��ͷ��ָ�����ַ���Ĭ��ȥ���ո�
     * @param str Դ�ַ���
     * @param trimChar ��Ҫȥ�����ַ�(ֻ����һ���ַ�)
     * @return ȥ������ַ���
     * @note
     */
    static std::wstring TrimLeft(const std::wstring& str, const std::wstring& trimChar = L" ");
    static std::string TrimLeft(const std::string& str, const std::string& trimChar = " ");
    /**
     * @brief ȥ��β��ָ�����ַ���Ĭ��ȥ���ո�
     * @param str Դ�ַ���
     * @param trimChar ��Ҫȥ�����ַ�(ֻ����һ���ַ�)
     * @return ȥ������ַ���
     * @note
     */
    static std::wstring TrimRight(const std::wstring& str, const std::wstring& trimChar = L" ");
    static std::string TrimRight(const std::string& str, const std::string& trimChar = " ");
    /**
    * @brief ��ʽ�ַ���
     * @param wstring format
    * @param ...
    * @return std::wstring
    * @note ע�⣡����...��������ֱ�Ӵ�wstring����Ϊԭ����...ֻ֧��wchar_t����֧��wstring��
    *���ʹ��ʱ������ǵ���wstring�����c_str()�������磺
    *wstring fileName;
    *KStringConvert.Format(L"%s", fileName.c_str());
    */
    static std::wstring Format(std::wstring format, ...);

    /**
     * @brief ��ʽ�ַ���
     * @param string format
     * @param ...
     * @return string
     * @note ע�⣡����...��������ֱ�Ӵ�string����Ϊԭ����...ֻ֧��char����֧��string��
     *���ʹ��ʱ������ǵ���string�����c_str()�������磺
     *string fileName;
     *KStringConvert.Format("%s", fileName.c_str());
     */
    static std::string Format(std::string format, ...);
    
    /**
    * �ַ����ȽϺ�����ָ���Ƿ���Դ�Сд����� bICase == true�����Դ�Сд�����򲻺��Դ�Сд
    **/ 
    static int Compare(const std::string_view& left, const std::string_view& right, bool bICase) noexcept;
    /**
    * �ַ����ȽϺ�����ָ���Ƿ���Դ�Сд����� bICase == true�����Դ�Сд�����򲻺��Դ�Сд
    **/
    static int Compare(const std::wstring_view& left, const std::wstring_view& right, bool bICase)noexcept;
    /**
    * �ַ����ȽϺ�����ָ���Ƿ���Դ�Сд����� bICase == true�����Դ�Сд�����򲻺��Դ�Сд
    **/
    static bool Equal(const std::string_view& left, const std::string_view& right, bool bICase)noexcept;
    /**
    * �ַ����ȽϺ�����ָ���Ƿ���Դ�Сд����� bICase == true�����Դ�Сд�����򲻺��Դ�Сд
    **/
    static bool Equal(const std::wstring_view& left, const std::wstring_view& right, bool bICase)noexcept;

    /**
    * �ַ������Һ�����ָ���Ƿ���Դ�Сд����� bICase == true�����Դ�Сд�����򲻺��Դ�Сд
    **/
    static size_t Find(const std::string_view& src, const std::string_view subStr, bool bICase)noexcept;
    /**
    * �ַ������Һ�����ָ���Ƿ���Դ�Сд����� bICase == true�����Դ�Сд�����򲻺��Դ�Сд
    **/
    static size_t Find(const std::wstring_view& src, const std::wstring_view subStr, bool bICase)noexcept;

    /**
    * �ַ������Һ�����ָ���Ƿ���Դ�Сд����� bICase == true�����Դ�Сд�����򲻺��Դ�Сд
    **/
    static size_t Find(const std::string_view& src, size_t off, const std::string_view subStr, bool bICase)noexcept;
    /**
    * �ַ������Һ�����ָ���Ƿ���Դ�Сд����� bICase == true�����Դ�Сд�����򲻺��Դ�Сд
    **/
    static size_t Find(const std::wstring_view& src, size_t off, const std::wstring_view subStr, bool bICase)noexcept;

    /** �ַ�����ȫ����
    */
    static void SafeCpy(wchar_t* dest, int cnt, const wchar_t* src);

    /** �ַ�����ʼ��ĳ���ַ���
    */
	static bool StartWith(const std::string& str, const std::string& strStart);
    static bool StartWith(const std::wstring& str, const std::wstring& strStart);

    /** �ַ���������ĳ���ַ���
    */
	static bool EndWith(const std::string& str, const std::string& strEnd);
	static bool EndWith(const std::wstring& str, const std::wstring& strEnd);

    /** ������ĳ�����ַ����м���ַ���
    */
	static std::string  GetBetweenValue(const std::string& strOrg, const std::string& strFind1, const std::string& strFind2);
	static std::wstring GetBetweenValue(const std::wstring& strOrg, const std::wstring& strFind1, const std::wstring& strFind2);
private:
    /**
     * @brief ȥ��ͷ��ָ�����ַ���Ĭ��ȥ���ո�
     * @param str Դ�ַ���
     * @param trimChar ��Ҫȥ�����ַ�(ֻ����һ���ַ�)
     * @return ȥ������ַ���
     * @note
     */
    template <class T>
    static T TrimLeftT(const T& str, const T& trimChar);

    /**
     * @brief ȥ��β��ָ�����ַ���Ĭ��ȥ���ո�
     * @param str Դ�ַ���
     * @param trimChar ��Ҫȥ�����ַ�(ֻ����һ���ַ�)
     * @return ȥ������ַ���
     * @note
     */
    template <class T>
    static T TrimRightT(const T& str, const T& trimChar);
};


#endif //STRING_CONVERT_H
