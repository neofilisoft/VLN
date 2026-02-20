// src/main.cpp
// Main Entry Point

#include <raylib.h>
#include "core/Engine.h"
#include "scripting/LuaManager.h"
#include "python/PythonBridge.h"
#include "live2d/Live2DManager.h"
#include "live2d/LipSyncManager.h"
#include "audio/AudioManager.h"
#include "save/SaveLoadManager.h"
#include "settings/SettingsManager.h"
#include "localization/LocalizationManager.h"
#include "plugin/PluginManager.h"
#include "dlc/DLCManager.h"
#include "gui/SetupWizard.h"
#include "gui/DebugMenu.h"
#include "gui/SettingsMenu.h"

int main() {
    // 1. Init Engine หลัก (แสดงเวอร์ชั่น 1.0.0 ใน title)
    Engine& engine = Engine::Get();
    engine.Init(1280, 720);

    // 2. Init ทุก Manager 
    LuaManager::Get().Init();
    PythonBridge::Get().Init("scripts");
    AudioManager::Get().Init();
    Live2DManager::Get().Init();
    LipSyncManager::Get().Init();
    LocalizationManager::Get().LoadLanguage("th");
    PluginManager::Get().Init();
    DLCManager::Get().Init();
    SettingsManager::Get().Load();

    // 3. Run เอนจิ้นหลัก (มี loop + ImGui + Update ทุกอย่าง)
    engine.Run();

    // 4. Cleanup
    engine.Shutdown();
    return 0;
}
