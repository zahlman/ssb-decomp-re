/*====================================================================
 * cspsetfxmix.c
 *
 * Copyright 1995, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *====================================================================*/

#include <PR/libaudio.h>

#if 0
// Needs -O3
// ALCSPlayer Needs 8 bytes of padding before evtq to match
void alCSPSetChlFXMix(ALCSPlayer *seqp, u8 chan, u8 fxmix)
{
    ALEvent       evt; 

    evt.type            = AL_SEQP_MIDI_EVT;
    evt.msg.midi.ticks  = 0;
    evt.msg.midi.status = AL_MIDI_ControlChange | chan;
    evt.msg.midi.byte1  = AL_MIDI_FX1_CTRL;
    evt.msg.midi.byte2  = fxmix;
                    
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/libultra/n_audio/cspsetfxmix/alCSPSetChlFXMix.s")
#endif
