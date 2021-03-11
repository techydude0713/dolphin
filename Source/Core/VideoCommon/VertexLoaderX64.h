// Copyright 2015 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include "Common/CommonTypes.h"
#include "Common/x64Emitter.h"
#include "VideoCommon/VertexLoaderBase.h"

enum class VertexComponentFormat;
enum class ComponentFormat;
enum class ColorFormat;

class VertexLoaderX64 : public VertexLoaderBase, public Gen::X64CodeBlock
{
public:
  VertexLoaderX64(const TVtxDesc& vtx_desc, const VAT& vtx_att);

protected:
  bool IsInitialized() override { return true; }
  int RunVertices(DataReader src, DataReader dst, int count) override;

private:
  u32 m_src_ofs = 0;
  u32 m_dst_ofs = 0;
  Gen::FixupBranch m_skip_vertex;
  Gen::OpArg GetVertexAddr(int array, VertexComponentFormat attribute);
  int ReadVertex(Gen::OpArg data, VertexComponentFormat attribute, ComponentFormat format,
                 int count_in, int count_out, bool dequantize, u8 scaling_exponent,
                 AttributeFormat* native_format);
  void ReadColor(Gen::OpArg data, VertexComponentFormat attribute, ColorFormat format);
  void GenerateVertexLoader();
};
