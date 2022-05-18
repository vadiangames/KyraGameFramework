#ifndef KYRAGAMEFRAMEWORK_WINDOW_HPP
#define KYRAGAMEFRAMEWORK_WINDOW_HPP

#include <KyraGameFramework/Window/DLL.hpp>
#include <KyraGameFramework/Window/IWindow.hpp>
#include <KyraGameFramework/Window/SystemEventListener.hpp>
#include <KyraGameFramework/Window/SystemEventDispatcher.hpp>

#if defined(__WIN32__) || defined(__WIN64__) || defined(_WIN32) || defined(_WIN64)

#include <KyraGameFramework/Window/Windows/WindowWin32.hpp>

#endif

#endif