#pragma once

#include <QtCore/QDataStream>
#include <memory>

#include "PoolObject.h"
#include "Sequence.h"
#include "common/Event.h"

namespace MaximCompiler {
    class Transaction;
}

namespace AxiomModel {

    class ModelRoot;

    class ReferenceMapper;

    class ModelObject : public PoolObject {
    public:
        enum class ModelType { NODE_SURFACE, NODE, CONTROL_SURFACE, CONTROL, CONNECTION };

        AxiomCommon::Event<> removed;

        ModelObject(ModelType modelType, const QUuid &uuid, const QUuid &parentUuid, ModelRoot *root);

        virtual bool buildOnRemove() const { return false; }

        ModelType modelType() const { return _modelType; }

        ModelRoot *root() const { return _root; }

        virtual Sequence<ModelObject *> links();

        virtual void build(MaximCompiler::Transaction *transaction) {}

        void remove() override;

    private:
        ModelType _modelType;
        ModelRoot *_root;
    };
}
