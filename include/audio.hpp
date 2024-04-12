#ifndef AUDIO_H
#define AUDIO_H

#include "helper.hpp"
#include "miniaudio.hpp"
#include <stdexcept>
#include <string>

class Audio
{
  public:
    Audio(std::string filename);
    ~Audio();
    void play();

  private:
    ma_result result;
    ma_decoder decoder;
    ma_device_config deviceConfig;
    ma_device device;
};

#endif