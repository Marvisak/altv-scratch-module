#include "runtime.h"

ScratchRuntime::ScratchRuntime() {
    Py_Initialize();
    PyObject* sys = PyImport_ImportModule("sys");
    PyObject* pyPath = PyObject_GetAttrString(sys, "path");
    PyList_Append(pyPath, PyUnicode_FromString("modules\\scratch-module"));
}

void ScratchRuntime::OnDispose() {
    Py_Finalize();
}

alt::IResource::Impl* ScratchRuntime::CreateImpl(alt::IResource *resource) {
    return new ScratchResource(resource);
}

void ScratchRuntime::DestroyImpl(alt::IResource::Impl* impl) {
    auto* resource = dynamic_cast<ScratchResource*>(impl);
    if (resource != nullptr) delete resource;
}
