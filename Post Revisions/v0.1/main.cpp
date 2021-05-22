#include <graphics.h>
#include <conio.h>
#include <vector>
#include <map>
using namespace std;

#include "bars.h"
#include "items.h"
#include "Saver.h"

void GlobalEventsHandle(int id);
void Play();
void Init();

vector <Button> Newhand_Buttons;
SHOW Normal(RGB(240, 240, 240), WHITE, BLACK);
Inventory inventory(Bar(720-52*4, 720, 0, 1080, RGB(230, 230, 230)));
Reaction reaction(Bar(50, 100, 0, 1080, RGB(230, 230, 230)));
map <string, Formula> Formula_Map;

bool flg1 = true, flg2 = false;

int main() {
	// 初始化绘图窗口
	initgraph(1080, 720, SHOWCONSOLE);
	Init();
	while (read() == NULL) {
		MOUSEMSG m;
		Button x(Block(0, 0, 1080, 50, 20, string("Hello! Chemistry Master!(You can click me to move on)")), 1);
		x.show(Normal);
		Newhand_Buttons.push_back(x);
		Newhand_Buttons.push_back(Button(Block(0, 100, 50, string("点燃"), 1), 6));
		Newhand_Buttons.push_back(Button(Block(360, 310, 50, string("下一步"), 2), 7));
		int chose_chemicals = -1;
		while (flg1) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONUP) {
				for (int i = 0; i < Newhand_Buttons.size(); ++i) {
					Button& B = Newhand_Buttons[i];
					if (B.x <= m.x && m.x < B.x + B.length && B.y <= m.y && m.y < B.y + B.wide)
						GlobalEventsHandle(B.Get_Events_ID());
				}
				if (reaction.left <= m.x && m.x <= reaction.right
					&& reaction.top <= m.y && m.y <= reaction.bottom
					&& chose_chemicals != -1) {
					item x = inventory.items[chose_chemicals];
					x.num = 1;
					inventory.items[chose_chemicals].num -= 1;
					reaction.AddItem(x);
					reaction.show();
					inventory.show();
					flg2 = true;
					for (int i = 0; i < inventory.items.size(); ++i)
						if (inventory.items[i].num != 0) flg2 = false;
					if (flg2) GlobalEventsHandle(5);
				}
			}
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (inventory.left <= m.x && m.x <= inventory.right
					&& inventory.top <= m.y && m.y <= inventory.bottom) {
					int choice = (m.y - inventory.top) / 52;
					printf("choice = %d\n", chose_chemicals = choice);
					if (inventory.items[choice].num < 1) chose_chemicals = -1;
				}
				else {
					chose_chemicals = -1;
				}
			}
		}
	}
	Play();
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
	case 6:inventory.AddItem("CO2", 1); inventory.show(); Newhand_Buttons[2].show(Normal); break;
	case 7:cleardevice(); inventory.items.clear(); reaction.reactants.clear(); flg1 = false; save(1); printf("flag1=%d, saved: %d\n", flg1, read()); break;
	case 8:save(read() + 1); break;
	default:break;
	}
}

void Init() {
	Formula_Map_Init(Formula_Map);
}

void Play() {
	printf("-----------Play()-----------\n\n");
	vector <item> goal;
	vector <Button> Buttons;
	Button title(Block(0, 0, 1080, 50, 50, string("This is title")), 8);
	int choice = -1, BTSIZE = 5;
	SHOW unusable(RGB(230, 230, 230), WHITE, RGB(110, 110, 110)), usable(RGB(240, 240, 240), RGB(255,0,0), BLACK);
	Button BT[10];
	BT[0] = Button(Block(0, 100, 50, "直接反应", 1), 100);
	BT[1] = Button(Block(BT[0].x + BT[0].length, 100, 50, "点燃", 1), 101);
	BT[2] = Button(Block(BT[1].x + BT[1].length, 100, 50, "通电", 1), 102);
	BT[3] = Button(Block(BT[2].x + BT[2].length, 100, 50, "加热", 1), 103);
	BT[4] = Button(Block(BT[3].x + BT[3].length, 100, 50, "高温", 1), 104);

	while(1) {
		inventory.items.clear();
		reaction.reactants.clear();
		goal.clear();
		for (int i = 0; i < 5; ++i) {
			BT[i].show(unusable);
			BT[i].showed = 0;
		}
		switch (read()) {
		case 1:
			inventory.AddItem("H2", 2); inventory.AddItem("O2", 1);
			goal.push_back(item("H2O", 2));
			title.SetText("Ⅰ：请制造两个水分子"); break;
		case 2:
			inventory.AddItem("KMnO4", 2); inventory.AddItem("H2O2", 2);
			goal.push_back(item("O2", 2));
			title.SetText("Ⅱ：请制造两个氧气分子"); break;
		case 3:
			title.SetText("看什么锤子，你通关了"); title.show(); break;
		default:title.SetText("ERROR"); title.show(); break;
		}
		inventory.show();
		reaction.show();
		title.show(Normal);
		MOUSEMSG m;
		while (1) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (inventory.InBar(m)) {
					choice = (m.y - inventory.top) / 52;
					printf("CHOSE %d:%s\n", choice, inventory.items[choice].name.c_str());
				}
				else {
					choice = -1;
				}
			}
			if (m.uMsg == WM_LBUTTONUP) {
				for (int i = 0; i < BTSIZE; ++i)
					if (BT[i].InBlock(m) && BT[i].showed) {
						// 选择反应
						string tmp = Find_Formula(reaction.Formula(), Formula_Map).C_Formula;
						tmp += '+';
						while (tmp.size()) {
							// 添加反应物
							item new_item;
							if (isdigit(tmp[0])) {
								new_item.num = tmp[0] - '0';
								tmp.erase(0, 1);
							}
							new_item.name = tmp.substr(0, tmp.find('+'));
							new_item.num = max(1, new_item.num);
							printf("ITEM: num=%d, name=%s\n", new_item.num, new_item.name.c_str());
							tmp = tmp.substr(tmp.find('+'));
							tmp.erase(0, 1);
							inventory.AddItem(new_item);
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
							title.SetText("You Win! Click me to go to the next level!");
							title.show(Normal);
							title.showed = 1;
						}
						BT[i].showed = 0;
						BT[i].show(unusable);
					}
				if (reaction.InBar(m) && choice != -1) {
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
				}
				if (title.showed && title.InBlock(m)) {
					title.showed = 0;
					GlobalEventsHandle(title.Get_Events_ID());
					cleardevice();
					break;
				}
			}
		}
	}
}