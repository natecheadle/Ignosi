#pragma once

namespace ignosi::render {
class IImageFile {
 public:
  IImageFile() = default;
  virtual ~IImageFile() = default;

  virtual const unsigned char* GetData() const = 0;
  virtual int GetWidth() const = 0;
  virtual int GeHeight() const = 0;
  virtual int GetChannels() const = 0;
  virtual int GetFormat() const = 0;
};
}  // namespace ignosi::render
