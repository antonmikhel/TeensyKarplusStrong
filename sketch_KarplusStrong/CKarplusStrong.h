#include <Audio.h>
#include <AudioStream.h>

#define FS 44100
#define DEFAULT_FREQ 100
#define MAX_INT 32767
#define MIN_INT -32768
#define NUM_BLOCKS 128

typedef int16_t int16;

struct OSCMix 
{
    OSCMix() : sine(0.0f), saw(0.0f), tri(0.0f), square(0.0f), noise(0.0f) {}
    OSCMix(float s, float w, float t, float q, float n) :
        sine(s), saw(w), tri(t), square(q), noise(n) {} 
    float sine;
    float saw;
    float tri;
    float square;
    float noise;
};

class KarplusStrongString : public AudioStream
{
public:
    KarplusStrongString();
    KarplusStrongString(int16 freq);


    void            setMix(OSCMix mix){ m_mix = mix; };
    void            pluck(float velocity);
    void            setFreq(int16 freq);
    void            setDecay(float d);
    int16           tick();
    virtual void    update();

private:
    void            leftShiftBuffer();
    int16           randInt();

    OSCMix          m_mix;
    int16           m_numSamples;
    int16*          m_KSBuffer;
    bool            m_mode = false;
    int16           m_freq;
    float           m_decayFactor = 0.996f;
    audio_block_t*  m_audioBlock;

    int16           m_bufferIndex = 0;
    int16           m_ticks = 0;

    int16           m_randRangeMin;
    int16           m_randRangeMax;
    int16           m_randRangeSize;

    bool            m_hasBeenPlucked = false;
};
