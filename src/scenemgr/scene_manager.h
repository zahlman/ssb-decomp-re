#ifndef SCENEMGR_SCENE_MANGAGER_H
#define SCENEMGR_SCENE_MANGAGER_H

#include <PR/ultratypes.h>

// types
// the fields are only here to faciliate the entry of the raw data
// change as needed to fit the actual shape of the struct

#define SSB64_NUM_PLAYABLE_CHARACTERS 12

enum TimeStockFlag { TIMESTOCK_TIME_ON = 1 << 0, TIMESTOCK_STOCK_ON = 1 << 1 };

enum HandicapMode { HANDICAP_MODE_OFF, HANDICAP_MODE_MANUAL, HANDICAP_MODE_AUTO };

enum ItemAppearanceRate {
	ITEM_RATE_NONE,
	ITEM_RATE_VERY_LOW,
	ITEM_RATE_LOW,
	ITEM_RATE_MIDDLE,
	ITEM_RATE_HIGH,
	ITEM_RATE_VERY_HIGH
};

enum PlayerControlledBy { PLAYER_CONTROL_MAN, PLAYER_CONTROL_CPU, PLAYER_NOT_PRESENT };

// overlay defines
#define _ovl0SegRomStart 0x00043220
#define _ovl0SegRomEnd 0x00051c90
#define _ovl0SegStart 0x800c7840
#define _ovl0TextStart 0x800c7840
#define _ovl0TextEnd 0x800d4ca0
#define _ovl0DataStart 0x800d4ca0
#define _ovl0DataEnd 0x800d62b0
#define _ovl0SegNoloadStart 0x800d62b0
#define _ovl0SegNoloadEnd 0x800d6490
#define _ovl1SegRomStart 0x001079c0
#define _ovl1SegRomEnd 0x00109fb0
#define _ovl1SegStart 0x803903e0
#define _ovl1TextStart 0x803903e0
#define _ovl1TextEnd 0x80390be0
#define _ovl1DataStart 0x80390be0
#define _ovl1DataEnd 0x803929d0
#define _ovl1SegNoloadStart 0x803929d0
#define _ovl1SegNoloadEnd 0x80392a00
#define _ovl2SegRomStart 0x00051c90
#define _ovl2SegRomEnd 0x000ac540
#define _ovl2SegStart 0x800d6490
#define _ovl2TextStart 0x800d6490
#define _ovl2TextEnd 0x80116bd0
#define _ovl2DataStart 0x80116bd0
#define _ovl2DataEnd 0x80130d40
#define _ovl2SegNoloadStart 0x80130d40
#define _ovl2SegNoloadEnd 0x80131b00
#define _ovl3SegRomStart 0x000ac540
#define _ovl3SegRomEnd 0x001079c0
#define _ovl3SegStart 0x80131b00
#define _ovl3TextStart 0x80131b00
#define _ovl3TextEnd 0x80186660
#define _ovl3DataStart 0x80186660
#define _ovl3DataEnd 0x8018cf80
#define _ovl3SegNoloadStart 0x8018cf80
#define _ovl3SegNoloadEnd 0x8018d0c0
#define _ovl4SegRomStart 0x00109fb0
#define _ovl4SegRomEnd 0x0010b370
#define _ovl4SegStart 0x8018d0c0
#define _ovl4TextStart 0x8018d0c0
#define _ovl4TextEnd 0x8018e3d0
#define _ovl4DataStart 0x8018e3d0
#define _ovl4DataEnd 0x8018e480
#define _ovl4SegNoloadStart 0x8018e480
#define _ovl4SegNoloadEnd 0x8018e7e0
#define _ovl5SegRomStart 0x0010b370
#define _ovl5SegRomEnd 0x0010b920
#define _ovl5SegStart 0x8018d0c0
#define _ovl5TextStart 0x8018d0c0
#define _ovl5TextEnd 0x8018d580
#define _ovl5DataStart 0x8018d580
#define _ovl5DataEnd 0x8018d670
#define _ovl5SegNoloadStart 0x8018d670
#define _ovl5SegNoloadEnd 0x8018d950
#define _ovl6SegRomStart 0x00111800
#define _ovl6SegRomEnd 0x001138e0
#define _ovl6SegStart 0x8018d0c0
#define _ovl6TextStart 0x8018d0c0
#define _ovl6TextEnd 0x8018eec0
#define _ovl6DataStart 0x8018eec0
#define _ovl6DataEnd 0x8018f1a0
#define _ovl6SegNoloadStart 0x8018f1a0
#define _ovl6SegNoloadEnd 0x8018f710
#define _ovl7SegRomStart 0x001138e0
#define _ovl7SegRomEnd 0x00117180
#define _ovl7SegStart 0x8018d0c0
#define _ovl7TextStart 0x8018d0c0
#define _ovl7TextEnd 0x80190770
#define _ovl7DataStart 0x80190770
#define _ovl7DataEnd 0x80190960
#define _ovl7SegNoloadStart 0x80190960
#define _ovl7SegNoloadEnd 0x80190fa0
#define _ovl8SegRomStart 0x0018dcb0
#define _ovl8SegRomEnd 0x001ab6b0
#define _ovl8SegStart 0x80371460
#define _ovl8TextStart 0x80371460
#define _ovl8TextEnd 0x80387ca0
#define _ovl8DataStart 0x80387ca0
#define _ovl8DataEnd 0x8038ee60
#define _ovl8SegNoloadStart 0x8038ee60
#define _ovl8SegNoloadEnd 0x803903e0
#define _ovl9SegRomStart 0x001ab6b0
#define _ovl9SegRomEnd 0x001ac870
#define _ovl9SegStart 0x80369240
#define _ovl9TextStart 0x80369240
#define _ovl9TextEnd 0x80369f60
#define _ovl9DataStart 0x80369f60
#define _ovl9DataEnd 0x8036a400
#define _ovl9SegNoloadStart 0x8036a400
#define _ovl9SegNoloadEnd 0x80371460
#define _ovl10SegRomStart 0x00117180
#define _ovl10SegRomEnd 0x00119ac0
#define _ovl10SegStart 0x80131b00
#define _ovl10TextStart 0x80131b00
#define _ovl10TextEnd 0x801341e0
#define _ovl10DataStart 0x801341e0
#define _ovl10DataEnd 0x80134440
#define _ovl10SegNoloadStart 0x80134440
#define _ovl10SegNoloadEnd 0x801345b0
#define _ovl11SegRomStart 0x00119ac0
#define _ovl11SegRomEnd 0x00119df0
#define _ovl11SegStart 0x800d6490
#define _ovl11TextStart 0x800d6490
#define _ovl11TextEnd 0x800d6700
#define _ovl11DataStart 0x800d6700
#define _ovl11DataEnd 0x800d67c0
#define _ovl11SegNoloadStart 0x800d67c0
#define _ovl11SegNoloadEnd 0x800d6b30
#define _ovl12SegRomStart 0x00119df0
#define _ovl12SegRomEnd 0x0011a340
#define _ovl12SegStart 0x800d6490
#define _ovl12TextStart 0x800d6490
#define _ovl12TextEnd 0x800d6680
#define _ovl12DataStart 0x800d6680
#define _ovl12DataEnd 0x800d69e0
#define _ovl12SegNoloadStart 0x800d69e0
#define _ovl12SegNoloadEnd 0x800d69f0
#define _ovl13SegRomStart 0x0011a340
#define _ovl13SegRomEnd 0x0011b970
#define _ovl13SegStart 0x80131b00
#define _ovl13TextStart 0x80131b00
#define _ovl13TextEnd 0x801321e0
#define _ovl13DataStart 0x801321e0
#define _ovl13DataEnd 0x80133130
#define _ovl13SegNoloadStart 0x80133130
#define _ovl13SegNoloadEnd 0x80133170
#define _ovl14SegRomStart 0x0011b970
#define _ovl14SegRomEnd 0x0011ca90
#define _ovl14SegStart 0x80131b00
#define _ovl14TextStart 0x80131b00
#define _ovl14TextEnd 0x80132690
#define _ovl14DataStart 0x80132690
#define _ovl14DataEnd 0x80132c20
#define _ovl14SegNoloadStart 0x80132c20
#define _ovl14SegNoloadEnd 0x80133130
#define _ovl15SegRomStart 0x00150740
#define _ovl15SegRomEnd 0x00150ca0
#define _ovl15SegStart 0x800d6490
#define _ovl15TextStart 0x800d6490
#define _ovl15TextEnd 0x800d66e0
#define _ovl15DataStart 0x800d66e0
#define _ovl15DataEnd 0x800d69f0
#define _ovl15SegNoloadStart 0x800d69f0
#define _ovl15SegNoloadEnd 0x800d6a00
#define _ovl16SegRomStart 0x0018d030
#define _ovl16SegRomEnd 0x0018dcb0
#define _ovl16SegStart 0x800d6490
#define _ovl16TextStart 0x800d6490
#define _ovl16TextEnd 0x800d7010
#define _ovl16DataStart 0x800d7010
#define _ovl16DataEnd 0x800d7110
#define _ovl16SegNoloadStart 0x800d7110
#define _ovl16SegNoloadEnd 0x800d7170
#define _ovl17SegRomStart 0x0011ca90
#define _ovl17SegRomEnd 0x0011dc10
#define _ovl17SegStart 0x80131b00
#define _ovl17TextStart 0x80131b00
#define _ovl17TextEnd 0x80132b90
#define _ovl17DataStart 0x80132b90
#define _ovl17DataEnd 0x80132c80
#define _ovl17SegNoloadStart 0x80132c80
#define _ovl17SegNoloadEnd 0x80132d70
#define _ovl18SegRomStart 0x0011dc10
#define _ovl18SegRomEnd 0x0011f2b0
#define _ovl18SegStart 0x80131b00
#define _ovl18TextStart 0x80131b00
#define _ovl18TextEnd 0x80133080
#define _ovl18DataStart 0x80133080
#define _ovl18DataEnd 0x801331a0
#define _ovl18SegNoloadStart 0x801331a0
#define _ovl18SegNoloadEnd 0x801332a0
#define _ovl19SegRomStart 0x001224b0
#define _ovl19SegRomEnd 0x001252e0
#define _ovl19SegStart 0x80131b00
#define _ovl19TextStart 0x80131b00
#define _ovl19TextEnd 0x801347b0
#define _ovl19DataStart 0x801347b0
#define _ovl19DataEnd 0x80134930
#define _ovl19SegNoloadStart 0x80134930
#define _ovl19SegNoloadEnd 0x80134a50
#define _ovl20SegRomStart 0x001252e0
#define _ovl20SegRomEnd 0x001280a0
#define _ovl20SegStart 0x80131b00
#define _ovl20TextStart 0x80131b00
#define _ovl20TextEnd 0x801346c0
#define _ovl20DataStart 0x801346c0
#define _ovl20DataEnd 0x801348c0
#define _ovl20SegNoloadStart 0x801348c0
#define _ovl20SegNoloadEnd 0x801349e0
#define _ovl21SegRomStart 0x001280a0
#define _ovl21SegRomEnd 0x00129970
#define _ovl21SegStart 0x80131b00
#define _ovl21TextStart 0x80131b00
#define _ovl21TextEnd 0x80133210
#define _ovl21DataStart 0x80133210
#define _ovl21DataEnd 0x801333d0
#define _ovl21SegNoloadStart 0x801333d0
#define _ovl21SegNoloadEnd 0x80133540
#define _ovl22SegRomStart 0x00129970
#define _ovl22SegRomEnd 0x0012a4c0
#define _ovl22SegStart 0x80131b00
#define _ovl22TextStart 0x80131b00
#define _ovl22TextEnd 0x80132500
#define _ovl22DataStart 0x80132500
#define _ovl22DataEnd 0x80132650
#define _ovl22SegNoloadStart 0x80132650
#define _ovl22SegNoloadEnd 0x80132990
#define _ovl23SegRomStart 0x0012a4c0
#define _ovl23SegRomEnd 0x0012ae40
#define _ovl23SegStart 0x80131b00
#define _ovl23TextStart 0x80131b00
#define _ovl23TextEnd 0x80132370
#define _ovl23DataStart 0x80132370
#define _ovl23DataEnd 0x80132480
#define _ovl23SegNoloadStart 0x80132480
#define _ovl23SegNoloadEnd 0x80132800
#define _ovl24SegRomStart 0x0012ae40
#define _ovl24SegRomEnd 0x0012ef60
#define _ovl24SegStart 0x80131b00
#define _ovl24TextStart 0x80131b00
#define _ovl24TextEnd 0x80134df0
#define _ovl24DataStart 0x80134df0
#define _ovl24DataEnd 0x80135c20
#define _ovl24SegNoloadStart 0x80135c20
#define _ovl24SegNoloadEnd 0x80136070
#define _ovl25SegRomStart 0x0012ef60
#define _ovl25SegRomEnd 0x0012fd80
#define _ovl25SegStart 0x80131b00
#define _ovl25TextStart 0x80131b00
#define _ovl25TextEnd 0x80132830
#define _ovl25DataStart 0x80132830
#define _ovl25DataEnd 0x80132920
#define _ovl25SegNoloadStart 0x80132920
#define _ovl25SegNoloadEnd 0x80132a40
#define _ovl26SegRomStart 0x0012fd80
#define _ovl26SegRomEnd 0x00139d00
#define _ovl26SegStart 0x80131b00
#define _ovl26TextStart 0x80131b00
#define _ovl26TextEnd 0x8013b3a0
#define _ovl26DataStart 0x8013b3a0
#define _ovl26DataEnd 0x8013ba80
#define _ovl26SegNoloadStart 0x8013ba80
#define _ovl26SegNoloadEnd 0x8013c4c0
#define _ovl27SegRomStart 0x00139d00
#define _ovl27SegRomEnd 0x001410e0
#define _ovl27SegStart 0x80131b00
#define _ovl27TextStart 0x80131b00
#define _ovl27TextEnd 0x801385b0
#define _ovl27DataStart 0x801385b0
#define _ovl27DataEnd 0x80138ee0
#define _ovl27SegNoloadStart 0x80138ee0
#define _ovl27SegNoloadEnd 0x801396d0
#define _ovl28SegRomStart 0x001410e0
#define _ovl28SegRomEnd 0x00147b30
#define _ovl28SegStart 0x80131b00
#define _ovl28TextStart 0x80131b00
#define _ovl28TextEnd 0x80137f60
#define _ovl28DataStart 0x80137f60
#define _ovl28DataEnd 0x80138550
#define _ovl28SegNoloadStart 0x80138550
#define _ovl28SegNoloadEnd 0x80138cc0
#define _ovl29SegRomStart 0x00147b30
#define _ovl29SegRomEnd 0x0014d670
#define _ovl29SegStart 0x80131b00
#define _ovl29TextStart 0x80131b00
#define _ovl29TextEnd 0x80136f50
#define _ovl29DataStart 0x80136f50
#define _ovl29DataEnd 0x80137640
#define _ovl29SegNoloadStart 0x80137640
#define _ovl29SegNoloadEnd 0x80137e30
#define _ovl30SegRomStart 0x0014d670
#define _ovl30SegRomEnd 0x00150740
#define _ovl30SegStart 0x80131b00
#define _ovl30TextStart 0x80131b00
#define _ovl30TextEnd 0x801344d0
#define _ovl30DataStart 0x801344d0
#define _ovl30DataEnd 0x80134bd0
#define _ovl30SegNoloadStart 0x80134bd0
#define _ovl30SegNoloadEnd 0x80134e30
#define _ovl31SegRomStart 0x00150ca0
#define _ovl31SegRomEnd 0x00158a40
#define _ovl31SegStart 0x80131b00
#define _ovl31TextStart 0x80131b00
#define _ovl31TextEnd 0x80138ef0
#define _ovl31DataStart 0x80138ef0
#define _ovl31DataEnd 0x801398a0
#define _ovl31SegNoloadStart 0x801398a0
#define _ovl31SegNoloadEnd 0x8013a070
#define _ovl32SegRomStart 0x00158a40
#define _ovl32SegRomEnd 0x0015db50
#define _ovl32SegStart 0x80131b00
#define _ovl32TextStart 0x80131b00
#define _ovl32TextEnd 0x80136630
#define _ovl32DataStart 0x80136630
#define _ovl32DataEnd 0x80136c10
#define _ovl32SegNoloadStart 0x80136c10
#define _ovl32SegNoloadEnd 0x80136da0
#define _ovl33SegRomStart 0x0015db50
#define _ovl33SegRomEnd 0x00162640
#define _ovl33SegStart 0x80131b00
#define _ovl33TextStart 0x80131b00
#define _ovl33TextEnd 0x801340b0
#define _ovl33DataStart 0x801340b0
#define _ovl33DataEnd 0x801365f0
#define _ovl33SegNoloadStart 0x801365f0
#define _ovl33SegNoloadEnd 0x80136a90
#define _ovl34SegRomStart 0x00162640
#define _ovl34SegRomEnd 0x00165810
#define _ovl34SegStart 0x80131b00
#define _ovl34TextStart 0x80131b00
#define _ovl34TextEnd 0x80134a20
#define _ovl34DataStart 0x80134a20
#define _ovl34DataEnd 0x80134cd0
#define _ovl34SegNoloadStart 0x80134cd0
#define _ovl34SegNoloadEnd 0x801350d0
#define _ovl35SegRomStart 0x00165810
#define _ovl35SegRomEnd 0x001666f0
#define _ovl35SegStart 0x80131b00
#define _ovl35TextStart 0x80131b00
#define _ovl35TextEnd 0x801328a0
#define _ovl35DataStart 0x801328a0
#define _ovl35DataEnd 0x801329e0
#define _ovl35SegNoloadStart 0x801329e0
#define _ovl35SegNoloadEnd 0x80132bc0
#define _ovl36SegRomStart 0x001666f0
#define _ovl36SegRomEnd 0x00167830
#define _ovl36SegStart 0x8018d0c0
#define _ovl36TextStart 0x8018d0c0
#define _ovl36TextEnd 0x8018e090
#define _ovl36DataStart 0x8018e090
#define _ovl36DataEnd 0x8018e200
#define _ovl36SegNoloadStart 0x8018e200
#define _ovl36SegNoloadEnd 0x8018e620
#define _ovl37SegRomStart 0x00167830
#define _ovl37SegRomEnd 0x00168930
#define _ovl37SegStart 0x8018d0c0
#define _ovl37TextStart 0x8018d0c0
#define _ovl37TextEnd 0x8018e070
#define _ovl37DataStart 0x8018e070
#define _ovl37DataEnd 0x8018e1c0
#define _ovl37SegNoloadStart 0x8018e1c0
#define _ovl37SegNoloadEnd 0x8018e5e0
#define _ovl38SegRomStart 0x00168930
#define _ovl38SegRomEnd 0x00169ae0
#define _ovl38SegStart 0x8018d0c0
#define _ovl38TextStart 0x8018d0c0
#define _ovl38TextEnd 0x8018e120
#define _ovl38DataStart 0x8018e120
#define _ovl38DataEnd 0x8018e270
#define _ovl38SegNoloadStart 0x8018e270
#define _ovl38SegNoloadEnd 0x8018e690
#define _ovl39SegRomStart 0x00169ae0
#define _ovl39SegRomEnd 0x0016ac10
#define _ovl39SegStart 0x8018d0c0
#define _ovl39TextStart 0x8018d0c0
#define _ovl39TextEnd 0x8018e090
#define _ovl39DataStart 0x8018e090
#define _ovl39DataEnd 0x8018e1f0
#define _ovl39SegNoloadStart 0x8018e1f0
#define _ovl39SegNoloadEnd 0x8018e610
#define _ovl40SegRomStart 0x0016ac10
#define _ovl40SegRomEnd 0x0016bd10
#define _ovl40SegStart 0x8018d0c0
#define _ovl40TextStart 0x8018d0c0
#define _ovl40TextEnd 0x8018e070
#define _ovl40DataStart 0x8018e070
#define _ovl40DataEnd 0x8018e1c0
#define _ovl40SegNoloadStart 0x8018e1c0
#define _ovl40SegNoloadEnd 0x8018e5e0
#define _ovl41SegRomStart 0x0016bd10
#define _ovl41SegRomEnd 0x0016ce70
#define _ovl41SegStart 0x8018d0c0
#define _ovl41TextStart 0x8018d0c0
#define _ovl41TextEnd 0x8018e0c0
#define _ovl41DataStart 0x8018e0c0
#define _ovl41DataEnd 0x8018e220
#define _ovl41SegNoloadStart 0x8018e220
#define _ovl41SegNoloadEnd 0x8018e640
#define _ovl42SegRomStart 0x0016ce70
#define _ovl42SegRomEnd 0x0016dfd0
#define _ovl42SegStart 0x8018d0c0
#define _ovl42TextStart 0x8018d0c0
#define _ovl42TextEnd 0x8018e0c0
#define _ovl42DataStart 0x8018e0c0
#define _ovl42DataEnd 0x8018e220
#define _ovl42SegNoloadStart 0x8018e220
#define _ovl42SegNoloadEnd 0x8018e640
#define _ovl43SegRomStart 0x0016dfd0
#define _ovl43SegRomEnd 0x0016f130
#define _ovl43SegStart 0x8018d0c0
#define _ovl43TextStart 0x8018d0c0
#define _ovl43TextEnd 0x8018e0b0
#define _ovl43DataStart 0x8018e0b0
#define _ovl43DataEnd 0x8018e220
#define _ovl43SegNoloadStart 0x8018e220
#define _ovl43SegNoloadEnd 0x8018e640
#define _ovl44SegRomStart 0x0016f130
#define _ovl44SegRomEnd 0x0016fd40
#define _ovl44SegStart 0x80131b00
#define _ovl44TextStart 0x80131b00
#define _ovl44TextEnd 0x801325d0
#define _ovl44DataStart 0x801325d0
#define _ovl44DataEnd 0x80132710
#define _ovl44SegNoloadStart 0x80132710
#define _ovl44SegNoloadEnd 0x80132ab0
#define _ovl45SegRomStart 0x0016fd40
#define _ovl45SegRomEnd 0x00170660
#define _ovl45SegStart 0x80131b00
#define _ovl45TextStart 0x80131b00
#define _ovl45TextEnd 0x80132330
#define _ovl45DataStart 0x80132330
#define _ovl45DataEnd 0x80132420
#define _ovl45SegNoloadStart 0x80132420
#define _ovl45SegNoloadEnd 0x80132600
#define _ovl46SegRomStart 0x00170660
#define _ovl46SegRomEnd 0x00171320
#define _ovl46SegStart 0x80131b00
#define _ovl46TextStart 0x80131b00
#define _ovl46TextEnd 0x801326d0
#define _ovl46DataStart 0x801326d0
#define _ovl46DataEnd 0x801327c0
#define _ovl46SegNoloadStart 0x801327c0
#define _ovl46SegNoloadEnd 0x801329a0
#define _ovl47SegRomStart 0x00171320
#define _ovl47SegRomEnd 0x001721e0
#define _ovl47SegStart 0x80131b00
#define _ovl47TextStart 0x80131b00
#define _ovl47TextEnd 0x801328d0
#define _ovl47DataStart 0x801328d0
#define _ovl47DataEnd 0x801329c0
#define _ovl47SegNoloadStart 0x801329c0
#define _ovl47SegNoloadEnd 0x80132ba0
#define _ovl48SegRomStart 0x001721e0
#define _ovl48SegRomEnd 0x00172b60
#define _ovl48SegStart 0x80131b00
#define _ovl48TextStart 0x80131b00
#define _ovl48TextEnd 0x801323a0
#define _ovl48DataStart 0x801323a0
#define _ovl48DataEnd 0x80132480
#define _ovl48SegNoloadStart 0x80132480
#define _ovl48SegNoloadEnd 0x80132660
#define _ovl49SegRomStart 0x00172b60
#define _ovl49SegRomEnd 0x00173a30
#define _ovl49SegStart 0x80131b00
#define _ovl49TextStart 0x80131b00
#define _ovl49TextEnd 0x801328d0
#define _ovl49DataStart 0x801328d0
#define _ovl49DataEnd 0x801329d0
#define _ovl49SegNoloadStart 0x801329d0
#define _ovl49SegNoloadEnd 0x80132d80
#define _ovl50SegRomStart 0x00173a30
#define _ovl50SegRomEnd 0x00174940
#define _ovl50SegStart 0x80131b00
#define _ovl50TextStart 0x80131b00
#define _ovl50TextEnd 0x801328f0
#define _ovl50DataStart 0x801328f0
#define _ovl50DataEnd 0x80132a10
#define _ovl50SegNoloadStart 0x80132a10
#define _ovl50SegNoloadEnd 0x80132c10
#define _ovl51SegRomStart 0x00174940
#define _ovl51SegRomEnd 0x001752c0
#define _ovl51SegStart 0x8018d0c0
#define _ovl51TextStart 0x8018d0c0
#define _ovl51TextEnd 0x8018d870
#define _ovl51DataStart 0x8018d870
#define _ovl51DataEnd 0x8018da40
#define _ovl51SegNoloadStart 0x8018da40
#define _ovl51SegNoloadEnd 0x8018de60
#define _ovl52SegRomStart 0x001752c0
#define _ovl52SegRomEnd 0x00175f00
#define _ovl52SegStart 0x80131b00
#define _ovl52TextStart 0x80131b00
#define _ovl52TextEnd 0x80132640
#define _ovl52DataStart 0x80132640
#define _ovl52DataEnd 0x80132740
#define _ovl52SegNoloadStart 0x80132740
#define _ovl52SegNoloadEnd 0x80132920
#define _ovl53SegRomStart 0x00175f00
#define _ovl53SegRomEnd 0x001774a0
#define _ovl53SegStart 0x80131b00
#define _ovl53TextStart 0x80131b00
#define _ovl53TextEnd 0x80132e80
#define _ovl53DataStart 0x80132e80
#define _ovl53DataEnd 0x801330a0
#define _ovl53SegNoloadStart 0x801330a0
#define _ovl53SegNoloadEnd 0x801331c0
#define _ovl54SegRomStart 0x001774a0
#define _ovl54SegRomEnd 0x00178560
#define _ovl54SegStart 0x80131b00
#define _ovl54TextStart 0x80131b00
#define _ovl54TextEnd 0x80132ad0
#define _ovl54DataStart 0x80132ad0
#define _ovl54DataEnd 0x80132bc0
#define _ovl54SegNoloadStart 0x80132bc0
#define _ovl54SegNoloadEnd 0x80132f80
#define _ovl55SegRomStart 0x00178560
#define _ovl55SegRomEnd 0x0017ad50
#define _ovl55SegStart 0x80131b00
#define _ovl55TextStart 0x80131b00
#define _ovl55TextEnd 0x80134160
#define _ovl55DataStart 0x80134160
#define _ovl55DataEnd 0x801342f0
#define _ovl55SegNoloadStart 0x801342f0
#define _ovl55SegNoloadEnd 0x80134540
#define _ovl56SegRomStart 0x0017ad50
#define _ovl56SegRomEnd 0x0017e510
#define _ovl56SegStart 0x80131b00
#define _ovl56TextStart 0x80131b00
#define _ovl56TextEnd 0x80134ee0
#define _ovl56DataStart 0x80134ee0
#define _ovl56DataEnd 0x801352c0
#define _ovl56SegNoloadStart 0x801352c0
#define _ovl56SegNoloadEnd 0x801355b0
#define _ovl57SegRomStart 0x0017e510
#define _ovl57SegRomEnd 0x0017ecc0
#define _ovl57SegStart 0x80131b00
#define _ovl57TextStart 0x80131b00
#define _ovl57TextEnd 0x80132100
#define _ovl57DataStart 0x80132100
#define _ovl57DataEnd 0x801322b0
#define _ovl57SegNoloadStart 0x801322b0
#define _ovl57SegNoloadEnd 0x80132300
#define _ovl58SegRomStart 0x0017ecc0
#define _ovl58SegRomEnd 0x0017f200
#define _ovl58SegStart 0x80131b00
#define _ovl58TextStart 0x80131b00
#define _ovl58TextEnd 0x80131f50
#define _ovl58DataStart 0x80131f50
#define _ovl58DataEnd 0x80132040
#define _ovl58SegNoloadStart 0x80132040
#define _ovl58SegNoloadEnd 0x80132080
#define _ovl59SegRomStart 0x0017f200
#define _ovl59SegRomEnd 0x00187ed0
#define _ovl59SegStart 0x80131b00
#define _ovl59TextStart 0x80131b00
#define _ovl59TextEnd 0x80135260
#define _ovl59DataStart 0x80135260
#define _ovl59DataEnd 0x8013a7d0
#define _ovl59SegNoloadStart 0x8013a7d0
#define _ovl59SegNoloadEnd 0x8013aa60
#define _ovl60SegRomStart 0x0011f2b0
#define _ovl60SegRomEnd 0x00120f50
#define _ovl60SegStart 0x80131b00
#define _ovl60TextStart 0x80131b00
#define _ovl60TextEnd 0x80133620
#define _ovl60DataStart 0x80133620
#define _ovl60DataEnd 0x801337a0
#define _ovl60SegNoloadStart 0x801337a0
#define _ovl60SegNoloadEnd 0x801338c0
#define _ovl61SegRomStart 0x00120f50
#define _ovl61SegRomEnd 0x001224b0
#define _ovl61SegStart 0x80131b00
#define _ovl61TextStart 0x80131b00
#define _ovl61TextEnd 0x80132f20
#define _ovl61DataStart 0x80132f20
#define _ovl61DataEnd 0x80133060
#define _ovl61SegNoloadStart 0x80133060
#define _ovl61SegNoloadEnd 0x80133170
#define _ovl62SegRomStart 0x00187ed0
#define _ovl62SegRomEnd 0x0018a6d0
#define _ovl62SegStart 0x80131b00
#define _ovl62TextStart 0x80131b00
#define _ovl62TextEnd 0x801339e0
#define _ovl62DataStart 0x801339e0
#define _ovl62DataEnd 0x80134300
#define _ovl62SegNoloadStart 0x80134300
#define _ovl62SegNoloadEnd 0x80134480
#define _ovl63SegRomStart 0x0018a6d0
#define _ovl63SegRomEnd 0x0018be00
#define _ovl63SegStart 0x8018d0c0
#define _ovl63TextStart 0x8018d0c0
#define _ovl63TextEnd 0x8018e6e0
#define _ovl63DataStart 0x8018e6e0
#define _ovl63DataEnd 0x8018e7f0
#define _ovl63SegNoloadStart 0x8018e7f0
#define _ovl63SegNoloadEnd 0x8018ec00
#define _ovl64SegRomStart 0x0018be00
#define _ovl64SegRomEnd 0x0018d030
#define _ovl64SegStart 0x8018d0c0
#define _ovl64TextStart 0x8018d0c0
#define _ovl64TextEnd 0x8018e160
#define _ovl64DataStart 0x8018e160
#define _ovl64DataEnd 0x8018e2f0
#define _ovl64SegNoloadStart 0x8018e2f0
#define _ovl64SegNoloadEnd 0x8018e860

// Macro for creating array at dSCManagerOverlays inserting all the data above
#define GENERATE_OVERLAY_SECTION_DATA(OVL_NUM) { (u32)_ovl##OVL_NUM##SegRomStart, (u32)_ovl##OVL_NUM##SegRomEnd, _ovl##OVL_NUM##SegStart, _ovl##OVL_NUM##TextStart, _ovl##OVL_NUM##TextEnd, _ovl##OVL_NUM##DataStart, _ovl##OVL_NUM##DataEnd, _ovl##OVL_NUM##SegNoloadStart, _ovl##OVL_NUM##SegNoloadEnd, }

#endif /* SCENEMGR_SCENE_MANGAGER_H */

//------- Potentially outdated structs -------//

// struct RecordCharCombo {
//     /* 0x00 */ u16 gamesWith;
//     /* 0x02 */ u16 playedAgainst;
// }; // size == 4

// struct BattlePlayerState {
//     /* 0x00 */ u8 cpuLevel;
//     /* 0x01 */ u8 handicapLevel;
//     /* 0x02 */ u8 controlledBy;
//     /* 0x03 */ u8 character;
//     /* 0x04 */ u8 team;
//     /* 0x05 */ u8 unk05;
//     /* 0x06 */ u8 charColor;
//     /* 0x08 */ u16 unk08[(0x74 - 0x8) / 2];
// }; // size == 0x74

