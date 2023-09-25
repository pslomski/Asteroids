target_sources(${ASTER_LIB}
    PRIVATE
        MusicEngineBass.cpp MusicEngineBass.hpp
        SoundEngineBass.cpp SoundEngineBass.hpp
        SoundObjectBass.cpp SoundObjectBass.hpp
        SoundSamplesBass.cpp SoundSamplesBass.hpp
)

add_executable(
  TestSoundSamplesBass
  ut/TestSoundSamplesBass.cpp
  SoundSamplesBass.cpp SoundSamplesBass.hpp
)
target_link_libraries(
  TestSoundSamplesBass
  GTest::gtest_main
  ${BASS_LIBRARIES}
)
add_test(TestSoundSamplesBass TestSoundSamplesBass)
