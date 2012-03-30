#ifndef GAME_SOUND_SOUND_H
#define GAME_SOUND_SOUND_H

#include <OgreVector3.h>

namespace MWSound
{
    class Sound
    {
        virtual void update() = 0;

        Sound& operator=(const Sound &rhs);
        Sound(const Sound &rhs);

    protected:
        Ogre::Vector3 mPos;
        float mVolume; /* NOTE: Real volume = mVolume*mBaseVolume */
        float mBaseVolume;
        float mMinDistance;
        float mMaxDistance;

    public:
        virtual void stop() = 0;
        virtual bool isPlaying() = 0;
        void setVolume(float volume) { mVolume = volume; }

        Sound() : mPos(0.0f, 0.0f, 0.0f)
                , mVolume(1.0f)
                , mBaseVolume(1.0f)
                , mMinDistance(20.0f) /* 1 * min_range_scale */
                , mMaxDistance(12750.0f) /* 255 * max_range_scale */
        { }
        virtual ~Sound() { }

        friend class OpenAL_Output;
        friend class SoundManager;
    };
}

#endif
