#include <ef/effect.h>

// Equivalent file in Pokémon Snap: 4D880.c

#define LBPARTICLE_BANKS_NUM_MAX 8

// // // // // // // // // // // //
//                               //
//   GLOBAL / STATIC VARIABLES   //
//                               //
// // // // // // // // // // // //

// 0x800D6350
efParticle *sLBParticleStructsAllocFree;

// 0x800D6358
efParticle *sLBParticleStructsAllocLinks[16];

// 0x800D6398
efGenerator *sLBParticleGeneratorsAllocFree;

// 0x800D639C
efGenerator *sLBParticleGeneratorsAllocLinks[9];

// 0x800D63C0
s32 sLBParticleScriptBanksNum[LBPARTICLE_BANKS_NUM_MAX];

// 0x800D63E0
s32 sLBParticleTextureBanksNum[LBPARTICLE_BANKS_NUM_MAX];

// 0x800D6400
efScript **sLBParticleScriptBanks[LBPARTICLE_BANKS_NUM_MAX];

// 0x800D6420
efTexture **sLBParticleTextureBanks[LBPARTICLE_BANKS_NUM_MAX];

// 0x800D6440
void (*sLBParticleGeneratorProcDefault)(efGenerator*, Vec3f*);

// 0x800D6444
void (*sLBParticleGeneratorProcSetup)(efGenerator*);

// 0x800D6448
u16 sLBParticleStructsUsedNum;

// 0x800D644A
u16 sLBParticleGeneratorsUsedNum;

// 0x800D644C
u16 sLBParticleTransformsUsedNum;

// 0x800D644E
u16 D_ovl0_800D644E;

// 0x800D6450
u16 D_ovl0_800D6450;

// 0x800D6452
u16 D_ovl0_800D6452;

// 0x800D6454
efTransform *sLBParticleTransformsAllocFree;

// 0x800D6458
efGenerator *sLBParticleGeneratorsCurrent;

// // // // // // // // // // // //
//                               //
//       INITIALIZED DATA        //
//                               //
// // // // // // // // // // // //

// 0x800D5D50
u8 dLBParticleColorDitherMode = G_CD_MAGICSQ;

// 0x800D5D54
u8 dLBParticleAlphaDitherMode = G_AD_PATTERN;

// 0x800D5D58
u16 dLBParticleCurrentGeneratorID = 0;

// 0x800D5D5C
u8 dLBParticleCurrentTransformID = 123;

// // // // // // // // // // // //
//                               //
//           FUNCTIONS           //
//                               //
// // // // // // // // // // // //

// 0x800CE040
s32 lbParticleAllocTransforms(s32 num, size_t size)
{
	efTransform *tfrm;
	s32 i;

	sLBParticleTransformsAllocFree = NULL;
	
	for (i = 0; i < num; i++)
	{
		tfrm = gsMemoryAlloc(size, 0x4);

		if (tfrm == NULL)
		{
			return i;
		}
		tfrm->next = sLBParticleTransformsAllocFree;
		sLBParticleTransformsAllocFree = tfrm;
	}
	sLBParticleTransformsUsedNum = 0;
	D_ovl0_800D6452 = 0;

	return i;
}

// 0x800CE0D8
efTransform* lbParticleGetTransform(u8 status, u16 generator_id)
{
	efTransform *tfrm = sLBParticleTransformsAllocFree;

	if (tfrm != NULL)
	{
        sLBParticleTransformsAllocFree = tfrm->next;
        tfrm->users_num = 1;
        tfrm->transform_id = dLBParticleCurrentTransformID;
        tfrm->proc_dead = NULL;

		tfrm->translate.x = tfrm->translate.y = tfrm->translate.z = 0.0F;
		tfrm->rotate.x = tfrm->rotate.y = tfrm->rotate.z = 0.0F;
		tfrm->scale.x = tfrm->scale.y = tfrm->scale.z = 1.0F;

		tfrm->transform_status = status;
		tfrm->generator_id = generator_id;

		sLBParticleTransformsUsedNum++;

		if (D_ovl0_800D6452 < sLBParticleTransformsUsedNum)
		{
			D_ovl0_800D6452 = sLBParticleTransformsUsedNum;
		}
	}
	return tfrm;
}

// 0x800CE188
void lbParticleEjectTransform(efTransform *tfrm)
{
	if (tfrm->proc_dead != NULL)
	{
		tfrm->proc_dead(tfrm);
	}
	tfrm->next = sLBParticleTransformsAllocFree;
	sLBParticleTransformsAllocFree = tfrm;

	sLBParticleTransformsUsedNum--;
}

// 0x800CE1DC
efTransform* lbParticleAddTransformForParticle(efParticle *ptcl, u8 status)
{
    ptcl->tfrm = lbParticleGetTransform(status, ptcl->generator_id);

	return ptcl->tfrm;
}

// 0x800CE218
efTransform* lbParticleAddTransformForGenerator(efGenerator* gtor, u8 status)
{
	gtor->tfrm = lbParticleGetTransform(status, gtor->generator_id);

	return gtor->tfrm;
}

// 0x800CE254
void lbParticleSetupBankID(s32 bank_id, efScriptDesc *script_desc, efTextureDesc *texture_desc)
{
	s32 i, j;

	if (bank_id >= LBPARTICLE_BANKS_NUM_MAX)
	{
		return;
	}
	sLBParticleScriptBanksNum[bank_id] = script_desc->scripts_num;
	sLBParticleTextureBanksNum[bank_id] = texture_desc->textures_num;

	sLBParticleScriptBanks[bank_id] = script_desc->scripts;
	sLBParticleTextureBanks[bank_id] = texture_desc->textures;

	for (i = 1; i <= sLBParticleScriptBanksNum[bank_id]; i++)
	{
		/* By default, the scripts array is populated with the offsets of the scripts
		 * in their respective file, so this is essentially making them into valid RAM pointers.
		 */
		script_desc->scripts[i - 1] = gcGetDataFromFile(efScript*, script_desc, script_desc->scripts[i - 1]);
	}
	for (i = 1; i <= sLBParticleTextureBanksNum[bank_id]; i++)
	{
		// Much like scripts, textures from the file are also being "pointerized" here.
		texture_desc->textures[i - 1] = gcGetDataFromFile(efTexture*, texture_desc, texture_desc->textures[i - 1]);
	}
	for (i = 0; i < sLBParticleTextureBanksNum[bank_id]; i++)
	{
		for (j = 0; j < sLBParticleTextureBanks[bank_id][i]->count; j++)
		{
			sLBParticleTextureBanks[bank_id][i]->data[j] = gcGetDataFromFile(void*, texture_desc, sLBParticleTextureBanks[bank_id][i]->data[j]);
		}
		if (sLBParticleTextureBanks[bank_id][i]->fmt == G_IM_FMT_CI)
		{
			if (sLBParticleTextureBanks[bank_id][i]->flags & 1)
			{
				// One palette after the images
				j = sLBParticleTextureBanks[bank_id][i]->count;

				sLBParticleTextureBanks[bank_id][i]->data[j] = gcGetDataFromFile(void*, texture_desc, sLBParticleTextureBanks[bank_id][i]->data[j]);
			}
			else for (j = sLBParticleTextureBanks[bank_id][i]->count; j < sLBParticleTextureBanks[bank_id][i]->count * 2; j++)
			{
				sLBParticleTextureBanks[bank_id][i]->data[j] = gcGetDataFromFile(void*, texture_desc, sLBParticleTextureBanks[bank_id][i]->data[j]);
			}
		}
	}
}

// Temporary
extern void lbParticleStructProcRun(GObj*);

// 0x800CE418
GObj* lbParticleAllocStructs(s32 num)
{
	s32 i;
	efParticle *ptcl;

	sLBParticleStructsAllocFree = NULL;

	for (i = 0; i < ARRAY_COUNT(sLBParticleStructsAllocLinks); i++)
	{
		sLBParticleStructsAllocLinks[i] = NULL;
	}
	for (i = num - 1; i >= 0; i--)
	{
		ptcl = gsMemoryAlloc(sizeof(*ptcl), 4);

		if (ptcl == NULL)
		{
			return NULL;
		}
		ptcl->next = sLBParticleStructsAllocFree;
		sLBParticleStructsAllocFree = ptcl;
	}
	sLBParticleStructsUsedNum = 0;
	D_ovl0_800D644E = 0;

	if (gcFindGObjByID(-6) != NULL)
	{
		return NULL;
	}
	return gcMakeGObjSPAfter(-6, lbParticleStructProcRun, 0, GOBJ_LINKORDER_DEFAULT);
}

// 0x800CE4E4
efParticle* lbParticleMakeStruct
(
	efParticle *this_ptcl,
	s32 bank_id,
	u32 flags,
	u16 texture_id,
	u8 *bytecode,
	s32 arg5,
	f32 pos_x,
	f32 pos_y,
	f32 pos_z,
	f32 vel_x,
	f32 vel_y,
	f32 vel_z,
	f32 mscale,
	f32 argD,
	f32 argE,
	u32 argF,
	efGenerator *gtor
)
{
	efParticle *new_ptcl;
	s32 i;

    new_ptcl = sLBParticleStructsAllocFree;
    
    if (new_ptcl == NULL)
    {
        return NULL;
    }
    sLBParticleStructsUsedNum++;
    
    if (D_ovl0_800D644E < sLBParticleStructsUsedNum) 
    {
        D_ovl0_800D644E = sLBParticleStructsUsedNum;
    }
    if (gtor != NULL)
    {
        new_ptcl->generator_id = gtor->generator_id;
    } 
    else new_ptcl->generator_id = ++dLBParticleCurrentGeneratorID;

    if (gtor != NULL)
    {
        new_ptcl->tfrm = gtor->tfrm;
        
        if (new_ptcl->tfrm != NULL)
        {
            new_ptcl->tfrm->users_num++;
        }
    }
    else new_ptcl->tfrm = NULL;
    
    sLBParticleStructsAllocFree = new_ptcl->next;
    
    if (this_ptcl == NULL) 
    {
        new_ptcl->next = sLBParticleStructsAllocLinks[bank_id >> 3];
        sLBParticleStructsAllocLinks[bank_id >> 3] = new_ptcl;
    } 
    else 
    {
        new_ptcl->next = this_ptcl->next;
        this_ptcl->next = new_ptcl;
    }
    new_ptcl->bank_id = bank_id;
    new_ptcl->flags = flags;
    new_ptcl->texture_id = texture_id;

	new_ptcl->pos.x = pos_x;
	new_ptcl->pos.y = pos_y;
	new_ptcl->pos.z = pos_z;

    new_ptcl->vel.x = vel_x;
    new_ptcl->vel.y = vel_y;
    new_ptcl->vel.z = vel_z;
    
    new_ptcl->mscale = mscale;
    new_ptcl->unk_ptcl_0x38 = argD;
    new_ptcl->unk_ptcl_0x3C = argE;

    new_ptcl->unk_ptcl_0x1E = arg5 + 1;
    new_ptcl->bytecode_csr = new_ptcl->unk_ptcl_0x1A = 0;
    
    new_ptcl->bytecode = bytecode;

    if (argF != FALSE) 
    { 
        new_ptcl->flags |= 0x10;
    }
    new_ptcl->is_have_bytecode = (bytecode != NULL) ? TRUE : FALSE;
    
    new_ptcl->data_id = 0;
    
    new_ptcl->primcolor.r = new_ptcl->primcolor.g = new_ptcl->primcolor.b = new_ptcl->primcolor.a = 0xFF;
    new_ptcl->envcolor.r = new_ptcl->envcolor.g = new_ptcl->envcolor.b = new_ptcl->envcolor.a = 0x00;
    
    new_ptcl->unk_ptcl_0xE = new_ptcl->unk_ptcl_0x10 = new_ptcl->unk_ptcl_0x12 = 0;
    
    new_ptcl->gtor = gtor;

	return new_ptcl;
}

// 0x800CE6B8
efParticle* lbParticleMakeDefault(efParticle *ptcl, s32 bank_id, s32 script_id)
{
	efScript *efscript;
	s32 id = bank_id & 7;

	if (id >= LBPARTICLE_BANKS_NUM_MAX)
	{
		return NULL;
	}
	if (script_id >= sLBParticleScriptBanksNum[id])
	{
		return NULL;
	}
	efscript = sLBParticleScriptBanks[id][script_id];

	return lbParticleMakeStruct
	(
		ptcl,
		bank_id,
		efscript->flags,
		efscript->texture_id,
		efscript->bytecode,
		efscript->unk_efscript_0x6,
		0.0F, 0.0F, 0.0F,
		efscript->vel.x, efscript->vel.y, efscript->vel.z,
		efscript->mscale,
		efscript->unk_efscript_0xC,
		efscript->unk_efscript_0x10,
		sLBParticleTextureBanks[id][efscript->texture_id]->flags,
		NULL
	);
}

// 0x800CE7A8
efParticle* lbParticleMakeParam
(
	s32 bank_id,
	u32 flags,
	u16 texture_id,
	u8 *bytecode,
	s32 arg4,
	f32 pos_x,
	f32 pos_y,
	f32 pos_z,
	f32 vel_x,
	f32 vel_y,
	f32 vel_z,
	f32 argB,
	f32 argC,
	f32 argD,
	u32 argE,
	efGenerator *gtor
)
{
	efParticle *ptcl = lbParticleMakeStruct
	(
		NULL,
		bank_id,
		flags,
		texture_id,
		bytecode,
		arg4,
		pos_x, pos_y, pos_z,
		vel_x, vel_y, vel_z,
		argB,
		argC,
		argD,
		argE,
		gtor
	);
	if (ptcl != NULL)
	{
		func_ovl0_800CEF4C(ptcl, 0, bank_id >> 3);
	}
	return ptcl;
}

// 0x800CE870
efParticle* func_ovl0_800CE870(s32 bank_id, s32 script_id)
{
	efParticle *ptcl = lbParticleMakeDefault(NULL, bank_id, script_id);

	if (ptcl != NULL)
	{
		func_ovl0_800CEF4C(ptcl, 0, bank_id >> 3);
	}
	return ptcl;
}

// 0x800CE8C0
efParticle* lbParticleMakePosVel(s32 bank_id, s32 script_id, f32 pos_x, f32 pos_y, f32 pos_z, f32 vel_x, f32 vel_y, f32 vel_z)
{
	efParticle *ptcl;
	efScript *efscript;
	s32 id = bank_id & 7;

	if (id >= LBPARTICLE_BANKS_NUM_MAX)
	{
		return NULL;
	}
	if (script_id >= sLBParticleScriptBanksNum[id])
	{
		return NULL;
	}
	efscript = sLBParticleScriptBanks[id][script_id];

	ptcl = lbParticleMakeStruct
	(
		NULL,
		bank_id,
		efscript->flags,
		efscript->texture_id,
		efscript->bytecode,
		efscript->unk_efscript_0x6,
		pos_x, pos_y, pos_z,
		vel_x, vel_y, vel_z,
		efscript->mscale,
		efscript->unk_efscript_0xC,
		efscript->unk_efscript_0x10,
		sLBParticleTextureBanks[id][efscript->texture_id]->flags,
		NULL
	);
	if (ptcl != NULL)
	{
		func_ovl0_800CEF4C(ptcl, 0, bank_id >> 3);
	}
	return ptcl;
}

// 0x800CE9E8
efParticle* lbParticleMakeDefaultID(s32 bank_id, s32 script_id)
{
	return lbParticleMakeDefault(NULL, bank_id, script_id);
}

// 0x800CEA14
void lbParticleParseStructBytecode(efParticle *ptcl)
{
	if (ptcl != NULL)
	{
		func_ovl0_800CEF4C(ptcl, NULL, ptcl->bank_id >> 3);
	}
}

// 0x800CEA40
void lbParticleEjectStruct(efParticle *this_ptcl)
{
	efParticle *prev_ptcl, *current_ptcl;
	efGenerator *gtor;
	s32 bank_id;

	bank_id = this_ptcl->bank_id >> 3;
	current_ptcl = sLBParticleStructsAllocLinks[bank_id];
	prev_ptcl = NULL;

	while (current_ptcl != NULL)
	{
		if (current_ptcl == this_ptcl)
		{
			if (prev_ptcl == NULL)
			{
				sLBParticleStructsAllocLinks[bank_id] = current_ptcl->next;
			}
			else prev_ptcl->next = current_ptcl->next;

			gtor = this_ptcl->gtor;

			if ((gtor != NULL) && (this_ptcl->flags & 4) && (gtor->kind == 2))
			{
				gtor->generator_vars.unk_gtor_vars.halfword--;
			}
			if (this_ptcl->tfrm != NULL)
			{
				this_ptcl->tfrm->users_num--;

				if (this_ptcl->tfrm->users_num == 0)
				{
					lbParticleEjectTransform(this_ptcl->tfrm);
				}
			}
			current_ptcl->next = sLBParticleStructsAllocFree;
			sLBParticleStructsAllocFree = current_ptcl;
			sLBParticleStructsUsedNum--;

			break;
		}
		prev_ptcl = current_ptcl;
		current_ptcl = current_ptcl->next;
	}
}

// 0x800CEB50 - unused? Eject all efParticle structs
void lbParticleEjectStructAll(void)
{
	efParticle *current_ptcl, *next_ptcl;
	s32 i;

	for (i = 0; i < ARRAY_COUNT(sLBParticleStructsAllocLinks); i++)
	{
		current_ptcl = sLBParticleStructsAllocLinks[i];

		while (current_ptcl != NULL)
		{
			next_ptcl = current_ptcl->next;

			lbParticleEjectStruct(current_ptcl);

			current_ptcl = next_ptcl;
		}
	}
}

// 0x800CEBC0
u8* lbParticleParseFloatBE(u8 *csr, f32 *f)
{
	u8 bytes[4];

	bytes[0] = *csr++;
	bytes[1] = *csr++;
	bytes[2] = *csr++;
	bytes[3] = *csr++;

	*f = *(f32*)bytes;

	return csr;
}

// 0x800CEBF8
u8* lbParticleParseShortBE(u8 *csr, u16 *s)
{
	u16 value = *csr++;

	if (value & 0x80)
	{
		value = ((value & 0x7F) << 8) + *csr++;
	}
	*s = value + 1;

	return csr;
}

// 0x800CEC34
void lbParticleRotateVel(efParticle *ptcl, f32 angle)
{
	Vec3f vel;
	f32 sin_angle;
	f32 magnitude;
	f32 pitch;
	f32 yaw;
	f32 sin_pitch;
	f32 cos_pitch;
	f32 sin_yaw;
	f32 cos_yaw;
	f32 cos_angle;
	
	vel.x = ptcl->vel.x;
	vel.y = ptcl->vel.y;
	vel.z = ptcl->vel.z;
	
	pitch = atan2f(vel.y, vel.z);
	sin_pitch = __sinf(pitch);
	cos_pitch = __cosf(pitch);
	
	yaw = atan2f(vel.x, (vel.y * sin_pitch) + (vel.z * cos_pitch));
	sin_yaw = __sinf(yaw);
	cos_yaw = __cosf(yaw);
	
	magnitude = sqrtf(SQUARE(vel.x) + SQUARE(vel.y) + SQUARE(vel.z));
	
	vel.y = mtTrigGetRandomFloat() * F_CST_DTOR32(360.0F);
	
	sin_angle = __sinf(angle) * magnitude;
	
	vel.z = sin_yaw;
	vel.x = __cosf(vel.y) * sin_angle;
	vel.y = __sinf(vel.y) * sin_angle;
	
	cos_angle = __cosf(angle) * magnitude;
	
	ptcl->vel.x = (vel.x * cos_yaw) + (cos_angle * sin_yaw);
	ptcl->vel.y = (((-vel.x * sin_pitch) * sin_yaw) + (vel.y * cos_pitch)) + ((cos_angle * sin_pitch) * cos_yaw);
	ptcl->vel.z = (((-vel.x * cos_pitch) * vel.z) - (vel.y * sin_pitch)) + ((cos_angle * cos_pitch) * cos_yaw);
}

// 0x800CEDBC
void lbParticleSetDistVel(efParticle *ptcl, DObj *dobj)
{
	f32 dx, dy, dz, dist;

	if (dobj == NULL)
	{
		return;
	}
	dx = dobj->translate.vec.f.x - ptcl->pos.x;
	dy = dobj->translate.vec.f.y - ptcl->pos.y;
	dz = dobj->translate.vec.f.z - ptcl->pos.z;

	dist = sqrtf(SQUARE(ptcl->vel.x) + SQUARE(ptcl->vel.y) + SQUARE(ptcl->vel.z));

	if ((SQUARE(dx) + SQUARE(dy) + SQUARE(dz)) != 0.0F)
	{
		dist /= sqrtf(SQUARE(dx) + SQUARE(dy) + SQUARE(dz));

		ptcl->vel.x = dx * dist;
		ptcl->vel.y = dy * dist;
		ptcl->vel.z = dz * dist;
	}
}

// 0x800CEEB8
void lbParticleAddDistVelMag(efParticle *ptcl, DObj *dobj, f32 magnitude)
{
	f32 dx, dy, dz, dist;

	if (dobj == NULL)
	{
		return;
	}
	dx = dobj->translate.vec.f.x - ptcl->pos.x;
	dy = dobj->translate.vec.f.y - ptcl->pos.y;
	dz = dobj->translate.vec.f.z - ptcl->pos.z;

	dist = SQUARE(dx) + SQUARE(dy) + SQUARE(dz);

	if (dist != 0.0F)
	{
		dist = magnitude / dist;

		ptcl->vel.x += dist * dx;
		ptcl->vel.y += dist * dy;
		ptcl->vel.z += dist * dz;
	}
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl0/halsprite/func_ovl0_800CEF4C.s")

// 0x800D0C74
void lbParticleStructProcRun(GObj *gobj)
{
	u32 flags = gobj->flags;
	s32 i;
	efParticle *prev_ptcl;
	efParticle *current_ptcl;
	efParticle *next_ptcl;

	for (i = 0; i < ARRAY_COUNT(sLBParticleStructsAllocLinks); i++, flags >>= 1)
	{
		if (flags & 0x10000)
		{
			continue;
		}
		prev_ptcl = NULL;

		current_ptcl = sLBParticleStructsAllocLinks[i];

		while (current_ptcl != NULL)
		{
			next_ptcl = func_ovl0_800CEF4C(current_ptcl, prev_ptcl, i);

			if (current_ptcl->next == next_ptcl)
			{
				prev_ptcl = current_ptcl;
				current_ptcl = next_ptcl;
			}
			else current_ptcl = next_ptcl;
		}
	}
}

#ifdef NON_MATCHING
/* 
 * NONMATCHING: xh, xl, yh, yl, pos_x, pos_y and pos_z float reg and/or order swaps
 * This is likely related to control flow, because xl and yl are supposed to go into saved regs,
 * but they are instead placed in fv0 and fv1 (f0 and f2 respectively). xh and yh are however
 * correctly placed into the registers they belong in. The empty brackets are also suspicious.
 */

// 0x800D0D34
void lbParticleDrawTextures(GObj *gobj)
{
    efParticle *ptcl;
    void *prev_image, *prev_palette;
    s32 prev_ac, prev_alpha;
    s32 tlut;
    Mtx44f look_at_f;
    Mtx44f projection_f;
    u8 ac, alpha;
    s32 bank_id;
    void **p_palette;
    f32 pos_x, pos_y, pos_z;
    f32 tx, ty, tz;
    f32 pc0_magnitude;  // var_f14?
    f32 pc1_magnitude;  // var_f16?
    f32 tm;
    Camera *cam;
    s32 s;              // sp210
    s32 t;              // sp20C
    f32 vscale0;        // sp208
    f32 vtrans0;        // sp204
    f32 vscale1;        // sp200
    f32 vtrans1;        // sp1FC
    f32 vscale2;        // sp1F8
    f32 vtrans2;        // sp1F4    
    s32 dsdx;           // sp1F0
    s32 dtdy;           // sp1EC
    s32 cms, cmt;
    s32 fmt, siz;
    s32 i;              // s2
    u32 j;              // sp1D4
    s32 width, height;
    f32 xh, yh;
    f32 xl, yl;
    void *image, *palette;
    u8 masks, maskt;
    f32 mx, my;

    cam = CameraGetStruct(gOMObjCurrentCapture);

    for (i = 0; i < cam->ommtx_len; i++)
    {
        switch (cam->ommtx[i]->kind)
        {
            case nOMTransformPerspFastF:
                syMatrixPerspFastF
                (
                    &projection_f,
                    NULL,
                    cam->projection.persp.fovy,
                    cam->projection.persp.aspect,
                    cam->projection.persp.near,
                    cam->projection.persp.far,
                    cam->projection.persp.scale
                );
                break;
                
            case nOMTransformPerspF:
                syMatrixPerspF
                (
                    &projection_f,
                    NULL,
                    cam->projection.persp.fovy,
                    cam->projection.persp.aspect,
                    cam->projection.persp.near,
                    cam->projection.persp.far,
                    cam->projection.persp.scale
                );
                break;

			case nOMTransformOrtho:
				syMatrixOrthoF
                (
                    &projection_f,
                    cam->projection.ortho.l,
                    cam->projection.ortho.r,
                    cam->projection.ortho.b,
                    cam->projection.ortho.t,
                    cam->projection.ortho.n,
                    cam->projection.ortho.f,
                    cam->projection.ortho.scale
                );
                break;
                
            case 6:
            case 7:
            case 12:
            case 13:
                syMatrixLookAtF
                (
                    &look_at_f,
                    cam->vec.eye.x,
                    cam->vec.eye.y,
                    cam->vec.eye.z,
                    cam->vec.at.x,
                    cam->vec.at.y,
                    cam->vec.at.z,
                    cam->vec.up.x,
                    cam->vec.up.y,
                    cam->vec.up.z
                );
                break;
                
            case 8:
            case 9:
            case 14:
            case 15:
                syMatrixModLookAtF
                (
                    &look_at_f,
                    cam->vec.eye.x,
                    cam->vec.eye.y,
                    cam->vec.eye.z,
                    cam->vec.at.x,
                    cam->vec.at.y,
                    cam->vec.at.z,
                    cam->vec.up.x,
                    0.0F,
                    1.0F,
                    0.0F
                );
                break;
                
            case 10:
            case 11:
            case 16:
            case 17:
                syMatrixModLookAtF
                (
                    &look_at_f,
                    cam->vec.eye.x,
                    cam->vec.eye.y,
                    cam->vec.eye.z,
                    cam->vec.at.x,
                    cam->vec.at.y,
                    cam->vec.at.z,
                    cam->vec.up.x,
                    0.0F,
                    0.0F,
                    1.0F
                );
                break;
                
            default:
                syMatrixPerspFastF
                (
                    &projection_f,
                    NULL,
                    cam->projection.persp.fovy,
                    cam->projection.persp.aspect,
                    cam->projection.persp.near,
                    cam->projection.persp.far,
                    cam->projection.persp.scale
                );
                syMatrixLookAtF
                (
                    &look_at_f,
                    cam->vec.eye.x,
                    cam->vec.eye.y,
                    cam->vec.eye.z,
                    cam->vec.at.x,
                    cam->vec.at.y,
                    cam->vec.at.z,
                    cam->vec.up.x,
                    cam->vec.up.y,
                    cam->vec.up.z
                );
                break;
        }
    }
    if (cam->ommtx_len != 0)
    {
        guMtxCatF(look_at_f, projection_f, projection_f);
        
        vscale0 = cam->viewport.vp.vscale[0];
        vscale1 = -cam->viewport.vp.vscale[1];
        vscale2 = cam->viewport.vp.vscale[2];
        
        vtrans0 = cam->viewport.vp.vtrans[0];
        vtrans1 = cam->viewport.vp.vtrans[1];
        vtrans2 = cam->viewport.vp.vtrans[2];
    }
    else
    {
        vscale0 = cam->viewport.vp.vscale[0];
        vscale1 = -cam->viewport.vp.vscale[1];
        vscale2 = cam->viewport.vp.vscale[2];
        
        vtrans0 = cam->viewport.vp.vtrans[0];
        vtrans1 = cam->viewport.vp.vtrans[1];
        vtrans2 = cam->viewport.vp.vtrans[2];
        
        guMtxIdentF(projection_f);

        projection_f[0][0] = 1.0F / vscale0;
        projection_f[1][1] = 1.0F / vscale1;
        projection_f[2][2] = -1.0F / vscale2;

        projection_f[3][0] = -vtrans0 / vscale0;
        projection_f[3][1] = -vtrans1 / vscale1;
        projection_f[3][2] = vtrans2 / vscale2;
    }
    pc0_magnitude = sqrtf(SQUARE(projection_f[0][0]) + SQUARE(projection_f[1][0]) + SQUARE(projection_f[2][0]));
    pc1_magnitude = sqrtf(SQUARE(projection_f[0][1]) + SQUARE(projection_f[1][1]) + SQUARE(projection_f[2][1]));
    
    gDPPipeSync(gDisplayListHead[0]++);
    gDPSetTexturePersp(gDisplayListHead[0]++, G_TP_NONE);
    gDPSetDepthSource(gDisplayListHead[0]++, G_ZS_PRIM);
    gDPSetColorDither(gDisplayListHead[0]++, G_CD_MAGICSQ | dLBParticleColorDitherMode);
    gDPSetAlphaDither(gDisplayListHead[0]++, G_AD_PATTERN | dLBParticleAlphaDitherMode);

    prev_image = NULL;
    prev_palette = NULL;

    prev_ac = -1;
    prev_alpha = -1;
    tlut = -1;
    
    dLBParticleCurrentTransformID++;
    
    for (j = 0; j < ARRAY_COUNT(sLBParticleStructsAllocLinks); j++)
    {
        if (gobj->cam_mask & (1 << j))
        {
            for (ptcl = sLBParticleStructsAllocLinks[j]; ptcl != NULL; ptcl = ptcl->next)
            {
                if (ptcl->mscale != 0.0F)
                {
                    pos_x = ptcl->pos.x;
                    pos_y = ptcl->pos.y;
                    pos_z = ptcl->pos.z;
                    
                    if (ptcl->tfrm != NULL)
                    {
                        if (ptcl->tfrm->transform_id != dLBParticleCurrentTransformID)
                        {
							if (ptcl->tfrm->transform_status != nLBTransformStatusFinished)
							{
                                syMatrixTraRotRpyRScaF
                                (
                                    &ptcl->tfrm->affine,
                                    ptcl->tfrm->translate.x,
                                    ptcl->tfrm->translate.y,
                                    ptcl->tfrm->translate.z,
                                    ptcl->tfrm->rotate.x,
                                    ptcl->tfrm->rotate.y,
                                    ptcl->tfrm->rotate.z,
                                    ptcl->tfrm->scale.x,
                                    ptcl->tfrm->scale.y,
                                    ptcl->tfrm->scale.z
                                );
                            }
							if (ptcl->tfrm->transform_status == nLBTransformStatusReady)
							{
								ptcl->tfrm->transform_status = nLBTransformStatusFinished;
							}
                            guMtxCatF(ptcl->tfrm->affine, projection_f, ptcl->tfrm->projection);
                            
                            ptcl->tfrm->pc0_magnitude = sqrtf
                            (
                                SQUARE(ptcl->tfrm->projection[0][0]) +
                                SQUARE(ptcl->tfrm->projection[1][0]) +
                                SQUARE(ptcl->tfrm->projection[2][0])
                            );
                            ptcl->tfrm->pc1_magnitude = sqrtf
                            (
                                SQUARE(ptcl->tfrm->projection[0][1]) +
                                SQUARE(ptcl->tfrm->projection[1][1]) +
                                SQUARE(ptcl->tfrm->projection[2][1])
                            );
                            ptcl->tfrm->transform_id = dLBParticleCurrentTransformID;
                        }
                        s = (ptcl->tfrm->affine[0][0] >= 0.0F) ? 0 : -1;
                        t = (ptcl->tfrm->affine[1][1] >= 0.0F) ? 0 : -1;
                        
                        mx = ptcl->tfrm->pc0_magnitude;
                        my = ptcl->tfrm->pc1_magnitude;
                        
                        tx = ((ptcl->tfrm->projection[0][0] * pos_x) + (ptcl->tfrm->projection[1][0] * pos_y) + (ptcl->tfrm->projection[2][0] * pos_z)) + ptcl->tfrm->projection[3][0];
                        ty = ((ptcl->tfrm->projection[0][1] * pos_x) + (ptcl->tfrm->projection[1][1] * pos_y) + (ptcl->tfrm->projection[2][1] * pos_z)) + ptcl->tfrm->projection[3][1];
                        tz = ((ptcl->tfrm->projection[0][2] * pos_x) + (ptcl->tfrm->projection[1][2] * pos_y) + (ptcl->tfrm->projection[2][2] * pos_z)) + ptcl->tfrm->projection[3][2];
                        tm = ((ptcl->tfrm->projection[0][3] * pos_x) + (ptcl->tfrm->projection[1][3] * pos_y) + (ptcl->tfrm->projection[2][3] * pos_z)) + ptcl->tfrm->projection[3][3];
                    }
                    else
                    {
                        s = t = 0;
                        
                        mx = pc0_magnitude;
                        my = pc1_magnitude;
                        
                        tx = ((projection_f[0][0] * pos_x) + (projection_f[1][0] * pos_y) + (projection_f[2][0] * pos_z)) + projection_f[3][0];
                        ty = ((projection_f[0][1] * pos_x) + (projection_f[1][1] * pos_y) + (projection_f[2][1] * pos_z)) + projection_f[3][1];
                        tz = ((projection_f[0][2] * pos_x) + (projection_f[1][2] * pos_y) + (projection_f[2][2] * pos_z)) + projection_f[3][2];
                        tm = ((projection_f[0][3] * pos_x) + (projection_f[1][3] * pos_y) + (projection_f[2][3] * pos_z)) + projection_f[3][3];
                    }
                    if (tm == 0.0F)
                    {
                        // uh huh
                    }
                    else
                    {
                        tm = 1.0F / tm;
                
                        tx *= tm;
                        ty *= tm;
                        tz *= tm;
                        
                        if
                        (
                            (tx < -1.0F) || (tx > 1.0F) ||
                            (ty < -1.0F) || (ty > 1.0F) ||
                            (tz < +0.0F) || (tz > 1.0F)
                        )
                        {
                            // uh huh
                        }
                        else
                        {
                            tm *= ptcl->mscale;

                            mx = tm * mx;
                            xh = mx + tx;
                            
                            my = tm * my;
                            yh = my + ty;

                            tx = tx * vscale0 + vtrans0;
                            xh = xh * vscale0 + vtrans0;
                            
                            if (tx < xh)
                            {
                                xh = xh;
                                xl = tx - (xh - tx);
                            }
                            else
                            {
                                xl = xh;
                                xh = tx - (xh - tx);
                            }
                            ty = ty * vscale1 + vtrans1;
                            yh = yh * vscale1 + vtrans1;
                            
                            if (ty < yh)
                            {
                                yh = yh;
                                yl = ty - (yh - ty);
                            }
                            else
                            {
                                yl = yh;
                                yh = ty - (yh - ty);
                            }
                            tz = tz * vscale2 + vtrans2;
                            
                            bank_id = ptcl->bank_id & 7;

                            fmt = sLBParticleTextureBanks[bank_id][ptcl->texture_id]->fmt;
                            siz = sLBParticleTextureBanks[bank_id][ptcl->texture_id]->siz;
                            
                            width = sLBParticleTextureBanks[bank_id][ptcl->texture_id]->width;
                            height = sLBParticleTextureBanks[bank_id][ptcl->texture_id]->height;
                            
                            image = sLBParticleTextureBanks[bank_id][ptcl->texture_id]->data[ptcl->data_id];
                            
                            if (fmt == G_IM_FMT_CI)
                            {
                                p_palette = &sLBParticleTextureBanks[bank_id][ptcl->texture_id]->data[sLBParticleTextureBanks[bank_id][ptcl->texture_id]->count];
                                
                                palette = (!(ptcl->flags & 0x10)) ? p_palette[ptcl->data_id] : p_palette[0];
                            }
                            dsdx = (width * 4096.0F) / (xh - xl);
                            dtdy = (height * 4096.0F) / (yh - yl);
                
                            if (s < 0)
                            {
                                s = width * 32;
                                dsdx = -dsdx;
                            }
                            if (t < 0)
                            {
                                t = height * 32;
                                dtdy = -dtdy;
                            }
							if (ptcl->flags & LBPARTICLE_FLAG_MASKS)
							{
                                dsdx *= 2;
                                cms = 1;
                                
                                switch (width)
                                {
                                case 2:
                                    masks = 1;
                                    break;
                                    
                                case 4:
                                    masks = 2;
                                    break;
                                    
                                case 8:
                                    masks = 3;
                                    break;
                                    
                                case 16:
                                    masks = 4;
                                    break;
                                    
                                case 32:
                                    masks = 5;
                                    break;
                                    
                                case 64:
                                    masks = 6;
                                    break;
                                    
                                case 128:
                                    masks = 7;
                                    break;
                                    
                                case 256:
                                    masks = 8;
                                    break;

                                default:
                                    masks = 0;
                                    break;
                                }
                            }
                            else
                            {
                                cms = 2;
                                masks = 0;
                            }
                            if (ptcl->flags & LBPARTICLE_FLAG_MASKT)
                            {
                                dtdy *= 2;
                                cmt = 1;
                                
                                switch (height)
                                {
                                case 2:
                                    maskt = 1;
                                    break;
                                    
                                case 4:
                                    maskt = 2;
                                    break;
                                    
                                case 8:
                                    maskt = 3;
                                    break;
                                    
                                case 16:
                                    maskt = 4;
                                    break;
                                    
                                case 32:
                                    maskt = 5;
                                    break;
                                    
                                case 64:
                                    maskt = 6;
                                    break;
                                    
                                case 128:
                                    maskt = 7;
                                    break;
                                    
                                case 256:
                                    maskt = 8;
                                    break;
                                    
                                default: 
                                    maskt = 0;
                                    break;
                                }
                            }
                            else
                            {
                                cmt = 2;
                                maskt = 0;
                            }
                            if (fmt == G_IM_FMT_CI)
                            {
                                if (palette != prev_palette)
                                {
                                    gDPLoadTLUT_pal256(gDisplayListHead[0]++, palette);
                                    
                                    prev_palette = palette;
                                }
                                if (tlut != 1)
                                {
                                    gDPSetTextureLUT(gDisplayListHead[0]++, G_TT_RGBA16);
                                    
                                    tlut = 1;
                                }
                            }
                            else if (tlut != 0)
                            {
                                gDPSetTextureLUT(gDisplayListHead[0]++, G_TT_NONE);
                                
                                tlut = 0;
                            }
                            if (image != prev_image)
                            {
                                switch (siz)
                                {
                                case G_IM_SIZ_4b:
                                    gDPLoadTextureBlock_4b
                                    (
                                        gDisplayListHead[0]++,
                                        image,
                                        fmt,
                                        width,
                                        height,
                                        0,
                                        cms,
                                        cmt,
                                        masks,
                                        maskt,
                                        G_TX_NOLOD,
                                        G_TX_NOLOD
                                    );
                                    if ((width * height) >= 4096)
                                    {
                                        prev_palette = NULL;
                                    }
                                    break;
                                    
                                case G_IM_SIZ_8b:
                                    gDPLoadTextureBlock
                                    (
                                        gDisplayListHead[0]++,
                                        image,
                                        fmt,
                                        G_IM_SIZ_8b,
                                        width,
                                        height,
                                        0,
                                        cms,
                                        cmt,
                                        masks,
                                        maskt,
                                        G_TX_NOLOD,
                                        G_TX_NOLOD
                                    );
                                    if ((width * height) >= 2048)
                                    {
                                        prev_palette = NULL;
                                    }
                                    break;
                                    
                                case G_IM_SIZ_16b:
                                    gDPLoadTextureBlock
                                    (
                                        gDisplayListHead[0]++,
                                        image,
                                        fmt,
                                        G_IM_SIZ_16b,
                                        width,
                                        height,
                                        0,
                                        cms,
                                        cmt,
                                        masks,
                                        maskt,
                                        G_TX_NOLOD,
                                        G_TX_NOLOD
                                    );
                                    if ((width * height) >= 1024)
                                    {
                                        prev_palette = NULL;
                                    }
                                    break;
                                    
                                case G_IM_SIZ_32b:
                                    gDPLoadTextureBlock
                                    (
                                        gDisplayListHead[0]++,
                                        image,
                                        fmt,
                                        G_IM_SIZ_32b,
                                        width,
                                        height,
                                        0,
                                        cms,
                                        cmt,
                                        masks,
                                        maskt,
                                        G_TX_NOLOD,
                                        G_TX_NOLOD
                                    );
                                    if ((width * height) >= 512)
                                    {
                                        prev_palette = NULL;
                                    }
                                    break;
                                    
                                default:
                                    break;
                                }
                                prev_image = image;
                            }
                            gDPSetPrimColor(gDisplayListHead[0]++, 0, 0, ptcl->primcolor.r, ptcl->primcolor.g, ptcl->primcolor.b, ptcl->primcolor.a);
                
                            if (ptcl->flags & LBPARTICLE_FLAG_ENVCOLOR)
                            {
                                gDPSetEnvColor(gDisplayListHead[0]++, ptcl->envcolor.r, ptcl->envcolor.g, ptcl->envcolor.b, ptcl->envcolor.a);
                                
                                gDPSetCombineLERP
                                (
                                    gDisplayListHead[0]++,
                                    PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT,
                                    PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT
                                );
                            }
                            else if (ptcl->flags & 0x100)
                            {
                                gDPSetCombineLERP
                                (
                                    gDisplayListHead[0]++,
                                    NOISE, 0, TEXEL0, 0, TEXEL0, 0, PRIMITIVE, 0,
                                    NOISE, 0, TEXEL0, 0, TEXEL0, 0, PRIMITIVE, 0
                                );
                            }
                            else gDPSetCombineMode(gDisplayListHead[0]++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                            
                            if (ptcl->flags & LBPARTICLE_FLAG_DITHER)
                            {
                                ac = G_AC_DITHER;
                            }
                            else
                            {
                                ac = G_AC_THRESHOLD;

								if (ptcl->flags & LBPARTICLE_FLAG_ALPHABLEND)
								{
                                    alpha = ptcl->envcolor.a;
                                }
                                else alpha = 0x08;
                                
                                if (prev_alpha != alpha)
                                {
                                    gDPSetBlendColor(gDisplayListHead[0]++, 0x00, 0x00, 0x00, alpha);
                
                                    prev_alpha = alpha;
                                }
                            }
                            if (prev_ac != ac)
                            {
                                gDPSetAlphaCompare(gDisplayListHead[0]++, ac);
                                
                                prev_ac = ac;
                            }
                            gDPSetPrimDepth(gDisplayListHead[0]++, (s32) (tz * 32.0F), 0);
                
                            gSPScisTextureRectangle(gDisplayListHead[0]++, xl, yl, xh, yh, G_TX_RENDERTILE, s, t, dsdx, dtdy);
                        }
                    }
                }
            }
        }
    }
    if (tlut != 0)
    {
        gDPSetTextureLUT(gDisplayListHead[0]++, G_TT_NONE);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/ovl0/halsprite/lbParticleDrawTextures.s")
#endif

// 0x800D2720
void lbParticleAddGeneratorToBuf(s32 gtor_id, efGenerator *gtor)
{
	if ((gtor_id > 0) && (gtor_id < ARRAY_COUNT(sLBParticleGeneratorsAllocLinks)))
	{
		sLBParticleGeneratorsAllocLinks[gtor_id] = gtor;
	}
}

// 0x800D2744
void lbParticleSetDitherModes(s32 colordither_mode, s32 alphadither_mode)
{
	dLBParticleColorDitherMode = colordither_mode;
	dLBParticleAlphaDitherMode = alphadither_mode;
}

extern void lbParticleGeneratorProcRun(GObj*);

// 0x800D2758
GObj* lbParticleAllocGenerators(s32 num)
{
	s32 i;

	sLBParticleGeneratorsAllocFree = sLBParticleGeneratorsAllocLinks[0] = NULL;

	for (i = num - 1; i >= 0; i--)
	{
		efGenerator *gtor = gsMemoryAlloc(sizeof(*gtor), 0x4);

		if (gtor == NULL)
		{
			return NULL;
		}
		gtor->next = sLBParticleGeneratorsAllocFree;

		sLBParticleGeneratorsAllocFree = gtor;
	}
	sLBParticleGeneratorsUsedNum = 0;
	D_ovl0_800D6450 = 0;

	return gcMakeGObjSPAfter(-7, lbParticleGeneratorProcRun, 0, GOBJ_LINKORDER_DEFAULT);
}

// 0x800D27F8
void lbParticleGetPosVel(Vec3f *pos, Vec3f *vel, DObj *dobj)
{
	Mtx44f dst;
	Mtx44f tmp;
	f32 x, y, z;

	guMtxIdentF(dst);

	do
	{
		if ((dobj->scale.vec.f.x != 1.0F) || (dobj->scale.vec.f.y != 1.0F) || (dobj->scale.vec.f.z != 1.0F))
		{
			syMatrixScaF(&tmp, dobj->scale.vec.f.x, dobj->scale.vec.f.y, dobj->scale.vec.f.z);
			guMtxCatF(dst, tmp, dst);
		}
		if ((dobj->rotate.vec.f.x != 0.0F) || (dobj->rotate.vec.f.y != 0.0F) || (dobj->rotate.vec.f.z != 0.0F))
		{
			syMatrixRotRpyRF(&tmp, dobj->rotate.vec.f.x, dobj->rotate.vec.f.y, dobj->rotate.vec.f.z);
			guMtxCatF(dst, tmp, dst);
		}
		if ((dobj->translate.vec.f.x != 0.0F) || (dobj->translate.vec.f.y != 0.0F) || (dobj->translate.vec.f.z != 0.0F))
		{
			syMatrixTraF(&tmp, dobj->translate.vec.f.x, dobj->translate.vec.f.y, dobj->translate.vec.f.z);
			guMtxCatF(dst, tmp, dst);
		}
		if (dobj->dynstore != NULL)
		{
			OMTranslate *translate = NULL;
			OMRotate *rotate = NULL;
			OMScale *scale = NULL;
			uintptr_t csr = (uintptr_t)dobj->dynstore->data;
			s32 i;

			for (i = 0; i < ARRAY_COUNT(dobj->dynstore->kinds); i++)
			{
				switch (dobj->dynstore->kinds[i])
				{
				case nOMObjDrawVecKindNone:
                    break;

				case nOMObjDrawVecKindTranslate:
					translate = (OMTranslate*)csr;
					csr += sizeof(*translate);
					break;

				case nOMObjDrawVecKindRotate:
					rotate = (OMRotate*)csr;
					csr += sizeof(*rotate);
					break;

				case nOMObjDrawVecKindScale:
					scale = (OMScale*)csr;
					csr += sizeof(*scale);
					break;
				}
			}
			if (scale != NULL)
			{
				if ((scale->vec.f.x != 1.0F) || (scale->vec.f.y != 1.0F) || (scale->vec.f.z != 1.0F))
				{
					syMatrixScaF(&tmp, scale->vec.f.x, scale->vec.f.y, scale->vec.f.z);
					guMtxCatF(dst, tmp, dst);
				}
			}
			if (rotate != NULL)
			{
				if ((rotate->vec.f.x != 0.0F) || (rotate->vec.f.y != 0.0F) || (rotate->vec.f.z != 0.0F))
				{
					syMatrixRotRpyRF(&tmp, rotate->vec.f.x, rotate->vec.f.y, rotate->vec.f.z);
					guMtxCatF(dst, tmp, dst);
				}
			}
			if (translate != NULL)
			{
				if ((translate->vec.f.x != 0.0F) || (translate->vec.f.y != 0.0F) || (translate->vec.f.z != 0.0F))
				{
					syMatrixTraF(&tmp, translate->vec.f.x, translate->vec.f.y, translate->vec.f.z);
					guMtxCatF(dst, tmp, dst);
				}
			}
		}
		dobj = dobj->parent;
	}
    while (dobj != DOBJ_PARENT_NULL);

	pos->x = dst[3][0];
	pos->y = dst[3][1];
	pos->z = dst[3][2];

	x = vel->x, y = vel->y, z = vel->z;

	guNormalize(&dst[0][0], &dst[1][0], &dst[2][0]);
	guNormalize(&dst[0][1], &dst[1][1], &dst[2][1]);
	guNormalize(&dst[0][2], &dst[1][2], &dst[2][2]);

	vel->x = (dst[0][0] * x) + (dst[1][0] * y) + (dst[2][0] * z);
	vel->y = (dst[0][1] * x) + (dst[1][1] * y) + (dst[2][1] * z);
	vel->z = (dst[0][2] * x) + (dst[1][2] * y) + (dst[2][2] * z);
}

#ifdef NON_MATCHING
/* 
 * NONMATCHING: move $a0, $s0 and move $a1, $s1 order swap around sLBParticleGeneratorProcDefault
 */

// 0x800D2C4C
void lbParticleGeneratorProcRun(GObj *gobj)
{
    efGenerator *gtor, *next_gtor;
    f32 pos_random;
    Vec3f pos;
    Vec3f vel;
    f32 zero;
    f32 temp_vel_x;
    f32 temp_vel_y;
    f32 temp_vel_z;
    f32 magnitude;
    f32 angle1;
    f32 angle2;
    f32 sin_angle1;
    f32 cos_angle1;
    f32 sin_angle2;
    f32 cos_angle2;
    f32 spEC;
    f32 vel_x;
    f32 vel_y;
    f32 vel_z;
    f32 pv0;
    s32 unused;
    f32 temp_f26;
    f32 pos_x;
    f32 pos_y;
    f32 pos_z;
    f32 pm1;
    f32 var_f20;
    f32 pv1;
    f32 spB8;
    f32 vmag;
    
    gtor = sLBParticleGeneratorsAllocLinks[0];
    sLBParticleGeneratorsCurrent = NULL;
    
    while (gtor != NULL)
    {
            if (gobj->flags & (1 << ((gtor->bank_id >> 3) + 0x10)))
            {
                sLBParticleGeneratorsCurrent = gtor;

                gtor = gtor->next;

                continue;
            }
            if (gtor->flags & 0x800)
            {
                sLBParticleGeneratorsCurrent = gtor;

                gtor = gtor->next;

                continue;
            }
            if (gtor->unk_gtor_0x40 < 0.0F)
            {
                gtor->unk_gtor_0x44 -= gtor->unk_gtor_0x40;
            }
            else gtor->unk_gtor_0x44 += (mtTrigGetRandomFloat() * gtor->unk_gtor_0x40);

            if (gtor->unk_gtor_0x44 >= 1.0F)
            {
                vel.x = gtor->vel.x;
                vel.y = gtor->vel.y;
                vel.z = gtor->vel.z;

                if (gtor->dobj != NULL)
                {
                    lbParticleGetPosVel(&pos, &vel, gtor->dobj);
                    
                    gtor->pos.x = pos.x;
                    gtor->pos.y = pos.y;
                    gtor->pos.z = pos.z;
                }
                switch (gtor->kind)
                {
                case 0:
                case 3:
                case 4:
                    pv0 = gtor->generator_vars.rotate.base + (mtTrigGetRandomFloat() * (gtor->generator_vars.rotate.target - gtor->generator_vars.rotate.base));
                    spB8 = (gtor->generator_vars.rotate.target - gtor->generator_vars.rotate.base) / (s32) gtor->unk_gtor_0x44;
                    break;

                default:
                    pv0 = F_CST_DTOR32(360.0F) * mtTrigGetRandomFloat();
                    spB8 = F_CST_DTOR32(360.0F) / (s32) gtor->unk_gtor_0x44;
                    break;
                }
            }
            while (gtor->unk_gtor_0x44 >= 1.0F)
            {
                    switch (gtor->kind)
                    {
                    case 0:
                    case 3:
                    case 4:
                        vel_x = vel.x;
                        vel_y = vel.y;
                        vel_z = vel.z;
                        
                        angle1 = atan2f(vel_y, vel_z);
                        
                        sin_angle1 = __sinf(angle1); // spFC
                        cos_angle1 = __cosf(angle1); // spF8

                        angle2 = atan2f(vel_x, (vel_y * sin_angle1) + (vel_z * cos_angle1));
                        
                        sin_angle2 = __sinf(angle2); // spF4
                        cos_angle2 = __cosf(angle2); // spF0
                        // spFC = sin_angle1;
                        magnitude = sqrtf(SQUARE(vel_x) + SQUARE(vel_y) + SQUARE(vel_z)); // sp108
                        
                        if (gtor->unk_gtor_0x38 < 0.0F)
                        {
                            vmag = pv1 = 1.0F;
                            var_f20 = -gtor->unk_gtor_0x38;
                        }
                        else
                        {
                            pv1 = vmag = mtTrigGetRandomFloat();

                            if (gtor->kind != 0)
                            {
                                vmag = pv1 = sqrtf(pv1);
                            }
                            var_f20 = gtor->unk_gtor_0x38 * pv1;
                        }
                        if (gtor->unk_gtor_0x3C < 0.0F)
                        {
                            pv0 += spB8;
                            pv1 = -gtor->unk_gtor_0x3C;
                        }
                        else
                        {
                            pv0 = gtor->generator_vars.rotate.base + (mtTrigGetRandomFloat() * (gtor->generator_vars.rotate.target - gtor->generator_vars.rotate.base));
                            pv1 *= gtor->unk_gtor_0x3C;
                        }
                        zero = 0.0F;
                        
                        spEC = __cosf(pv0) * var_f20;
                        temp_f26 = __sinf(pv0) * var_f20;
                        pm1 = __sinf(pv1) * magnitude;

                        vel_x = __cosf(pv0) * pm1;
                        vel_y = __sinf(pv0) * pm1;
                        vel_z = __cosf(pv1) * magnitude;

                        pos_x = (spEC * cos_angle2) + zero + gtor->pos.x;
                        pos_y = (-spEC * sin_angle1 * sin_angle2) + (temp_f26 * cos_angle1) + zero + gtor->pos.y;
                        pos_z = (-spEC * cos_angle1 * sin_angle2) - (temp_f26 * sin_angle1) + zero + gtor->pos.z;

                        temp_vel_x = (vel_x * cos_angle2) + (vel_z * sin_angle2);
                        temp_vel_y = (-vel_x * sin_angle1 * sin_angle2) + (vel_y * cos_angle1) + (vel_z * sin_angle1 * cos_angle2);
                        temp_vel_z = (-vel_x * cos_angle1 * sin_angle2) - (vel_y * sin_angle1) + (vel_z * cos_angle1 * cos_angle2);

                        if (gtor->kind == 3)
                        {
                            temp_vel_x *= vmag;
                            temp_vel_y *= vmag;
                            temp_vel_z *= vmag;
                        }
                        lbParticleMakeParam
                        (
                            gtor->bank_id,
                            gtor->flags,
                            gtor->texture_id,
                            gtor->bytecode,
                            gtor->unk_gtor_0xC,
                            pos_x,
                            pos_y,
                            pos_z,
                            temp_vel_x,
                            temp_vel_y,
                            temp_vel_z,
                            gtor->mscale,
                            gtor->unk_gtor_0x2C,
                            gtor->unk_gtor_0x30,
                            0,
                            gtor
                        );
                        break;
                        
                    case 1:
                        vel_x = vel.x;
                        vel_y = vel.y;
                        vel_z = vel.z;
                        
                        pos_random = mtTrigGetRandomFloat();

                        pos_x = gtor->pos.x + (pos_random * (gtor->generator_vars.move.x - gtor->pos.x));
                        pos_y = gtor->pos.y + (pos_random * (gtor->generator_vars.move.y - gtor->pos.y));
                        pos_z = gtor->pos.z + (pos_random * (gtor->generator_vars.move.z - gtor->pos.z));
                        
                        lbParticleMakeParam
                        (
                            gtor->bank_id,
                            gtor->flags,
                            gtor->texture_id,
                            gtor->bytecode,
                            gtor->unk_gtor_0xC,
                            pos_x,
                            pos_y,
                            pos_z,
                            vel.x,
                            vel.y,
                            vel.z,
                            gtor->mscale,
                            gtor->unk_gtor_0x2C,
                            gtor->unk_gtor_0x30,
                            0,
                            gtor
                        );
                        break;
                        
                    case 2:
                        vel_x = vel.x;
                        vel_y = vel.y;
                        vel_z = vel.z;
                        
                        angle1 = atan2f(vel_y, vel_z);
                        sin_angle1 = __sinf(angle1);
                        cos_angle1 = __cosf(angle1);
                        // spF8 = cos_angle1;
                        angle2 = atan2f(vel_x, (vel_y * sin_angle1) + (vel_z * cos_angle1));
                        
                        magnitude = sqrtf(SQUARE(vel_x) + SQUARE(vel_y) + SQUARE(vel_z));
                        
                        pv1 = (gtor->unk_gtor_0x38 < 0.0F) ? 1.0F : mtTrigGetRandomFloat();

                        pv0 = (gtor->unk_gtor_0x3C < 0.0F) ? pv0 + spB8 : mtTrigGetRandomFloat() * F_CST_DTOR32(360.0F);

                        gtor->generator_vars.unk_gtor_vars.f = magnitude;

                        if
                        (
                            lbParticleMakeParam
                            (
                                gtor->bank_id,
                                gtor->flags | 0x4,
                                gtor->texture_id,
                                gtor->bytecode,
                                gtor->unk_gtor_0xC,
                                0,
                                0,
                                0,
                                pv0,
                                pv1,
                                0,
                                gtor->mscale,
                                angle1,
                                angle2,
                                0,
                                gtor
                            ) != NULL
                        )
                        {
                            gtor->generator_vars.unk_gtor_vars.halfword++;
                        }
                        break;
                        
                    default:
                        // OK seriously this order swap is ridiculous
                        if (sLBParticleGeneratorProcDefault != NULL)
                        {
                            sLBParticleGeneratorProcDefault(gtor, &vel);
                        }
                        break;
                    }
                    gtor->unk_gtor_0x44 -= 1.0F;
            }
            if (gtor->lifetime != 0)
            {
                gtor->lifetime--;

                if (gtor->generator_vars.rotate.target); // bruh
    
                if (gtor->lifetime == 0)
                {
                    if ((gtor->kind == 2) && (gtor->generator_vars.unk_gtor_vars.halfword != 0))
                    {
                        gtor->unk_gtor_0x40 = 0.0F;
                        gtor->lifetime = 1;
                    }
                    else
                    {
                        if (sLBParticleGeneratorsCurrent == NULL)
                        {
                            sLBParticleGeneratorsAllocLinks[0] = gtor->next;
                        }
                        else sLBParticleGeneratorsCurrent->next = gtor->next;
                
                        next_gtor = gtor->next;
                
                        if (gtor->tfrm != NULL)
                        {
                            gtor->tfrm->users_num--;
                    
                            if (gtor->tfrm->users_num == 0)
                            {
                                lbParticleEjectTransform(gtor->tfrm);
                            }
                        }
                        gtor->next = sLBParticleGeneratorsAllocFree;
                        sLBParticleGeneratorsAllocFree = gtor;
                
                        gtor = next_gtor;
                
                        sLBParticleGeneratorsUsedNum--;

                        continue;
                    }
                }
            }
            sLBParticleGeneratorsCurrent = gtor;

            gtor = gtor->next;
        }
    
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/ovl0/halsprite/lbParticleGeneratorProcRun.s")
#endif

// 0x800D353C
efGenerator* lbParticleGetGenerator(void)
{
    efGenerator *gtor = sLBParticleGeneratorsAllocFree;
    
    if (sLBParticleGeneratorsAllocFree == NULL)
    {
        return NULL;
    }
    sLBParticleGeneratorsUsedNum++;
    
    if (D_ovl0_800D6450 < sLBParticleGeneratorsUsedNum)
    {
        D_ovl0_800D6450 = sLBParticleGeneratorsUsedNum;
    }
    sLBParticleGeneratorsAllocFree = gtor->next;
    gtor->next = sLBParticleGeneratorsAllocLinks[0];
    sLBParticleGeneratorsAllocLinks[0] = gtor;
    
    if (sLBParticleGeneratorsCurrent == NULL)
    {
        sLBParticleGeneratorsCurrent = gtor;
    }
    gtor->generator_id = ++dLBParticleCurrentGeneratorID;
    gtor->tfrm = NULL;
    
    return gtor;
}

// 0x800D35DC
efGenerator* lbParticleMakeGenerator(s32 bank_id, s32 script_id)
{
    efGenerator *gtor;
    s32 id = bank_id & 7;  
    s32 unused;
    
    if (id >= LBPARTICLE_BANKS_NUM_MAX)
    {
        return NULL;
    }
    if (script_id >= sLBParticleScriptBanksNum[id])
    {
        return NULL;
    }
    gtor = lbParticleGetGenerator();

    if (gtor != NULL)
    {   
        gtor->kind = sLBParticleScriptBanks[id][script_id]->kind;
        gtor->bank_id = bank_id;
        gtor->flags = sLBParticleScriptBanks[id][script_id]->flags;
        gtor->texture_id = sLBParticleScriptBanks[id][script_id]->texture_id;
        gtor->unk_gtor_0xC = sLBParticleScriptBanks[id][script_id]->unk_efscript_0x6;
        gtor->lifetime = sLBParticleScriptBanks[id][script_id]->lifetime;
        
        gtor->pos.x = 0.0F;
        gtor->pos.y = 0.0F;
        gtor->pos.z = 0.0F;
        
        gtor->vel.x = sLBParticleScriptBanks[id][script_id]->vel.x;
        gtor->vel.y = sLBParticleScriptBanks[id][script_id]->vel.y;
        gtor->vel.z = sLBParticleScriptBanks[id][script_id]->vel.z;
        
        gtor->unk_gtor_0x2C = sLBParticleScriptBanks[id][script_id]->unk_efscript_0xC;
        gtor->unk_gtor_0x30 = sLBParticleScriptBanks[id][script_id]->unk_efscript_0x10;
        gtor->mscale = sLBParticleScriptBanks[id][script_id]->mscale;
        
        gtor->bytecode = sLBParticleScriptBanks[id][script_id]->bytecode;
        
        gtor->unk_gtor_0x38 = sLBParticleScriptBanks[id][script_id]->unk_efscript_0x20;
        gtor->unk_gtor_0x3C = sLBParticleScriptBanks[id][script_id]->unk_efscript_0x24;
        gtor->unk_gtor_0x40 = sLBParticleScriptBanks[id][script_id]->unk_efscript_0x28;
        
        gtor->unk_gtor_0x44 = 0.0F;
        
        if (sLBParticleTextureBanks[id][sLBParticleScriptBanks[id][script_id]->texture_id]->flags != 0)
        {
            gtor->flags |= 0x10;
        }
        gtor->dobj = NULL;
        
        switch (gtor->kind)
        {
        case 0:
        case 3:
        case 4:
            gtor->generator_vars.rotate.base = 0;
            gtor->generator_vars.rotate.target = F_CST_DTOR32(360.0F);
            break;
            
        case 1:
            gtor->generator_vars.move.x = gtor->pos.x + gtor->vel.x;
            gtor->generator_vars.move.y = gtor->pos.y + gtor->vel.y;
            gtor->generator_vars.move.z = gtor->pos.z + gtor->vel.z;
            break;
            
        case 2:
            gtor->generator_vars.unk_gtor_vars.halfword = 0;
            break;
            
        default:
            if (sLBParticleGeneratorProcSetup != NULL)
            {
                sLBParticleGeneratorProcSetup(gtor);
            }
            break;
        }
    }
    return gtor;
}

// 0x800D3884
void lbParticleEjectGenerator(efGenerator *this_gtor)
{
    efGenerator *prev_gtor = NULL, *current_gtor = sLBParticleGeneratorsAllocLinks[0];
    
    while (current_gtor != NULL)
    {
        if (current_gtor == this_gtor)
        {
            if ((this_gtor->kind == 2) && (this_gtor->generator_vars.unk_gtor_vars.halfword != 0))
            {
                this_gtor->unk_gtor_0x40 = 0.0F;
                this_gtor->lifetime = 1;
                
                break;
            }
            if (prev_gtor == NULL)
            {
                sLBParticleGeneratorsAllocLinks[0] = current_gtor->next;
            }
            else prev_gtor->next = current_gtor->next;
            
            if (this_gtor->tfrm != NULL)
            {
                this_gtor->tfrm->users_num--;
                
                if (this_gtor->tfrm->users_num == 0)
                {
                    lbParticleEjectTransform(this_gtor->tfrm);
                }
            }
            current_gtor->next = sLBParticleGeneratorsAllocFree;
            sLBParticleGeneratorsAllocFree = current_gtor;
            sLBParticleGeneratorsUsedNum--;
            
            break;
        }
        prev_gtor = current_gtor;
        current_gtor = current_gtor->next;
    }
}

// 0x800D3978
void lbParticleEjectGeneratorAll(void)
{
	efGenerator *current_gtor = sLBParticleGeneratorsAllocLinks[0];

	while (current_gtor != NULL)
	{
		efGenerator *next_gtor = current_gtor->next;

		lbParticleEjectGenerator(current_gtor);

		current_gtor = next_gtor;
	}
}

// 0x800D39C0
void lbParticleSetGeneratorProcs(void (*proc_setup)(efGenerator*), void (*proc_default)(efGenerator*, Vec3f*))
{
	sLBParticleGeneratorProcSetup = proc_setup;
	sLBParticleGeneratorProcDefault = proc_default;
}

// 0x800D39D4
void lbParticleEjectStructID(u16 generator_id, s32 link_id)
{
    efParticle *next_ptcl;
    efParticle *current_ptcl;
    efParticle *prev_ptcl;

    efGenerator *current_gtor;
    efGenerator *prev_gtor;
    efGenerator *next_gtor;

    prev_ptcl = NULL;
    current_ptcl = sLBParticleStructsAllocLinks[link_id];
    
    while (current_ptcl != NULL)
    {
        next_ptcl = current_ptcl->next;
            
        if (current_ptcl->generator_id == generator_id)
        {
            if (prev_ptcl == NULL)
            {
                sLBParticleStructsAllocLinks[link_id] = current_ptcl->next;
            }
            else prev_ptcl->next = current_ptcl->next;
                
            if ((current_ptcl->gtor != NULL) && (current_ptcl->flags & 0x4) && (current_ptcl->gtor->kind == 2))
            {
                current_ptcl->gtor->generator_vars.unk_gtor_vars.halfword--;
            }
            if (current_ptcl->tfrm != NULL)
            {
                current_ptcl->tfrm->users_num--;
                    
                if (current_ptcl->tfrm->users_num == 0)
                {
                    lbParticleEjectTransform(current_ptcl->tfrm);
                }
            }
            current_ptcl->next = sLBParticleStructsAllocFree;
            sLBParticleStructsAllocFree = current_ptcl;
            sLBParticleStructsUsedNum--;
        }
        else prev_ptcl = current_ptcl;
            
        current_ptcl = next_ptcl;
    }
    prev_gtor = NULL;
    current_gtor = sLBParticleGeneratorsAllocLinks[0];
    
    while (current_gtor != NULL)
    {
        next_gtor = current_gtor->next;
        
        if (current_gtor->generator_id == generator_id)
        {
            if ((current_gtor->kind == 2) && (current_gtor->generator_vars.unk_gtor_vars.halfword != 0))
            {
                current_gtor->unk_gtor_0x40 = 0.0F;
                current_gtor->lifetime = 1;
                
                prev_gtor = current_gtor;
            }
            else
            {
                if (prev_gtor == NULL)
                {
                    sLBParticleGeneratorsAllocLinks[0] = current_gtor->next;
                }
                else prev_gtor->next = current_gtor->next;
            
                if (current_gtor->tfrm != NULL)
                {
                    current_gtor->tfrm->users_num--;
                
                    if (current_gtor->tfrm->users_num == 0)
                    {
                        lbParticleEjectTransform(current_gtor->tfrm);
                    }
                }
                current_gtor->next = sLBParticleGeneratorsAllocFree;
                sLBParticleGeneratorsAllocFree = current_gtor;
                sLBParticleGeneratorsUsedNum--;
            }
        }
        else prev_gtor = current_gtor;
        
        current_gtor = next_gtor;
    }
}

// 0x800D3BFC
void lbParticleEjectStructBankID(efParticle *ptcl)
{
	lbParticleEjectStructID(ptcl->generator_id, ptcl->bank_id >> 3);
}

// 0x800D3C28
void lbParticleEjectStructLinkID(efParticle *ptcl)
{
	lbParticleEjectStructID(ptcl->generator_id, ptcl->link_id >> 3);
}

// 0x800D3C54
void func_ovl0_800D3C54(GObj *gobj)
{
	DObj *dobj;
	efGenerator *current_gtor, *next_gtor;

	if (gobj->obj_kind == nOMObjCommonAppendDObj)
	{
		for (dobj = DObjGetStruct(gobj); dobj != NULL; dobj = gcGetTreeDObjNext(dobj))
		{
			for (current_gtor = sLBParticleGeneratorsAllocLinks[0]; current_gtor != NULL; current_gtor = next_gtor)
			{
				next_gtor = current_gtor->next;

				if (current_gtor->dobj == dobj)
				{
					lbParticleEjectGenerator(current_gtor);
				}
			}
		}
	}
}

// 0x800D3CE0
void lbParticleSetStructPosAll(f32 pos_x, f32 pos_y, f32 pos_z)
{
    efGenerator *gtor;
    s32 i;
    
    for (i = 0; i < ARRAY_COUNT(sLBParticleStructsAllocLinks); i++)
    {
        efParticle *ptcl = sLBParticleStructsAllocLinks[i];
        
        while (ptcl != NULL)
        {
            ptcl->pos.x = pos_x;
            ptcl->pos.y = pos_y;
            ptcl->pos.z = pos_z;

            ptcl = ptcl->next;
        }
    }
    gtor = sLBParticleGeneratorsAllocLinks[0];
    
    while (gtor != NULL)
    {
        gtor->pos.x = pos_x;
        gtor->pos.y = pos_y;
        gtor->pos.z = pos_z;

        gtor = gtor->next;
    }
}

// 0x800D3D64
void func_ovl0_800D3D64(u16 generator_id, s32 link_id)
{
	efParticle *ptcl;
	efGenerator *gtor;

	for (ptcl = sLBParticleStructsAllocLinks[link_id]; ptcl != NULL; ptcl = ptcl->next)
	{
		if (ptcl->generator_id == generator_id)
		{
			ptcl->flags |= 0x800;
		}
	}
	for (gtor = sLBParticleGeneratorsAllocLinks[0]; gtor != NULL; gtor = gtor->next)
	{
		if (gtor->generator_id == generator_id)
		{
			gtor->flags |= 0x800;
		}
	}
}

// 0x800D3DE8
void func_ovl0_800D3DE8(u16 generator_id, s32 link_id)
{
	efParticle *ptcl;
	efGenerator *gtor;

	for (ptcl = sLBParticleStructsAllocLinks[link_id]; ptcl != NULL; ptcl = ptcl->next)
	{
		if (ptcl->generator_id == generator_id)
		{
			ptcl->flags &= ~0x800;
		}
	}
	for (gtor = sLBParticleGeneratorsAllocLinks[0]; gtor != NULL; gtor = gtor->next)
	{
		if (gtor->generator_id == generator_id)
		{
			gtor->flags &= ~0x800;
		}
	}
}
