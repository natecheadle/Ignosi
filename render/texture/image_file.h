#pragma once

#include <filesystem>

#include "iimage_file.h"

namespace ignosi::render {
class ImageFile : public IImageFile {
  int m_Width;
  int m_Height;
  int m_Channels;
  int m_Format;
  unsigned char* m_pData;

 public:
  ImageFile(const std::filesystem::path& path,
            bool flipVerticallyOnLoad = true);
  ~ImageFile();

  const unsigned char* GetData() const { return m_pData; }
  int GetWidth() const { return m_Width; }
  int GeHeight() const { return m_Width; }
  int GetChannels() const { return m_Width; }
  int GetFormat() const { return m_Format; }
};
}  // namespace ignosi::render
