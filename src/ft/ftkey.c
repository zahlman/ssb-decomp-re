#include <ft/fighter.h>

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x80115B10
void ftKeyProcessInputSequence(GObj *fighter_gobj)
{
    FTStruct *fp = ftGetStruct(fighter_gobj);
    FTComputerInput *cp = &fp->input.cp;
    FTKey *key = &fp->key;

    if (key->input_seq != NULL)
    {
        if (key->input_wait != 0)
        {
            key->input_wait--;
        }
        while (TRUE)
        {
            if ((key->input_seq == NULL) || (key->input_wait > 0))
            {
                break;
            }
            else key->input_wait = key->input_seq->command.param;

            switch (key->input_seq->command.opcode)
            {
            case nFTKeyCommandEnd:
                key->input_seq = NULL;
                break;

            case nFTKeyCommandButton:
                key->input_seq++;

                cp->button_inputs = FTKeyGetButtons(key->input_seq);

                key->input_seq++;
                break;

            case nFTKeyCommandStick:
                key->input_seq++;

                cp->stick_range.x = FTKeyGetStickRange(key->input_seq)->x;
                cp->stick_range.y = FTKeyGetStickRange(key->input_seq)->y;

                key->input_seq++;
                break;
            }
        }
    }
}
