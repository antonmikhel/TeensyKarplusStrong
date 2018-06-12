#include <Audio.h>
#include <AudioStream.h>

#define SAMPLE_RATE 44100
#define DEFAULT_NUM_BLOCKS 129
#define MIN_INT16 -32768
#define MAX_INT16 32768

typedef struct OSCmix {
    float sine = 0.0f;
    float saw = 0.0f;
    float tri = 0.0f;
    float square = 0.0f;
    float noise = 0.0f;
};

class KarplusStrongString : public AudioStream
{
public:
    KarplusStrongString() : AudioStream(0, NULL) {};
    KarplusStrongString(int freq) : AudioStream(0, NULL), m_freq(freq)
    {
        m_numSamples = SAMPLE_RATE / freq;
        m_KSBuffer = new int16_t[m_numSamples];
    };

    void pluck(float velocity);
    void setFreq(int freq);
    virtual void update();

private:
    OSCmix          m_mix;
    int16_t         m_numSamples;
    int16_t*        m_KSBuffer;
    bool            m_mode = false;
    int             m_freq;
    float           m_decayFactor = 0.996;
    audio_block_t*  m_audioBlock;

    int             m_bufferIndex;
    //TODO: floats must be 16 bit too
};