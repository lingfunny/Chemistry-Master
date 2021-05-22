#include <graphics.h>
#include <conio.h>
#include <vector>
#include <map>
#include <cstdio>
using namespace std;

#include "bars.h"
#include "items.h"
#include "Saver.h"

const SHOW Normal(RGB(240, 240, 240), BLACK, BLACK);
const SHOW Title_Style(WHITE, WHITE, BLACK);
const SHOW MenuButton_Style(WHITE, RGB(34, 172, 56), BLACK);

item I_Al, I_Al2O3, I_AlCl3, I_C, I_CO2, I_Fe, I_Fe2O3, I_FeCl2, I_FeCl3, I_FeO, I_H2, I_H2O, I_H2O2,
I_HCl, I_K2MnO4, I_KMnO4, I_MnO2, I_O2;

void GlobalEventsHandle(int id);
void Play(int Help_Flg = 1);
void Help();
void Menu();
void Init();

vector <Button> Newhand_Buttons;
Inventory inventory(Bar(513, 719, 0, 1079, RGB(230, 230, 230)));
Reaction reaction(Bar(50, 103, 0, 1079, RGB(230, 230, 230)));
map <string, Formula> Formula_Map;
map <string, item> Item_Map;

bool flg1 = true, flg2 = false;

int main() {
	// 初始化绘图窗口
	initgraph(1080, 720/*, SHOWCONSOLE*/);
	Init();
	Menu();
	closegraph();
}

void GlobalEventsHandle(int id) {
	printf("GlobalEventsHandle(%d)\n", id);
	switch (id) {
	case 1:Newhand_Buttons[0].SetText(string("I'd like to introduce the game to you")); Newhand_Buttons[0].show(Normal); Newhand_Buttons[0].Set_Events_ID(2); break;
	case 2:Newhand_Buttons[0].SetText(string("Now, there's some oxygen here")); Newhand_Buttons[0].show(Normal); Newhand_Buttons[0].Set_Events_ID(3); 
		inventory.AddItem("O2", 1); inventory.show(); break;
	case 3:Newhand_Buttons[0].SetText(string("Well, you may need some carbon")); Newhand_Buttons[0].show(Normal); Newhand_Buttons[0].Set_Events_ID(4);
		inventory.AddItem("C", 1); inventory.show(); break;
	case 4:Newhand_Buttons[0].SetText(string("好了不说English了，你可以试试将它们反应一下（拖到下面的这个框框里就好了）")); Newhand_Buttons[0].show(Normal); Newhand_Buttons[0].Set_Events_ID(-1);
		reaction.show(); break;
	case 5:Newhand_Buttons[0].SetText(string("Well done!你可以点击反应了！")); Newhand_Buttons[0].show(Normal); Newhand_Buttons[1].show(Normal); break;
	case 6:inventory.AddItem("CO2", 1); inventory.show(); cleardevice(); Newhand_Buttons[2].show(Normal); break;
	case 7:cleardevice(); inventory.items.clear(); reaction.reactants.clear(); flg1 = false; save(1); printf("flag1=%d, saved: %d\n", flg1, read()); break;
	case 8:save(read() == NULL ? 0 : read() + 1); break;
	default:break;
	}
}

void Init() {
	BeginBatchDraw();
	Block title(0, 0, 1080, 49, 45, "This is title");

	title.SetText("Loading... 5%");
	title.show(Title_Style);
	FlushBatchDraw();
	
	inventory.PgUp = Button(Block(inventory.right - 30, inventory.top, 30, "▲"));
	inventory.PgDn = Button(Block(inventory.right - 30, inventory.bottom - 30, 30, "▼"));

	title.SetText("Loading... 10%");
	title.show(Title_Style);
	FlushBatchDraw();

	I_Al = item("Al");
	I_Al2O3 = item("Al2O3");
	I_AlCl3 = item("AlCl3");
	I_C = item("C");
	I_CO2 = item("CO2");

	title.SetText("Loading... 30%");
	title.show(Title_Style);
	FlushBatchDraw();

	I_Fe = item("Fe");
	I_Fe2O3 = item("Fe2O3");
	I_FeCl2 = item("FeCl2");
	I_FeCl3 = item("FeCl3");
	I_FeO = item("FeO");

	title.SetText("Loading... 50%");
	title.show(Title_Style);
	FlushBatchDraw();

	I_H2 = item("H2");
	I_H2O = item("H2O");
	I_H2O2 = item("H2O2");
	I_HCl = item("HCl");
	I_K2MnO4 = item("K2MnO4");

	title.SetText("Loading... 70%");
	title.show(Title_Style);
	FlushBatchDraw();

	I_KMnO4 = item("KMnO4");
	I_MnO2 = item("MnO2");
	I_O2 = item("O2");

	title.SetText("Loading... 97%");
	title.show(Title_Style);
	FlushBatchDraw();

	Item_Map.insert(make_pair("Al", I_Al));
	Item_Map.insert(make_pair("Al2O3", I_Al2O3));
	Item_Map.insert(make_pair("AlCl3", I_AlCl3));
	Item_Map.insert(make_pair("C", I_C));
	Item_Map.insert(make_pair("CO2", I_CO2));
	Item_Map.insert(make_pair("Fe", I_Fe));
	Item_Map.insert(make_pair("Fe2O3", I_Fe2O3));
	Item_Map.insert(make_pair("FeCl2", I_FeCl2));
	Item_Map.insert(make_pair("FeCl3", I_FeCl3));
	Item_Map.insert(make_pair("FeO", I_FeO));
	Item_Map.insert(make_pair("H2", I_H2));
	Item_Map.insert(make_pair("H2O", I_H2O));
	Item_Map.insert(make_pair("H2O2", I_H2O2));
	Item_Map.insert(make_pair("HCl", I_HCl));
	Item_Map.insert(make_pair("K2MnO4", I_K2MnO4));
	Item_Map.insert(make_pair("KMnO4", I_KMnO4));
	Item_Map.insert(make_pair("MnO2", I_MnO2));
	Item_Map.insert(make_pair("O2", I_O2));

	if (read() == NULL) save(1);

	title.SetText("Loading... 100%");
	title.show(Title_Style);
	FlushBatchDraw();
	EndBatchDraw();
}

void Play(int Help_Flg) {
	BeginBatchDraw();
	cleardevice();
	printf("-----------Play()-----------\n\n");
	vector <item> goal;
	vector <Button> Buttons;
	Button title(Block(0, 0, 1080, 49, 45, "This is title"), 8);
	Button Restart(Block(0, 461, 50, "Restart", 1));
	Button Back(Block(Restart.x + Restart.length + 1, 461, 50, "Back", 1));
	int choice = -1, BTSIZE = 5;
	SHOW unusable(RGB(230, 230, 230), RGB(255, 0, 20), RGB(110, 110, 110)), usable(RGB(240, 240, 240), GREEN, BLACK);
	Button BT[10];
	BT[0] = Button(Block(0, 105, 50, "直接反应", 2), 100);
	BT[1] = Button(Block(BT[0].x + BT[0].length, 105, 50, "点燃", 2), 101);
	BT[2] = Button(Block(BT[1].x + BT[1].length, 105, 50, "通电", 2), 102);
	BT[3] = Button(Block(BT[2].x + BT[2].length, 105, 50, "加热", 2), 103);
	BT[4] = Button(Block(BT[3].x + BT[3].length, 105, 50, "高温", 2), 104);

	while(1) {
		inventory.items.clear();
		reaction.reactants.clear();
		Formula_Map.clear();
		goal.clear();
		for (int i = 0; i < 5; ++i) {
			BT[i].show(unusable);
			BT[i].showed = 0;
		}
		map<string, Formula>& x = Formula_Map;
		switch (read() * Help_Flg) {
		case 0:
			inventory.AddItem(I_H2.CgNum(2)); inventory.AddItem(I_O2.CgNum(1));
			x.insert(make_pair("2H2+O2", Formula("2H2O", 1)));
			x.insert(make_pair("2H2O", Formula("2H2+O2", 2)));
			goal.push_back(I_H2O2.CgNum(1));
			title.SetText("帮助");
			break;
		case 1:
			inventory.AddItem(I_H2.CgNum(2)); inventory.AddItem(I_O2.CgNum(1));
			goal.push_back(I_H2O.CgNum(2));
			x.insert(make_pair("2H2+O2", Formula("2H2O", 1)));
			x.insert(make_pair("2H2O", Formula("2H2+O2", 2)));
			title.SetText("Ⅰ：请制造两个水分子"); break;
		case 2:
			inventory.AddItem(I_KMnO4.CgNum(2)); inventory.AddItem(I_H2O2.CgNum(2));
			goal.push_back(I_O2.CgNum(3));
			x.insert(make_pair("2KMnO4", Formula("K2MnO4+MnO2+O2", 3)));
			x.insert(make_pair("2H2O2+MnO2", Formula("2H2O+O2+MnO2", 0)));
			x.insert(make_pair("2H2O", Formula("2H2+O2", 2)));
			title.SetText("Ⅱ：请制造三个氧气分子"); break;
		case 3:
			inventory.AddItem(I_Al.CgNum(2)); inventory.AddItem(I_HCl.CgNum(6)); inventory.AddItem(I_Fe2O3.CgNum(1));
			goal.push_back(I_FeCl2.CgNum(2));
			x.insert(make_pair("2Al+6HCl", Formula("2AlCl3+3H2", 0)));
			x.insert(make_pair("Fe2O3+6HCl", Formula("2FeCl3+3H2", 0)));
			x.insert(make_pair("2Al+Fe2O3", Formula("Al2O3+2Fe", 4)));
			x.insert(make_pair("Fe+2HCl", Formula("FeCl2+H2", 0)));
			title.SetText("Ⅲ：请制造两个氯化亚铁"); break;
		case 4:
			title.SetText("看什么锤子，你通关了"); title.show(); break;
		default:title.SetText("ERROR"); title.show(); break;
		}
		inventory.show();
		reaction.show();
		Restart.show(Normal);
		Back.show(Normal);
		title.show(Title_Style);
		MOUSEMSG m;
		while (1) {
			FlushBatchDraw();
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (inventory.InBar(m)) {
					if (inventory.PgUp.InBlock(m)) {
						choice = In_PgUp;
					}
					else if (inventory.PgDn.InBlock(m)) {
						choice = In_PgDn;
					}
					else {
						choice = (m.y - inventory.top) / 52 + inventory.begin;
						printf("CHOSE %d:%s\n", choice, inventory.items[choice].name.c_str());
					}
				}
				else if (reaction.InBar(m)) {
					choice = -1;
					for (int i = 0; i < reaction.items_Rect.size(); ++i)
						if (reaction.items_Rect[i].InRect(m))choice = i;
					if (choice != -1)choice |= REACTANTS_X;
				}
				else {
					choice = -1;
				}
				printf("choice = %d\n", choice);
			}
			if (m.uMsg == WM_LBUTTONUP) {
				if (Restart.InBlock(m)) break;
				if (Back.InBlock(m)) {
					cleardevice();
					EndBatchDraw();
					return;
				}
				if (inventory.PgDn.InBlock(m) && inventory.PgDn.showed && choice == In_PgDn) {
					inventory.PageDown();
					inventory.show();
				}
				if (inventory.PgUp.InBlock(m) && inventory.PgUp.showed && choice == In_PgUp) {
					inventory.PageUp();
					inventory.show();
				}
				for (int i = 0; i < BTSIZE; ++i)
					if (BT[i].InBlock(m) && BT[i].showed) {
						// 选择反应
						string tmp = Find_Formula(reaction.Formula(), Formula_Map).C_Formula;
						tmp += '+';
						while (tmp.size()) {
							// 添加生成物
							int num = 1;
							if (isdigit(tmp[0])) {
								num = max(num, tmp[0] - '0');
								tmp.erase(0, 1);
							}
							string name = tmp.substr(0, tmp.find('+'));
							printf("ITEM: num=%d, name=%s\n", num, name.c_str());
							tmp = tmp.substr(tmp.find('+'));
							tmp.erase(0, 1);
							inventory.AddItem(Item_Map[name].CgNum(num));
						}
						reaction.reactants.clear();
						inventory.show();
						reaction.show();
						bool win_flg = true;
						for (int i = 0; i < goal.size(); ++i) {
							printf("Goal: [%s]:%d\n", goal[i].name.c_str(), goal[i].num);
							bool HAVE_ITEM = false;
							for (int j = 0; j < inventory.items.size(); ++j) {
								if (goal[i].name == inventory.items[j].name &&
									goal[i].num <= inventory.items[j].num)
									HAVE_ITEM = true;
								printf("Inventory: [%s]:%d\n", inventory.items[j].name.c_str(), inventory.items[j].num);
							}
							if (!HAVE_ITEM) {
								win_flg = false;
								break;
							}
						}
						if (win_flg) {
							printf("Winned %d\n", read());
							title.SetText("恭喜通关 点我进入下一关");
							title.show(Normal);
							title.showed = 1;
						}
						BT[i].showed = 0;
						BT[i].show(unusable);
					}
				if (reaction.InBar(m) && choice != -1 && !(choice&REACTANTS_X)) {
					item& tmp = inventory.items[choice];
					int tnum = tmp.num;
					tmp.num = 1;
					reaction.AddItem(tmp);
					tmp.num = tnum - 1;
					for (vector<item>::iterator iter = inventory.items.begin(); iter != inventory.items.end(); )
						if (iter->num == 0) iter = inventory.items.erase(iter);
						else ++iter;
					reaction.show();
					inventory.show();
					//--- 加上反应物
					//判断是否能反应 ---
					Formula F = Find_Formula(reaction.Formula(), Formula_Map);
					if (F.condition != -1) {
						printf("F.condition = %d\n", F.condition);
						BT[F.condition].show(usable);
						BT[F.condition].showed = 1;
					}
					else {
						for (int i = 0; i < BTSIZE; ++i) {
							if (BT[i].showed == 1) {
								BT[i].show(unusable);
								BT[i].showed = 0;
							}
						}
					}
				}
				if (reaction.InBar(m) && choice != -1 && (choice & REACTANTS_X)) {
					reaction.reactants[choice ^ REACTANTS_X].num -= 1;
					item tmp = reaction.reactants[choice ^ REACTANTS_X];
					tmp.num = 1;
					inventory.AddItem(tmp);
					for (vector<item>::iterator iter = reaction.reactants.begin(); iter != reaction.reactants.end();)
						if (iter->num == 0) iter = reaction.reactants.erase(iter);
						else ++iter;
					reaction.show();
					inventory.show();
					Formula F = Find_Formula(reaction.Formula(), Formula_Map);
					if (F.condition != -1) {
						printf("F.condition = %d\n", F.condition);
						BT[F.condition].show(usable);
						BT[F.condition].showed = 1;
					}
				}
				if (title.showed && title.InBlock(m)) {
					title.showed = 0;
					GlobalEventsHandle(title.Get_Events_ID());
					break;
				}
			}
		}
	}
	EndBatchDraw();
}

void Menu() {
	Button BStart(Block(420, 220, 240, 100, 80, "Start", 3));
	Button BHelp(Block(420, 330, 240, 100, 80, "Help", 3));
	Button BQuit(Block(420, 440, 240, 100, 80, "Quit", 3));
	BeginBatchDraw();
	cleardevice();
	MOUSEMSG m;
	int choice = -1;
	while (1) {
		BStart.show(MenuButton_Style);
		BHelp.show(MenuButton_Style);
		BQuit.show(MenuButton_Style);
		FlushBatchDraw();
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			choice = -1;
			if (BStart.InBlock(m))choice = 1;
			if (BHelp.InBlock(m))choice = 2;
			if (BQuit.InBlock(m))choice = 3;
		}
		if (m.uMsg == WM_LBUTTONUP && choice != -1) {
			if (choice == 1 && BStart.InBlock(m))Play();
			else if (choice == 2 && BHelp.InBlock(m))Help();
			else if (choice == 3 && BQuit.InBlock(m))break;
		}
	}
	EndBatchDraw();
}

void Help(){
	Play(0);
}