#include "stdafx.h"

Die1::Die1()
{
	die1Img = *new vector<ObImage*>(64);
	die1Img[0] = new ObImage(L"will_die (1).png");
	die1Img[1] = new ObImage(L"will_die (2).png");
	die1Img[2] = new ObImage(L"will_die (3).png");
	die1Img[3] = new ObImage(L"will_die (4).png");
	die1Img[4] = new ObImage(L"will_die (5).png");
	die1Img[5] = new ObImage(L"will_die (6).png");
	die1Img[6] = new ObImage(L"will_die (7).png");
	die1Img[7] = new ObImage(L"will_die (8).png");
	die1Img[8] = new ObImage(L"will_die (9).png");
	die1Img[9] = new ObImage(L"will_die (10).png");
	die1Img[10] = new ObImage(L"will_die (11).png");
	die1Img[11] = new ObImage(L"will_die (12).png");
	die1Img[12] = new ObImage(L"will_die (13).png");
	die1Img[13] = new ObImage(L"will_die (14).png");
	die1Img[14] = new ObImage(L"will_die (15).png");
	die1Img[15] = new ObImage(L"will_die (16).png");
	die1Img[16] = new ObImage(L"will_die (17).png");
	die1Img[17] = new ObImage(L"will_die (18).png");
	die1Img[18] = new ObImage(L"will_die (19).png");
	die1Img[19] = new ObImage(L"will_die (20).png");
	die1Img[20] = new ObImage(L"will_die (21).png");
	die1Img[21] = new ObImage(L"will_die (22).png");
	die1Img[22] = new ObImage(L"will_die (23).png");
	die1Img[23] = new ObImage(L"will_die (24).png");
	die1Img[24] = new ObImage(L"will_die (25).png");
	die1Img[25] = new ObImage(L"will_die (26).png");
	die1Img[26] = new ObImage(L"will_die (27).png");
	die1Img[27] = new ObImage(L"will_die (28).png");
	die1Img[28] = new ObImage(L"will_die (29).png");
	die1Img[29] = new ObImage(L"will_die (30).png");
	die1Img[30] = new ObImage(L"will_die (31).png");
	die1Img[31] = new ObImage(L"will_die (32).png");
	die1Img[32] = new ObImage(L"will_die (33).png");
	die1Img[33] = new ObImage(L"will_die (34).png");
	die1Img[34] = new ObImage(L"will_die (35).png");
	die1Img[35] = new ObImage(L"will_die (36).png");
	die1Img[36] = new ObImage(L"will_die (37).png");
	die1Img[37] = new ObImage(L"will_die (38).png");
	die1Img[38] = new ObImage(L"will_die (39).png");
	die1Img[39] = new ObImage(L"will_die (40).png");
	die1Img[40] = new ObImage(L"will_die (41).png");
	die1Img[41] = new ObImage(L"will_die (42).png");
	die1Img[42] = new ObImage(L"will_die (43).png");
	die1Img[43] = new ObImage(L"will_die (44).png");
	die1Img[44] = new ObImage(L"will_die (45).png");
	die1Img[45] = new ObImage(L"will_die (46).png");
	die1Img[46] = new ObImage(L"will_die (47).png");
	die1Img[47] = new ObImage(L"will_die (48).png");
	die1Img[48] = new ObImage(L"will_die (49).png");
	die1Img[49] = new ObImage(L"will_die (50).png");
	die1Img[50] = new ObImage(L"will_die (51).png");
	die1Img[51] = new ObImage(L"will_die (52).png");
	die1Img[52] = new ObImage(L"will_die (53).png");
	die1Img[53] = new ObImage(L"will_die (54).png");
	die1Img[54] = new ObImage(L"will_die (55).png");
	die1Img[55] = new ObImage(L"will_die (56).png");
	die1Img[56] = new ObImage(L"will_die (57).png");
	die1Img[57] = new ObImage(L"will_die (58).png");
	die1Img[58] = new ObImage(L"will_die (59).png");
	die1Img[59] = new ObImage(L"will_die (60).png");
	die1Img[60] = new ObImage(L"will_die (61).png");
	die1Img[61] = new ObImage(L"will_die (62).png");
	die1Img[62] = new ObImage(L"will_die (63).png");
	die1Img[63] = new ObImage(L"will_die (64).png");

	for (auto& _image : die1Img)
	{
		_image->animInterval = 0.27f;
		_image->SetWorldPos(Vector2(-1.0f, 36.0f));
	}
}

Die1::~Die1()
{
}

void Die1::Update()
{
}

void Die1::LateUpdate()
{
}

void Die1::Render()
{
}
