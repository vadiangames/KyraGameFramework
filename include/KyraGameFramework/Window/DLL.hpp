#ifndef KYRAGAMEFRAMEWORK_WINDOW_DLL_HPP
#define KYRAGAMEFRAMEWORK_WINDOW_DLL_HPP

#ifdef KYRA_WINDOW_EXPORTS
  #define KYRA_WINDOW_API __declspec(dllexport)
#else
  #define KYRA_WINDOW_API __declspec(dllimport)
#endif

#endif