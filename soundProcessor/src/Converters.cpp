#include "Converters.h"
#include <cstdint>

void TMuteConverter::Convert(IFormat &file, std::vector<std::string> &instruction) const {
    size_t curOutPos = file.getCurrentOutPos();
    size_t startTime = std::stoull(instruction[instruction.size() - 2]);
    size_t endTime = std::stoull(instruction[instruction.size() - 1]);

    size_t startSample = file.getSampleRate() * startTime;
    size_t endSample = file.getSampleRate() * endTime;

    size_t lastSample = file.getLastSample();
    if (startSample >= lastSample)
        return;
    if (endSample > lastSample) endSample = lastSample;

    file.setOutPos(sizeof(int16_t) * startSample, std::ios::beg);

    for (size_t i = startSample; i < endSample; ++i)
        file.sendSample(0);

    file.setOutPos(curOutPos);
}

void TMixConverter::Convert(IFormat &file, std::vector<std::string> &instruction) const {
    size_t curInPos = file.getCurrentInPos();
    size_t curOutPos = file.getCurrentOutPos();

    size_t startTime = std::stoull(instruction[2]);
    size_t endTime = std::stoull(instruction[3]);
    size_t startSample = file.getSampleRate() * startTime;
    size_t endSample = file.getSampleRate() * endTime;

    size_t lastSample = file.getLastSample();
    if (startSample >= lastSample) return;
    if (endSample > lastSample) endSample = lastSample;

    file.setOutPos(sizeof(int16_t) * startSample, std::ios::beg);
    file.setInPos(sizeof(int16_t) * startSample, std::ios::beg);

    for (size_t i = startSample; i < endSample; ++i) {
        int16_t sample1 = file.getSample();
        int16_t sample2 = file.getExtraSample();
        int32_t mixed = static_cast<int32_t>(sample1) + static_cast<int32_t>(sample2);
        int16_t result = static_cast<int16_t>(mixed / 2);

        file.setOutPos(-sizeof(int16_t), std::ios::cur);
        file.sendSample(result);
    }

    file.setInPos(curInPos);
    file.setOutPos(curOutPos);
}

void TBassBoostConverter::Convert(IFormat &file, std::vector<std::string> &instruction) const {
    size_t curOutPos = file.getCurrentOutPos();

    double gain = std::stod(instruction[2]);
    size_t startTime = std::stoull(instruction[3]);
    size_t endTime   = std::stoull(instruction[4]);

    size_t startSample = file.getSampleRate() * startTime;
    size_t endSample   = file.getSampleRate() * endTime;

    size_t lastSample = file.getLastSample();
    if (startSample >= lastSample) return;
    if (endSample > lastSample) endSample = lastSample;

    file.setOutPos(sizeof(int16_t) * startSample, std::ios::beg);

    for (size_t i = startSample; i < endSample; ++i) {
        int16_t sample = file.getSample();
        int32_t boosted = static_cast<int32_t>(sample * gain);

        if (boosted > INT16_MAX) boosted = INT16_MAX;
        if (boosted < INT16_MIN) boosted = INT16_MIN;

        file.setOutPos(-sizeof(int16_t), std::ios::cur);
        file.sendSample(static_cast<int16_t>(boosted));
    }

    file.setOutPos(curOutPos);
}







