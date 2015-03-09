/*
    DGClassName class decleration/implementation
    (c) 2003 root-1 Software
*/

Type definitions:
0	Normal
1	Sword
2	Fighting
3	Flying
4	Remote
5	WhiteMagic
6	BlackMagic
7	Wood
8	Metal
9	Fire
10	Wind
11	Water
12	Enhanced

On a DGTypeHandle::Lookup call:
-1 = absorbes damage;
0 = nothing special
1 = weak attack
2 = strong attack

Attack definitions/type:


Item definitions:
0	Potion
1	Ether
2	Phoenix Down
3	Cure
4	Rest Potion

Status tags:
n	Normal
p	Poisoned
s	Sleeping
k	KO'ed

DGCharacter::CharType()
1 = DGPlayable
2 = DGDemi
3 = DGSummons

DGIntelligence::Type()
0 = HumanPlayableIntel
1 = HumanSummonsIntel

ATTACK - execute standard attack
SPECIAL - choose and execute special attack
ITEM - choose and use item
SUMMON - choose and summon
RETURN - (DGSummons only) return without attacking
FUSE - DGPlayable fuse with a DGDemi
DEFUSE - de-fuse from DGDemi
TRANSFORM - transform into different self?
LIMIT - execute "limit break" attack

Bug meanings:
Bug01: out of range in call to DGTypeHandle::TypeName
Bug02: out of range in call to DGItemHandle::Name