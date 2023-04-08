#ifndef TIGINE_RHI_INTERFACE_I_COMMON_H_
#define TIGINE_RHI_INTERFACE_I_COMMON_H_

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

#define RHI_THROW(msg) throw std::runtime_error("tigine::rhi " + std::string(msg))

namespace tigine { namespace rhi {
typedef std::uint8_t  TChar;
typedef std::uint16_t TUShort;
typedef std::int16_t  TShort;
typedef std::uint32_t TUInt;
typedef std::int32_t  TInt;
typedef std::uint64_t TULong;
typedef std::int64_t  TLong;
typedef std::string   TString;
#define TVector std::vector

class NonCopyable {
public:
    NonCopyable(const NonCopyable &)            = delete;
    NonCopyable &operator=(const NonCopyable &) = delete;

    virtual ~NonCopyable() = default;

protected:
    NonCopyable() = default;
};

enum class DataFormat {
    Undefined,
    A8UNorm,
    R8UNorm,
    R8SNorm,
    R8UInt,
    R8SInt,
    R16UNorm,
    R16SNorm,
    R16UInt,
    R16SInt,
    R16Float,
    R32UInt,
    R32SInt,
    R32Float,
    R64Float,
    RG8UNorm,
    RG8SNorm,
    RG8UInt,
    RG8SInt,
    RG16UNorm,
    RG16SNorm,
    RG16UInt,
    RG16SInt,
    RG16Float,
    RG32UInt,
    RG32SInt,
    RG32Float,
    RG64Float,
    RGB8UNorm,
    RGB8UNorm_sRGB, 
    RGB8SNorm,
    RGB8UInt,
    RGB8SInt,
    RGB16UNorm, 
    RGB16SNorm, 
    RGB16UInt, 
    RGB16SInt,
    RGB16Float,
    RGB32UInt,
    RGB32SInt,
    RGB32Float,
    RGB64Float,
    RGBA8UNorm,
    RGBA8UNorm_sRGB,
    RGBA8SNorm,
    RGBA8UInt,
    RGBA8SInt,
    RGBA16UNorm,
    RGBA16SNorm,
    RGBA16UInt,
    RGBA16SInt,
    RGBA16Float,
    RGBA32UInt,
    RGBA32SInt,
    RGBA32Float,
    RGBA64Float,
    BGRA8UNorm,
    BGRA8UNorm_sRGB,
    BGRA8SNorm,
    BGRA8UInt,
    BGRA8SInt,
    RGB10A2UNorm,
    RGB10A2UInt,
    RG11B10Float,
    RGB9E5Float,
    D16UNorm,
    D24UNormS8UInt, 
    D32Float, 
    D32FloatS8X24UInt,
    BC1UNorm,
    BC1UNorm_sRGB,
    BC2UNorm,
    BC2UNorm_sRGB,
    BC3UNorm,
    BC3UNorm_sRGB,
    BC4UNorm,
    BC4SNorm,
    BC5UNorm,
    BC5SNorm,
};
}} // namespace tigine::rhi

#endif // !TIGINE_RHI_INTERFACE_I_COMMON_H_
