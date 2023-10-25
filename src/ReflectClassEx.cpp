#include "ReflectClassEx.h"
#include "StringConvert.h"

namespace ComLib
{
	ReflectClassEx::ReflectClassEx()
	{

	}
	ReflectClassEx* ReflectClassEx::Instance()
	{
		static ReflectClassEx s_instance;
		return &s_instance;
	}

	void* ReflectClassEx::CreateObjByClassEx(const std::wstring& className)
	{
		return ReflectClassEx::Instance()->CreateObjcetByClassName(StringConvert::Unicode2Ascii(className));
	}

	void* ReflectClassEx::CreateObjcetByClassName(const std::string& className)
	{
		if (m_reflectClassMap.find(className) != m_reflectClassMap.end())
		{
			return m_reflectClassMap[className]();
		}
		return nullptr;
	}
	void ReflectClassEx::RegistClass(const std::string& className, std::function<void* (void)> fun)
	{
		if (className.empty())
		{
			return;
		}

		m_reflectClassMap.insert(std::pair(className, fun));
	}
	ReflectClassHelper::ReflectClassHelper(const std::string& className, std::function<void* (void)> fun)
	{
		ReflectClassEx::Instance()->RegistClass(className, fun);
	}
}