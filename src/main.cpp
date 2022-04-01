#include "main.h"
#include <version/version.h>
#include "runtime.h"

EXPORT bool altMain(alt::ICore* core) {
    alt::ICore::SetInstance(core);

    auto runtime = new ScratchRuntime();
    core->RegisterScriptRuntime("scratch", runtime);

    core->LogInfo("Loaded scratch module");
    return true;
}

EXPORT const char* GetSDKHash() {
    return ALT_SDK_VERSION;
}
