#include "Runtime.h"

#include "Frontend.h"
#include "Jit.h"

using namespace MaximCompiler;

Runtime::Runtime(bool includeUi, bool minSize, Jit *jit)
    : OwnedObject(MaximFrontend::maxim_create_runtime(includeUi, minSize, jit->get()),
                  &MaximFrontend::maxim_destroy_runtime) {}

uint64_t Runtime::nextId() {
    return MaximFrontend::maxim_allocate_id(get());
}

void Runtime::runUpdate() {
    MaximFrontend::maxim_run_update(get());
}

void Runtime::setBpm(float bpm) {
    MaximFrontend::maxim_set_bpm(get(), bpm);
}

void Runtime::setSampleRate(float sampleRate) {
    MaximFrontend::maxim_set_sample_rate(get(), sampleRate);
}

void Runtime::commit(MaximCompiler::Transaction transaction) {
    MaximFrontend::maxim_commit(get(), transaction.release());
}

void *Runtime::getPortalPtr(size_t portal) {
    return MaximFrontend::maxim_get_portal_ptr(get(), portal);
}

void *Runtime::getRootPtr() {
    return MaximFrontend::maxim_get_root_ptr(get());
}

void *Runtime::getNodePtr(uint64_t surface, void *surfacePtr, size_t node) {
    return MaximFrontend::maxim_get_node_ptr(get(), surface, surfacePtr, node);
}

void *Runtime::getSurfacePtr(void *nodePtr) {
    return MaximFrontend::maxim_get_surface_ptr(nodePtr);
}

void *Runtime::getBlockPtr(void *nodePtr) {
    return MaximFrontend::maxim_get_block_ptr(nodePtr);
}

MaximFrontend::ControlPointers Runtime::getControlPtrs(uint64_t block, void *blockPtr, size_t control) {
    return MaximFrontend::maxim_get_control_ptrs(get(), block, blockPtr, control);
}
