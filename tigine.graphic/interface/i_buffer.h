#ifndef TIGINE_GRAPHIC_INTERFACE_I_BUFFER_H_
#define TIGINE_GRAPHIC_INTERFACE_I_BUFFER_H_

#include "interface/i_common.h"
#include "interface/i_resource.h"

namespace tigine { namespace graphic {
enum BufferKind {
    BK_Vertices = 1 << 0,
    BK_Indices  = 1 << 1,
};

struct BufferDesc {
    TUInt  kinds = 0;
    TULong data_size  = 0;
    void  *data  = nullptr;
};

class IBuffer : public IResource {
public:
    ResourceKind getResourceKind() const override final { return ResourceKind::Buffer; }
    virtual void updateData(TULong data_size, void *data) = 0;
};
}} // namespace tigine::graphic

#endif // !TIGINE_GRAPHIC_INTERFACE_I_BUFFER_H_
