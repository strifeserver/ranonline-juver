#pragma once

#include "../Lib_Engine/GUInterface/UITextUtil.h"

//	NOTE
//		아래의 이름은 'color_chart.html'을 따릅니다.
//		/=document/color_chart.html

//	CAUTION
//		알파값은 바꾸지 마십시오.

namespace	NS_UITEXTCOLOR
{
	//	기본색 정의
	//
	const DWORD DARKLBUE		= D3DCOLOR_ARGB(0xFF,0x87,0xCE,0xFF);
	const DWORD BRIGHTGREEN		= D3DCOLOR_ARGB(0xFF,0x00,0xFF,0x00);
	const DWORD WHITESMOKE		= D3DCOLOR_ARGB(0xFF,0xF5,0xF5,0xF5);
	const DWORD WHITE			= D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0xFF);
	const DWORD DARKGRAY		= D3DCOLOR_ARGB(0xFF,0xA9,0xA9,0xA9);
	const DWORD	LIGHTSKYBLUE	= D3DCOLOR_ARGB(0xFF,0x87,0xCE,0xFA);
	const DWORD	PALEGREEN		= D3DCOLOR_ARGB(0xFF,0x98,0xFB,0x98);	
	const DWORD dwRandomAbility	= D3DCOLOR_RGBA(118,238,198,255);
	const DWORD RED				= D3DCOLOR_ARGB(0xFF,0xFF,0x00,0x00);
	const DWORD GOLD			= D3DCOLOR_ARGB(0xFF,0xFF,0xD7,0x00);
	const DWORD PALEGOLDENROD	= D3DCOLOR_ARGB(0xFF,0xEE,0xE8,0xAA);	
	const DWORD DODGERBLUE		= D3DCOLOR_ARGB(0xFF,0x1E,0x90,0xFF);
	const DWORD DARKTURQUOISE	= D3DCOLOR_ARGB(0xFF,0x00,0xCE,0xD1);
	const DWORD TOMATO			= D3DCOLOR_ARGB(0xFF,0xFF,0x63,0x47);
	const DWORD AQUA			= D3DCOLOR_ARGB(0xFF,0x00,0xFF,0xFF);
	const DWORD ORANGE			= D3DCOLOR_ARGB(0xFF,0xFF,0xA5,0x00);
	const DWORD PALETURQUOISE	= D3DCOLOR_ARGB(0xFF,0xAF,0xEE,0xEE);
	const DWORD SILVER			= D3DCOLOR_ARGB(0xFF,0xC0,0xC0,0xC0);
	const DWORD LIGHTGREY		= D3DCOLOR_ARGB(0xFF,0xD3,0xD3,0xD3);	
	const DWORD GREENYELLOW		= D3DCOLOR_ARGB(0xFF,0xAD,0xFF,0x2F);
	const DWORD ORNAGERED		= D3DCOLOR_ARGB(0xFF,0xFF,0x45,0x00);
	const DWORD HONEYDEW		= D3DCOLOR_ARGB(0xFF,0xF0,0xFF,0xF0);
	const DWORD PERU			= D3DCOLOR_ARGB(0xFF,0xCD,0x85,0x3F);
	const DWORD BURLYWOOD		= D3DCOLOR_ARGB(0xFF,0xDE,0xB8,0x87);
	const DWORD GOLDENROD		= D3DCOLOR_ARGB(0xFF,0xDA,0xA5,0x20);
	const DWORD DARKORANGE		= D3DCOLOR_ARGB(0xFF,0xFF,0x8C,0x00);	
	const DWORD LIGHTCYAN		= D3DCOLOR_ARGB(0xFF,0xE0,0xFF,0xFF);
	const DWORD IVORY			= D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0xF0);
	const DWORD YELLOW			= D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0x00);
	const DWORD CHARTREUSE		= D3DCOLOR_ARGB(0xFF,0x7F,0xFF,0x00);
	const DWORD THISTLE			= D3DCOLOR_ARGB(0xFF,0xD8,0xBF,0xD8);	
	const DWORD LIGHTSALMON		= D3DCOLOR_ARGB(0xFF,0xFF,0xA0,0x7A);
	const DWORD TURQUOISE		= D3DCOLOR_ARGB(0xFF,0x40,0xE0,0xD0);
	const DWORD VIOLET			= D3DCOLOR_ARGB(0xFF,0xEE,0x82,0xEE);
	const DWORD AQUAMARINE		= D3DCOLOR_ARGB(0xFF,0x7F,0xFF,0xD4);
	const DWORD FORESTGREEN		= D3DCOLOR_ARGB(0xFF,0x22,0x8B,0x22);
	const DWORD HOTPINK			= D3DCOLOR_ARGB(0xFF,0xFF,0x69,0xB4);
	const DWORD MAROON			= D3DCOLOR_ARGB(0xFF,0x80,0x00,0x00);
	const DWORD NAVY			= D3DCOLOR_ARGB(0xFF,0x00,0x00,0x80); // 짙은검은빛을띤남빛
	const DWORD BLACK			= D3DCOLOR_ARGB(0xFF,0x00,0x00,0x00);

	//wow colors
	const DWORD GREEN_WOW		= D3DCOLOR_ARGB(0xFF,0x00,0xFF,0x00);
	const DWORD BLUE_WOW		= D3DCOLOR_ARGB(0xFF,0x00,0x99,0xFF);
	const DWORD PURPLE_WOW		= D3DCOLOR_ARGB(0xFF,0xFF,0x65,0xFF);
	const DWORD ORANGE_WOW		= D3DCOLOR_ARGB(0xFF,0xFF,0x99,0x00);
	const DWORD GOLD_WOW		= D3DCOLOR_ARGB(0xFF,0xFF,0xCC,0x00);
	
	// clubBattle 사용할려고 추가 ( 색상값 조금씩 틀림 ) 
	const DWORD AQUABLUE		= D3DCOLOR_ARGB(0xFF,0x00,0x26,0xFF);
	const DWORD DARKVIOLET		= D3DCOLOR_ARGB(0xFF,0xB2,0x00,0xFF);
	const DWORD FUCHSIA			= D3DCOLOR_ARGB(0xFF,0xFF,0x00,0xDC);
	const DWORD PURPLE			= D3DCOLOR_ARGB(0xFF,0x7F,0x00,0x6E);
	const DWORD LIGHTYELLOW		= D3DCOLOR_ARGB(0xFF,0xFF,0xE9,0x7F);


	//	사용처
	const DWORD ENABLE			= LIGHTGREY;	
	const DWORD DISABLE			= RED;

	const DWORD DEFAULT			= ENABLE;
	const DWORD DIALOGUE_MOUSEOVER = GOLD;
	const DWORD ITEMMONEY		= GOLD;
	const DWORD SELF			= PALEGOLDENROD;	
	const DWORD SYS_ERROR		= RED;
	const DWORD PARTY			= DARKTURQUOISE;
	const DWORD GUILD			= TOMATO;
	const DWORD PRIVATE			= GOLD;	
	const DWORD	PLUSOPTION		= PALEGOLDENROD;
	const DWORD PARTYNAME		= PLUSOPTION;
	const DWORD IDCOLOR			= LIGHTSKYBLUE;
	const DWORD ADMIN_COLOR		= DISABLE;	
	const DWORD NEGATIVE		= RED;
	const DWORD FRIEND_OFF		= MAROON;

	const DWORD MAX_CLUB_BATTLE_COLOR = 8;
	const DWORD CLUB_BATTLE_COLOR[MAX_CLUB_BATTLE_COLOR] = { AQUA, DODGERBLUE, AQUABLUE, DARKVIOLET,
		FUCHSIA, PURPLE, LIGHTYELLOW, GOLD };

};

namespace	NS_UITEXTCONTROL
{
	using namespace NS_UITEXTUTIL;

	DWORD	GetEvaluateColor ( BOOL bValue );
};

/*
778899 lightslategray 밝은푸른빛회색 
696969 dimgray 칙칙한회색 
808080 gray 회색 
a9a9a9 darkgray 어두운회색 
c0c0c0 silver 은색 
d3d3d3 lightgrey 밝은회색 
dcdcdc gainsboro 
ffffff white 백색 
fff5ee seashell 바다조가비 
fffafa snow 설백 
f8f8ff ghostwhite 허깨비백색 
fffaf0 floralwhite 꽃의백색 
f5f5f5 whitesmoke 백색연기 
f0f8ff aliceblue 엷은잿빛바탕에푸른빛 
f0ffff azure 하늘색 
fdf5e6 oldlace 낡은끈 
f5fffa mintcream 박하크림 
ffefd5 papayawhip 열대아메리카산과수매질 
ffdab9 peachpuff 복숭아빛불기 
faf0e6 linen 리넨 
eee8aa palegoldenrod 옅은국화과의다년초 
ffe4e1 mistyrose 짙은장미빛 
ffe4b5 moccasin 사슴가죽의구두 
ffdead navajowhite 나바호족백색 
d2b48c tan 볕에탄빛깔 
f5deb3 wheat 밀 
fafad2 lightgoldenrodyellow 밝은국화과다년초노랑 
ffffe0 lightyellow 밝은노랑 
fff8dc cornsilk 옥수수명주실 
faebd7 antiquewhite 옛날의백색 
f5f5dc beige 엷은갈색 
fffacd lemonchiffon 레몬빛가볍고얇은직물 
fffff0 ivory 상앗빛 
f0e68c khaki 누른빛에엷은다색이섞인빛깔 
e6e6fa lavender 연한자주색 
fff0f5 lavenderblush 연한자주빛붉기 
ffe4c4 bisque 분홍빛이도는검은빛을띤누른빛 
ffebcd blanchedalmond 희어진엷은황갈색 
deb887 burlywood 튼튼한목재 
cd853f peru 남미서부의공화국 
00ced1 darkturquoise 어두운푸른빛녹색 
00bfff deepskyblue 짙은하늘파랑 
7fffd4 aquamarine 엷은푸른빛녹색 
1e90ff dodgerblue옥수수빵파랑 
00ffff cyan 푸른정도 
f0fff0 honeydew 식물의잎에서나는단물 
87cefa lightskyblue 밝은하늘파랑 
afeeee paleturquoise 옅은푸른빛녹색 
e0ffff lightcyan 밝은푸른정도 
add8e6 lightblue 밝은파랑 
b0c4de lightsteelblue 밝은철강빛파랑 
40e0d0 turquoise 푸른빛녹색 
48d1cc mediumturquoise 중간의푸른빛녹색 
00ffff aqua 엷은푸른빛녹색 
7b68ee mediumslateblue 중푸른빛회색파랑 
191970 midnightblue 깜깜한파랑 
6495ed cornflowerblue 옥수수꽃파랑 
0000cd mediumblue 중간의파랑 
6a5acd slateblue 푸른빛회색파랑 
4682b4 steelblue 철강빛파랑 
0000ff blue 파랑 
483d8b darkslateblue 어두운푸른빛회색파랑 
5f9ea0 cadetblue 이하의파랑 
87ceeb skyblue 하늘파랑 
4169e1 royalblue 황실의파랑 
b0e0e6 powderblue 가루파랑 
000080 navy 짙은검은빛을띤남빛 
00008b darkblue 어두운파랑 
8a2be2 blueviolet 파란제비꽃색 
8b008b darkmagenta 어두운짙은분홍색 
9932cc darkorchid 어두운연보라색 
9400d3 darkviolet 어두운제비꽃색 
ff00ff magenta 짙은분홍색 
ff00ff fuchsia 붉은빛깔이나는자줏빛 
c71585 mediumvioletred 중제비꽃빨강 
ba55d3 mediumorchid 중간의연보라색 
9370db mediumpurple 중간의자줏빛 
dc143c crimson 짙게붉은색깔 
ff1493 deeppink 짙은연분홍색 
ffb6c1 lightpink 밝은연분홍색 
ff69b4 hotpink 강렬한연분홍색 
ffc0cb pink 연분홍색 
dda0dd plum 짙은 보라색 
800080 purple 자줏빛 
ee82ee violet 제비꽃색 
d8bfd8 thistle 엉겅퀴 
da70d6 orchid 연보라색 
4b0082 indigo 남색 
a52a2a brown 갈색 
e9967a darksalmon 어두운주황색 
f08080 lightcoral 밝은산호빛 
cd5c5c indianred 인디언빨강 
ffa07a lightsalmon 밝은주황색 
db7093 palevioletred 옅은제비꽃빨강 
f4a460 sandybrown 엷은갈색 
fa8072 salmon 주황색 
ff6347 tomato 토마토색 
ff4500 ornagered 
ff0000 red 빨강 
800000 maroon 붉은빛을띤갈색 
8b0000 darkred 어두운빨강 
b22222 firebrick 내화 
d2691e chocolate 갈색 
8b4513 saddlebrown 안장갈색 
a0522d sienna 붉은빛을띤갈색 
bc8f8f rosybrown 장미빛갈색 
ff7f50 coral 산호빛 
ff8c00 darkorange 어두운붉은빛을띤누른색 
ffa500 orange 붉은빛을띤누른색 
b8860b darkgoldenrod 어둔운국화과의다년초 
ffd700 gold 금빛 
ffff00 yellow 노랑 
7fff00 chartreuse 연두색 
7cfc00 lawngreen 잔디녹색 
00ff00 lime 열대산의레몬비슷한과일 
32cd32 limegreen 라임녹색 
00ff7f springgreen 봄녹색 
3cb371 mediumseagreen 중간의바다녹색 
adff2f greenyellow 녹색의노랑 
8fbc8f darkseagreen 어두운바다녹색 
90ee90 lightgreen 밝은녹색 
98fb98 palegreen 옅은녹색 
9acd32 yello: wgree: n 
2e8b57 seagreen 바다녹색 
00fa9a mediumspringgreen 중봄녹색 
20b2aa lightseagreen 밝은바다녹색 
66cdaa mediumaquamarine 중엷은청록색 
228b22 forestgreen 숲녹색 
008b8b darkcyan 어두운푸른정도 
008080 teal 암록색을띤청색 
006400 darkgreen 어두운녹색 
556b2f darkolivegreen 어두운올리브녹색 
008000 green 녹색 
808000 olive 물푸레나뭇과의상록교목 
6b8e23 olivedrab 올리브엷은갈색 
bdb76b darkkhaki 어두운누른빛에엷은다색 
daa520 goldenrod 국화과의다년초 
*/







