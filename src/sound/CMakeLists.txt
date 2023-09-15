target_sources(${ASTER_LIB}
    PRIVATE
        ObjectSound.cpp ObjectSound.hpp
        Sound.cpp Sound.hpp
        SoundEngine.hpp
)

add_subdirectory(bass)
