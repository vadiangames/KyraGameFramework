#ifndef KYRAGAMEFRAMEWORK_THREADING_DLL_HPP
#define KYRAGAMEFRAMEWORK_THREADING_DLL_HPP

#ifdef KYRA_THREADING_EXPORTS
  #define KYRA_THREADING_API __declspec(dllexport)
#else
  #define KYRA_THREADING_API __declspec(dllimport)
#endif

#endif