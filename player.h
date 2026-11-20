#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

void playFile(const fs::path& filePath)
{
    ma_result result;
    ma_decoder decoder;
    ma_device_config deviceConfig;
    ma_device device;

    result = ma_decoder_init_file(filePath.string().c_str(), NULL, &decoder);
    if (result != MA_SUCCESS) {
        std::cerr << "Could not load file: " << filePath.string() << std::endl;
        return;
    }

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = decoder.outputFormat;
    deviceConfig.playback.channels = decoder.outputChannels;
    deviceConfig.sampleRate = decoder.outputSampleRate;
    deviceConfig.dataCallback = [](ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
        ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
        if (pDecoder == NULL)
            return;
        ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);
        (void)pInput;
    };
    deviceConfig.pUserData = &decoder;

    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        std::cerr << "Failed to open playback device.\n" << std::endl;
        ma_decoder_uninit(&decoder);
        return;
    }

    if (ma_device_start(&device) != MA_SUCCESS) {
        std::cerr << "Failed to start playback device.\n" << std::endl;
        ma_device_uninit(&device);
        ma_decoder_uninit(&decoder);
        return;
    }

    std::cout << "Press Enter to quit...";
    int ok = 0;
    while (ok == 0)
    {
        std::cin >> ok;
    }

    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
}