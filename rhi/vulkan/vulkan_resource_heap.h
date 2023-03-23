#ifndef TIGINE_RHI_VULKAN_VULKAN_RESOURCE_HEAP_H_
#define TIGINE_RHI_VULKAN_VULKAN_RESOURCE_HEAP_H_

#include "interface/i_resource_heap.h"

#include "vulkan/vulkan_common.h"

namespace tigine { namespace rhi {
class VulkanResourceHeap : public IResourceHeap {
public:
    VulkanResourceHeap(const VulkanContextInfo &context, const ResourceHeapDesc &desc);
    ~VulkanResourceHeap();

    VkPipelineLayout *getVkPipelineLayout() { return &vk_pipeline_layout_; }
    VkDescriptorSet  *getVkDescriptorSet() { return &vk_descriptor_set_; }

private:
    VkDevice *vk_device_;

    VkDescriptorSetLayout vk_descriptor_set_layout_;
    VkDescriptorPool      vk_descriptor_pool_;
    VkDescriptorSet       vk_descriptor_set_; 
    VkPipelineLayout      vk_pipeline_layout_;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_VULKAN_VULKAN_RESOURCE_HEAP_H_