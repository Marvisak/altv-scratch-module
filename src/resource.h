#pragma once

#include "main.h"

class ScratchResource : public alt::IResource::Impl {
    alt::IResource* resource;
public:
    ScratchResource(alt::IResource* resource) : resource{resource} {}
    bool Start() override;

    bool Stop() override {
        return true;
    }
    bool OnEvent(const alt::CEvent* event) override {
        return true;
    }

    void OnTick() override {
    }

    void OnCreateBaseObject(alt::Ref<alt::IBaseObject> object) override {
    }

    void OnRemoveBaseObject(alt::Ref<alt::IBaseObject> object) override {
    }
};