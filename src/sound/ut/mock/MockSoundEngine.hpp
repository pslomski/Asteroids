#include <gmock/gmock.h>

#include "sound/SoundEngine.hpp"

namespace sound
{
class MockSoundEngine : public SoundEngine
{
public:
    MOCK_METHOD(bool, Open, (), (override));
    MOCK_METHOD(void, Close, (), (override));
    MOCK_METHOD(void, SetVolume, (float), (override));
    MOCK_METHOD(float, GetVolume, (), (override));
    MOCK_METHOD(void, Mute, (), (override));
    MOCK_METHOD(void, Unmute, (), (override));
    MOCK_METHOD(bool, InitSound, (), (override));
    MOCK_METHOD(void, FreeSound, (), (override));
};
} // namespace sound
