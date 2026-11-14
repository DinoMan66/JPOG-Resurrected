// Export macro for PGUICore.dll (the plugin that adds game-facing widgets and layouts on top of TGuiInterface).
#ifndef PGUIAPI_H
#define PGUIAPI_H
#ifdef PGUICORE_EXPORTS
#define PGUI_API __declspec(dllexport)
#else
#define PGUI_API __declspec(dllimport)
#endif
#endif
