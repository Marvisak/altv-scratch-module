#pragma once

#include "main.h"
#include "resource.h"

class ScratchRuntime : public alt::IScriptRuntime {
public:
    ScratchRuntime();
    alt::IResource::Impl* CreateImpl(alt::IResource* resource) override;
    void DestroyImpl(alt::IResource::Impl* impl) override;
    void OnDispose() override;
    void OnTick() override {
    }
};