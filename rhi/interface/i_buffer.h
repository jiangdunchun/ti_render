#ifndef TIGINE_RHI_INTERFACE_I_BUFFER_H_
#define TIGINE_RHI_INTERFACE_I_BUFFER_H_

#include "interface/i_common.h"
#include "interface/i_resource.h"

namespace tigine { namespace rhi {
enum class BufferKind {
    Uniform,
    Vertices,
    Indices,
};

struct BufferDataDesc {
    TULong data_size;
    void  *data;
    TULong offset = 0;
};

struct BufferDesc {
    BufferKind     kind;
    TULong         buffer_size;
    // no source data if the .data is nullptr
    BufferDataDesc src_data = { 0, nullptr };
};

class IBuffer : public IResource {
public:
    virtual ~IBuffer() = default;

    ResourceKind getResourceKind() const override final { return ResourceKind::Buffer; }

    virtual void updateData(const BufferDataDesc &desc) = 0;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_BUFFER_H_
