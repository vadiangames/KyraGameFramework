#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_DLL_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_DLL_HPP

#ifdef KYRA_ARD_EXPORTS
  #define KYRA_ARD_API __declspec(dllexport)
#else
  #define KYRA_ARD_API __declspec(dllimport)
#endif

#endif