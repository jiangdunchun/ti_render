#ifndef TIGINE_RHI_GL430_GL430_RENDER_SYSTEM_H_
#define TIGINE_RHI_GL430_GL430_RENDER_SYSTEM_H_

#include "interface/i_render_system.h"

#include "gl430/gl430_buffer.h"
#include "gl430/gl430_buffer_array.h"
#include "gl430/gl430_command_buffer.h"
#include "gl430/gl430_command_queue.h"
#include "gl430/gl430_pipeline_state.h"
#include "gl430/gl430_render_context.h"
#include "gl430/gl430_shader.h"
#include "gl430/gl430_shader_program.h"

namespace tigine { namespace rhi {
class GL430RenderSystem : public IRenderSystem {
public:
    GL430RenderSystem() { command_queue_ = new GL430CommandQueue(); }
    ~GL430RenderSystem() { delete command_queue_; }

    IRenderContext  *createRenderContext(const RenderContextDesc &desc) override { return new GL430RenderContext(desc); }
    void             release(IRenderContext *render_context) override { delete render_context; }
    IShader         *createShader(const ShaderDesc &desc) override { return new GL430Shader(desc); }
    void             release(IShader *shader) override { delete shader; }
    IShaderProgram  *createShaderProgram(const ShaderProgramDesc &desc) override { return new GL430ShaderProgram(desc); }
    void             release(IShaderProgram *shader_program) override { delete shader_program; }
    IBuffer         *createBuffer(const BufferDesc &desc, void *data) override { return new GL430Buffer(desc, data); }
    void             release(IBuffer *buffer) override { delete buffer; }
    IBufferArray    *createBufferArray(const BufferArrayDesc &desc) override { return new GL430BufferArray(desc); }
    void             release(IBufferArray *buffer_array) override { delete buffer_array; }
    ICommandQueue   *getCommandQueue() override { return command_queue_; }
    ICommandBuffer  *createCommandBuffer() override { return new GL430CommandBuffer(); }
    void             release(ICommandBuffer *command_buffer) override { delete command_buffer; }
    ITexture        *createTexture(const TextureDesc &desc) override { return nullptr; }
    void             release(ITexture *render_target) override {}
    IResourceHeap   *CreateResourceHeap(const ResourceHeapDesc &desc) { return nullptr; }
    void             release(IResourceHeap *resource_heap) {}
    IRenderPass     *CreateRenderPass(const RenderPassDesc &desc) { return nullptr; }
    void             release(IRenderPass *render_pass) {}
    IRenderTarget   *createRenderTarget(const RenderTargetDesc &desc) override { return nullptr; }
    void             release(IRenderTarget *render_target) override {}
    IPipelineLayout *createPipelineLayout(const PipelineLayoutDescriptor &desc) override { return nullptr; }
    void             release(IPipelineLayout *pipeline_layout) override {}
    IPipelineState  *createPipelineState(const PipelineStateDesc &desc) override { return new GL430PipelineState(desc); }
    void             release(IPipelineState *pipeline) override { delete pipeline; }

private:
    GL430CommandQueue *command_queue_ = nullptr;
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_GL430_GL430_RENDER_SYSTEM_H_
