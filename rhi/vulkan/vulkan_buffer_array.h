#ifndef TIGINE_RHI_VULKAN_VULKAN_BUFFER_ARRAY_H_
#define TIGINE_RHI_VULKAN_VULKAN_BUFFER_ARRAY_H_

#include "interface/i_buffer_array.h"

#include "vulkan/vulkan_common.h"

namespace tigine { namespace rhi {
class VulkanBuffer;
class VulkanBufferArray : public IBufferArray {
public:
    VulkanBufferArray(const VulkanContextInfo &context, const BufferArrayDesc &desc);
    ~VulkanBufferArray();

    bool                                  hasIndices() const { return has_indices_; }
    VulkanBuffer                         *getVerticesBuffer() { return vertices_buffer_; }
    VulkanBuffer                         *getIndicesBuffer() { return indices_buffer_; }
    IndexKind                             getIndexKind() { return index_kind_; }
    VkPipelineVertexInputStateCreateInfo *getVkPipelineVertexInputStateCreateInfo() { return &vk_pipeline_vertex_input_state_create_info_; }

private:
    VulkanBuffer *vertices_buffer_;
    VulkanBuffer *indices_buffer_ = nullptr;

    VkPipelineVertexInputStateCreateInfo           vk_pipeline_vertex_input_state_create_info_;
    std::vector<VkVertexInputBindingDescription>   vk_bindings_desc_;
    std::vector<VkVertexInputAttributeDescription> vk_attributes_desc_;
    bool                                           has_indices_ = false;
    IndexKind                                      index_kind_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_BUFFER_ARRAY_H_
