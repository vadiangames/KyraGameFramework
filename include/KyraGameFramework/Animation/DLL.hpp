#ifndef KYRAGAMEFRAMEWORK_ANIMATION_DLL_HPP
#define KYRAGAMEFRAMEWORK_ANIMATION_DLL_HPP

#ifdef KYRA_ANIMATION_EXPORTS
  #define KYRA_ANIMATION_API __declspec(dllexport)
#else
  #define KYRA_ANIMATION_API __declspec(dllimport)
#endif

#endif