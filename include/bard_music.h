#ifndef GUARD_BARD_MUSIC_H
#define GUARD_BARD_MUSIC_H

// The maximum number of BardSoundTemplates/BardSounds there can be for each easy chat word.
#define MAX_BARD_SOUNDS_PER_WORD 6

// The number of pitch tables there are for each pitch table size (see sPitchTables).
#define NUM_BARD_PITCH_TABLES_PER_SIZE 5

// TODO: Fix all these to be up to date with upstream,
// but right now, I don't want to.
// This struct describes which phoneme song to play for the sound, and whether to
// make any adjustments to its length or volume. Very few sounds make any adjustments.
struct BardSoundTemplate
{
    /*0x00*/ u8 songLengthId;
    /*0x01*/ s8 songLengthOffset;
    /*0x02*/ u16 unused; // Only set on EC_WORD_WAAAH, and never read.
    /*0x04*/ s16 volume;
    /*0x06*/ u16 unused2;
};

// This is the length and pitch to play the phoneme song at.
// These will be calculated in 'CalcWordSounds'.
struct BardSound
{
    /*0x00*/ u16 length;
    /*0x02*/ u16 pitch;
};

struct BardSong
{
    /*0x00*/ u8 currWord;
    /*0x01*/ u8 currPhoneme;
    /*0x02*/ u8 phonemeTimer;
    /*0x03*/ u8 state;
    /*0x04*/ s16 length;
    /*0x06*/ u16 volume;
    /*0x08*/ s16 pitch;
    /*0x0A*/ s16 voiceInflection;
    /*0x0C*/ u16 lyrics[6];
    /*0x18*/ struct BardSound phonemes[6];
    /*0x30*/ const struct BardSoundTemplate *sound;
};

extern const u16 gNumBardWords_Species;
extern const u16 gNumBardWords_Moves;

const struct BardSoundTemplate *GetWordSoundTemplates(u16 easyChatWord);
void CalcWordSounds(struct BardSong *song, u16 pitchTableIndex);

#endif //GUARD_BARD_MUSIC_H
