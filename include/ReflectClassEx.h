/** 通用实现类反射辅助工具
* 使用方法：
* 1、反射类注册
* 在类定义中增加宏 REFLECT_CLASS， 建议在类头部增加
* 在类实现文件中增加宏 REG_REFLECT_CLASS，建议在构造函数实现体之前
* 2、反射类对象创建
* 调用ReflectClassEx::Instance()->CreateObjcetByClassName()即可，返回类型需要进行转换
*/

#ifndef __ReflectClassEx_h_
#define __ReflectClassEx_h_

#include <functional>
#include <string>
#include <map>

namespace ComLib
{
    // 实现反射的辅助类
    class ReflectClassEx
    {
    public:
        static ReflectClassEx* Instance();
        static void* CreateObjByClassEx(const std::wstring& className);
        void* CreateObjcetByClassName(const std::string& className);
        void RegistClass(const std::string& className, std::function<void* (void)> fun);
    private:
        ReflectClassEx();
        typedef std::map<std::string, std::function<void* (void)>> ReflectClassObjMap;
        ReflectClassObjMap m_reflectClassMap;
    };

    class ReflectClassHelper
    {
    public:
        ReflectClassHelper(const std::string& className, std::function<void* (void)> fun);
    };

#define REFLECT_CLASS(className)								\
public:                                                         \
static void* CreateObj(void)									\
{                                                               \
    return new className();										\
}																\
static ComLib::ReflectClassHelper s_creatorReflectClassHelper

#define REG_REFLECT_CLASS(className) \
ComLib::ReflectClassHelper className::s_creatorReflectClassHelper(#className, className::CreateObj)

}
#endif // !__ReflectClass_h_