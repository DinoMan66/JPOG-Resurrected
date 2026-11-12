// Export macro for TGuiInterface.dll (Toshi GUI). Every class is exported whole.
#ifndef TGUIAPI_H
#define TGUIAPI_H
#ifdef TGUIINTERFACE_EXPORTS
#define TGUI_API __declspec(dllexport)
#else
#define TGUI_API __declspec(dllimport)
#endif
#endif
