#ifndef _EFDEF_H_
#define _EFDEF_H_

typedef enum efKind
{
    nEFKindDamageNormal,               // Texture displayed when hit by an attack of the normal element
    nEFKindFlameLR = 6,                // Flame whose velocity depends on the user's facing direction
    nEFKindFlameRandom,                // Small flame texture that scatters
    nEFKindFlameStatic,                // Small flame texture that is stationary?
    nEFKindShockSmall = 10,            // Texture displayed when hit by an attack of the electric element; small shockwave texture
    nEFKindDustLight,                  // e.g. Light landing (no fast fall)
    nEFKindDustLightRapid,             // Faster version of DustLight?
    nEFKindDustHeavyDouble,            // Two instances of heavy dust clouds
    nEFKindDustHeavyDoubleRapid,       // Two instances of faster heavy dust clouds?
    nEFKindDustHeavy,                  // Single instance of heavy dust cloud
    nEFKindDustHeavyReverse,           // Single instance of direction-flipped heavy dust cloud
    nEFKindDustExpandLarge,            // Large dust cloud that grows in size
    nEFKindDustExpandSmall,            // Small dust cloud that grows in size
    nEFKindDustDashSmall,              // Small (actually pretty large) dust kickup behind user
    nEFKindDustDashLarge,              // Large dust kickup behind user
    nEFKindDamageFlyOrbs,              // Cyan orbs that fly outward
    nEFKindImpactWave,                   // Green impact shockwave that is created when a character slams into collision
    nEFKindStarRodSpark,               // Star Rod / Star projectile sparkles 
    nEFKindDamageFlySparks,            // Shows sometimes when getting hit
    nEFKindDamageFlySparksReverse,     // LR-inverted version
    nEFKindDamageFlyMDust,             // Metal dust effect, shows sometimes when getting hit
    nEFKindDamageFlyMDustReverse,      // LR-inverted version
    nEFKindSparkleWhite,               // Plays when a flame (Fire Flower, Charizard, Charmander) or when Pikachu's Thunder hits the ground
    nEFKindSparkleWhiteMultiExplode,   // e.g. Kirby's F-Throw explosion
    nEFKindSparkleWhiteMulti,          // I can't really trigger this but it's just SparkleWhiteMultiExplode without the explosion; seems to be exclusive to fighter scripts
    nEFKindSparkleWhiteScale,          // Most common white sparkle, plays during many moves such as Smash attacks
    nEFKindQuakeM0,                    // Creates an earthquake of magnitude 0
    nEFKindQuakeM1,                    // Creates an earthquake of magnitude 1
    nEFKindQuakeM2,                    // Creates an earthquake of magnitude 2
    nEFKindFireSpark = 37,             // Not sure who uses this
    nEFKindFuraSparkle = 40,           // Dizzy sparkles after shield break
    nEFKindPsionic,                    // Ness PSI sparkles
    nEFKindFlashSmall,                 // Expanding green circle, plays when teching
    nEFKindFlashMiddle,                // Other expanding green circle, plays when grabbing ledge
    nEFKindFlashLarge,                 // Large expanding green circle, plays when grabbing Star Man?
    nEFKindBoxSmash = 46,              // Crate / Barrel smash effect
    nEFKindCrashTheGame,               // Literally crashes the game; this takes an argument which acts as a timer; must be extra specific, during a certain scene
    nEFKindKirbyStar = 54,             // Can be created manually but this plays when Kirby makes impact with stage collision
    nEFKindThunderHit = 70,            // Pikachu's Thunder self-hit
    nEFKindRipple,                     // Pikachu's Quick-Attack, Ness's PSI Magnet, Mew spawn, etc.
    nEFKindChargeSparkle = 73,         // Fully charged Neutral Special, e.g. DK or Samus
    nEFKindHealSparkles,               // Used for Heart, Maxim Tomato and Star Man
    nEFKindYoshiEggRoll = 87,
    nEFKindSingNote = 90,
    nEFKindEggBreak

} efKind;

typedef struct efStruct			efStruct;
typedef struct efTransform		efTransform;	// This is Temp001 in halsprite.c
typedef struct efParticle		efParticle;		// This is Temp002 in halsprite.c
typedef struct efGenerator		efGenerator;	// This is Temp003 in halsprite.c
typedef struct efCreateDesc		efCreateDesc;

#endif
