#include "stdafx.h"

Phase2::Phase2()
{
	this->animation = AddComponent<Animation>();

	phase2 = *new vector<ObImage*>(112);
	phase2[0] = new ObImage(L"phase2 (1).png");
	phase2[1] = new ObImage(L"phase2 (2).png");
	phase2[2] = new ObImage(L"phase2 (3).png");
	phase2[3] = new ObImage(L"phase2 (4).png");
	phase2[4] = new ObImage(L"phase2 (5).png");
	phase2[5] = new ObImage(L"phase2 (6).png");
	phase2[6] = new ObImage(L"phase2 (7).png");
	phase2[7] = new ObImage(L"phase2 (8).png");
	phase2[8] = new ObImage(L"phase2 (9).png");
	phase2[9] = new ObImage(L"phase2 (10).png");
	phase2[10] = new ObImage(L"phase2 (11).png");
	phase2[11] = new ObImage(L"phase2 (12).png");
	phase2[12] = new ObImage(L"phase2 (13).png");
	phase2[13] = new ObImage(L"phase2 (14).png");
	phase2[14] = new ObImage(L"phase2 (15).png");
	phase2[15] = new ObImage(L"phase2 (16).png");
	phase2[16] = new ObImage(L"phase2 (17).png");
	phase2[17] = new ObImage(L"phase2 (18).png");
	phase2[18] = new ObImage(L"phase2 (19).png");
	phase2[19] = new ObImage(L"phase2 (20).png");
	phase2[20] = new ObImage(L"phase2 (21).png");
	phase2[21] = new ObImage(L"phase2 (22).png");
	phase2[22] = new ObImage(L"phase2 (23).png");
	phase2[23] = new ObImage(L"phase2 (24).png");
	phase2[24] = new ObImage(L"phase2 (25).png");
	phase2[25] = new ObImage(L"phase2 (26).png");
	phase2[26] = new ObImage(L"phase2 (27).png");
	phase2[27] = new ObImage(L"phase2 (28).png");
	phase2[28] = new ObImage(L"phase2 (29).png");
	phase2[29] = new ObImage(L"phase2 (30).png");
	phase2[30] = new ObImage(L"phase2 (31).png");
	phase2[31] = new ObImage(L"phase2 (32).png");
	phase2[32] = new ObImage(L"phase2 (33).png");
	phase2[33] = new ObImage(L"phase2 (34).png");
	phase2[34] = new ObImage(L"phase2 (35).png");
	phase2[35] = new ObImage(L"phase2 (36).png");
	phase2[36] = new ObImage(L"phase2 (37).png");
	phase2[37] = new ObImage(L"phase2 (38).png");
	phase2[38] = new ObImage(L"phase2 (39).png");
	phase2[39] = new ObImage(L"phase2 (40).png");
	phase2[40] = new ObImage(L"phase2 (41).png");
	phase2[41] = new ObImage(L"phase2 (42).png");
	phase2[42] = new ObImage(L"phase2 (43).png");
	phase2[43] = new ObImage(L"phase2 (44).png");
	phase2[44] = new ObImage(L"phase2 (45).png");
	phase2[45] = new ObImage(L"phase2 (46).png");
	phase2[46] = new ObImage(L"phase2 (47).png");
	phase2[47] = new ObImage(L"phase2 (48).png");
	phase2[48] = new ObImage(L"phase2 (49).png");
	phase2[49] = new ObImage(L"phase2 (50).png");
	phase2[50] = new ObImage(L"phase2 (51).png");
	phase2[51] = new ObImage(L"phase2 (52).png");
	phase2[52] = new ObImage(L"phase2 (53).png");
	phase2[53] = new ObImage(L"phase2 (54).png");
	phase2[54] = new ObImage(L"phase2 (55).png");
	phase2[55] = new ObImage(L"phase2 (56).png");
	phase2[56] = new ObImage(L"phase2 (57).png");
	phase2[57] = new ObImage(L"phase2 (58).png");
	phase2[58] = new ObImage(L"phase2 (59).png");
	phase2[59] = new ObImage(L"phase2 (60).png");
	phase2[60] = new ObImage(L"phase2 (61).png");
	phase2[61] = new ObImage(L"phase2 (62).png");
	phase2[62] = new ObImage(L"phase2 (63).png");
	phase2[63] = new ObImage(L"phase2 (64).png");
	phase2[64] = new ObImage(L"phase2 (65).png");
	phase2[65] = new ObImage(L"phase2 (66).png");
	phase2[66] = new ObImage(L"phase2 (67).png");
	phase2[67] = new ObImage(L"phase2 (68).png");
	phase2[68] = new ObImage(L"phase2 (69).png");
	phase2[69] = new ObImage(L"phase2 (70).png");
	phase2[70] = new ObImage(L"phase2 (71).png");
	phase2[71] = new ObImage(L"phase2 (72).png");
	phase2[72] = new ObImage(L"phase2 (73).png");
	phase2[73] = new ObImage(L"phase2 (74).png");
	phase2[74] = new ObImage(L"phase2 (75).png");
	phase2[75] = new ObImage(L"phase2 (76).png");
	phase2[76] = new ObImage(L"phase2 (77).png");
	phase2[77] = new ObImage(L"phase2 (78).png");
	phase2[78] = new ObImage(L"phase2 (79).png");
	phase2[79] = new ObImage(L"phase2 (80).png");
	phase2[80] = new ObImage(L"phase2 (81).png");
	phase2[81] = new ObImage(L"phase2 (82).png");
	phase2[82] = new ObImage(L"phase2 (83).png");
	phase2[83] = new ObImage(L"phase2 (84).png");
	phase2[84] = new ObImage(L"phase2 (85).png");
	phase2[85] = new ObImage(L"phase2 (86).png");
	phase2[86] = new ObImage(L"phase2 (87).png");
	phase2[87] = new ObImage(L"phase2 (88).png");
	phase2[88] = new ObImage(L"phase2 (89).png");
	phase2[89] = new ObImage(L"phase2 (90).png");
	phase2[90] = new ObImage(L"phase2 (91).png");
	phase2[91] = new ObImage(L"phase2 (92).png");
	phase2[92] = new ObImage(L"phase2 (93).png");
	phase2[93] = new ObImage(L"phase2 (94).png");
	phase2[94] = new ObImage(L"phase2 (95).png");
	phase2[95] = new ObImage(L"phase2 (96).png");
	phase2[96] = new ObImage(L"phase2 (97).png");
	phase2[97] = new ObImage(L"phase2 (98).png");
	phase2[98] = new ObImage(L"phase2 (99).png");
	phase2[99] = new ObImage(L"phase2 (100).png");
	phase2[100] = new ObImage(L"phase2 (101).png");
	phase2[101] = new ObImage(L"phase2 (102).png");
	phase2[102] = new ObImage(L"phase2 (103).png");
	phase2[103] = new ObImage(L"phase2 (104).png");
	phase2[104] = new ObImage(L"phase2 (105).png");
	phase2[105] = new ObImage(L"phase2 (106).png");
	phase2[106] = new ObImage(L"phase2 (107).png");
	phase2[107] = new ObImage(L"phase2 (108).png");
	phase2[108] = new ObImage(L"phase2 (109).png");
	phase2[109] = new ObImage(L"phase2 (110).png");
	phase2[110] = new ObImage(L"phase2 (111).png");
	phase2[111] = new ObImage(L"phase2 (112).png");
	for (auto& _image : phase2)
	{
		_image->animInterval = 0.12f;
		_image->SetWorldPosY(-420.f);
		//_image->imageSize = Int2(1400, 800);
	}

	phase3 = *new vector<ObImage*>(112);
	phase3[0] = new ObImage(L"3phase (1).png");
	phase3[1] = new ObImage(L"3phase (2).png");
	phase3[2] = new ObImage(L"3phase (3).png");
	phase3[3] = new ObImage(L"3phase (4).png");
	phase3[4] = new ObImage(L"3phase (5).png");
	phase3[5] = new ObImage(L"3phase (6).png");
	phase3[6] = new ObImage(L"3phase (7).png");
	phase3[7] = new ObImage(L"3phase (8).png");
	phase3[8] = new ObImage(L"3phase (9).png");
	phase3[9] = new ObImage(L"3phase (10).png");
	phase3[10] = new ObImage(L"3phase (11).png");
	phase3[11] = new ObImage(L"3phase (12).png");
	phase3[12] = new ObImage(L"3phase (13).png");
	phase3[13] = new ObImage(L"3phase (14).png");
	phase3[14] = new ObImage(L"3phase (15).png");
	phase3[15] = new ObImage(L"3phase (16).png");
	phase3[16] = new ObImage(L"3phase (17).png");
	phase3[17] = new ObImage(L"3phase (18).png");
	phase3[18] = new ObImage(L"3phase (19).png");
	phase3[19] = new ObImage(L"3phase (20).png");
	phase3[20] = new ObImage(L"3phase (21).png");
	phase3[21] = new ObImage(L"3phase (22).png");
	phase3[22] = new ObImage(L"3phase (23).png");
	phase3[23] = new ObImage(L"3phase (24).png");
	phase3[24] = new ObImage(L"3phase (25).png");
	phase3[25] = new ObImage(L"3phase (26).png");
	phase3[26] = new ObImage(L"3phase (27).png");
	phase3[27] = new ObImage(L"3phase (28).png");
	phase3[28] = new ObImage(L"3phase (29).png");
	phase3[29] = new ObImage(L"3phase (30).png");
	phase3[30] = new ObImage(L"3phase (31).png");
	phase3[31] = new ObImage(L"3phase (32).png");
	phase3[32] = new ObImage(L"3phase (33).png");
	phase3[33] = new ObImage(L"3phase (34).png");
	phase3[34] = new ObImage(L"3phase (35).png");
	phase3[35] = new ObImage(L"3phase (36).png");
	phase3[36] = new ObImage(L"3phase (37).png");
	phase3[37] = new ObImage(L"3phase (38).png");
	phase3[38] = new ObImage(L"3phase (39).png");
	phase3[39] = new ObImage(L"3phase (40).png");
	phase3[40] = new ObImage(L"3phase (41).png");
	phase3[41] = new ObImage(L"3phase (42).png");
	phase3[42] = new ObImage(L"3phase (43).png");
	phase3[43] = new ObImage(L"3phase (44).png");
	phase3[44] = new ObImage(L"3phase (45).png");
	phase3[45] = new ObImage(L"3phase (46).png");
	phase3[46] = new ObImage(L"3phase (47).png");
	phase3[47] = new ObImage(L"3phase (48).png");
	phase3[48] = new ObImage(L"3phase (49).png");
	phase3[49] = new ObImage(L"3phase (50).png");
	phase3[50] = new ObImage(L"3phase (51).png");
	phase3[51] = new ObImage(L"3phase (52).png");
	phase3[52] = new ObImage(L"3phase (53).png");
	phase3[53] = new ObImage(L"3phase (54).png");
	phase3[54] = new ObImage(L"3phase (55).png");
	phase3[55] = new ObImage(L"3phase (56).png");
	phase3[56] = new ObImage(L"3phase (57).png");
	phase3[57] = new ObImage(L"3phase (58).png");
	phase3[58] = new ObImage(L"3phase (59).png");
	phase3[59] = new ObImage(L"3phase (60).png");
	phase3[60] = new ObImage(L"3phase (61).png");
	phase3[61] = new ObImage(L"3phase (62).png");
	phase3[62] = new ObImage(L"3phase (63).png");
	phase3[63] = new ObImage(L"3phase (64).png");
	phase3[64] = new ObImage(L"3phase (65).png");
	phase3[65] = new ObImage(L"3phase (66).png");
	phase3[66] = new ObImage(L"3phase (67).png");
	phase3[67] = new ObImage(L"3phase (68).png");
	phase3[68] = new ObImage(L"3phase (69).png");
	phase3[69] = new ObImage(L"3phase (70).png");
	phase3[70] = new ObImage(L"3phase (71).png");
	phase3[71] = new ObImage(L"3phase (72).png");
	phase3[72] = new ObImage(L"3phase (73).png");
	phase3[73] = new ObImage(L"3phase (74).png");
	phase3[74] = new ObImage(L"3phase (75).png");
	phase3[75] = new ObImage(L"3phase (76).png");
	phase3[76] = new ObImage(L"3phase (77).png");
	phase3[77] = new ObImage(L"3phase (78).png");
	phase3[78] = new ObImage(L"3phase (79).png");
	phase3[79] = new ObImage(L"3phase (80).png");
	phase3[80] = new ObImage(L"3phase (81).png");
	phase3[81] = new ObImage(L"3phase (82).png");
	phase3[82] = new ObImage(L"3phase (83).png");
	phase3[83] = new ObImage(L"3phase (84).png");
	phase3[84] = new ObImage(L"3phase (85).png");
	phase3[85] = new ObImage(L"3phase (86).png");
	phase3[86] = new ObImage(L"3phase (87).png");
	phase3[87] = new ObImage(L"3phase (88).png");
	phase3[88] = new ObImage(L"3phase (89).png");
	phase3[89] = new ObImage(L"3phase (90).png");
	phase3[90] = new ObImage(L"3phase (91).png");
	phase3[91] = new ObImage(L"3phase (92).png");
	phase3[92] = new ObImage(L"3phase (93).png");
	phase3[93] = new ObImage(L"3phase (94).png");
	phase3[94] = new ObImage(L"3phase (95).png");
	phase3[95] = new ObImage(L"3phase (96).png");
	phase3[96] = new ObImage(L"3phase (97).png");
	phase3[97] = new ObImage(L"3phase (98).png");
	phase3[98] = new ObImage(L"3phase (99).png");
	phase3[99] = new ObImage(L"3phase (100).png");
	phase3[100] = new ObImage(L"3phase (101).png");
	phase3[101] = new ObImage(L"3phase (102).png");
	phase3[102] = new ObImage(L"3phase (103).png");
	phase3[103] = new ObImage(L"3phase (104).png");
	phase3[104] = new ObImage(L"3phase (105).png");
	phase3[105] = new ObImage(L"3phase (106).png");
	phase3[106] = new ObImage(L"3phase (107).png");
	phase3[107] = new ObImage(L"3phase (108).png");
	phase3[108] = new ObImage(L"3phase (109).png");
	phase3[109] = new ObImage(L"3phase (110).png");
	phase3[110] = new ObImage(L"3phase (111).png");
	phase3[111] = new ObImage(L"3phase (112).png");
	for (auto& _image : phase3)
	{
		_image->animInterval = 0.06f;
		_image->SetWorldPosY(-170.f);
	}
	SetState(AnimState::Phase2);

	CompoObject::Update();
}

Phase2::~Phase2()
{
}

void Phase2::Update()
{
	CompoObject::Update();
}

void Phase2::LateUpdate()
{
}

void Phase2::Render()
{
	CompoObject::Render();
}

void Phase2::Show()
{
}

void Phase2::SetState(AnimState _animState)
{
	if (this->animState == _animState)
	{
		return;
	}

	this->animState = _animState;

	switch (this->animState)
	{
	case AnimState::Phase2:
		animation->SetAnimation(&this->phase2);
		animation->isLoop = false;
		break;
	case AnimState::Phase3:
		animation->SetAnimation(&this->phase3);
		animation->isLoop = false;
		break;
	default:
		break;
	}
}