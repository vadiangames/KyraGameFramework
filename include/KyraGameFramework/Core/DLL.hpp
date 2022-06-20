#ifndef KYRAGAMEFRAMEWORK_CORE_DLL_HPP
#define KYRAGAMEFRAMEWORK_CORE_DLL_HPP

#ifdef KYRA_CORE_EXPORTS
  #define KYRA_CORE_API __declspec(dllexport)
#else
  #define KYRA_CORE_API __declspec(dllimport)
#endif

#endif