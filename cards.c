#include <stdio.h>
#include <stdlib.h>
//表示扑克牌四种花色，黑桃(Spade)、红桃(Heart)、方块(Diamond)、梅花(Club)
const char *s_suits_ascii[] = { "S", "H", "D", "C" };
/**
扑克牌中的数字
WHAT 表示数字为0时,如果大于>13的话,表示溢出(overflow)
**/
const char *s_nums[] = { "WHAT",
	"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
	"OVERFLOW"
};
/**
    定义一个扑克牌结构体
    suit：花色
    number:扑克牌的数字
    _s:随机值
**/
typedef struct { int suit, number, _s; } card_t, *card;
/**
    定义一副扑克牌的结构体
    n:表示一副扑克牌的数量
    cards:上面的定义的每张扑克牌的结构体类型
**/
typedef struct { int n; card_t cards[52]; } deck_t, *deck;
//显示扑克牌的花色和数字
void show_card(card c)
{
    //直接打印即可
    printf(" %s%s", s_suits_ascii[c->suit], s_nums[c->number]);
}
//创建一副扑克牌实例
deck new_deck()
{
    //定义三个循环变量
	int i, j, k;
	//创建一个deck的实例对象指针，并申请空间
	deck d = malloc(sizeof(deck_t));
	//给成员变量赋值,一副牌有52张(不包括大小王)
	d->n = 52;
	//i:花色 j:数字 k:扑克牌的数量
	for (i = k = 0; i < 4; i++)
		for (j = 1; j <= 13; j++, k++) {
            //分别给扑克牌的花色和数字进行赋值
			d->cards[k].suit = i;
			d->cards[k].number = j;
		}
    //返回一个deck结构体指针
	return d;
}
//显示一副扑克牌(包括花色和数字)
void show_deck(deck d)
{
    //定义循环变量i
	int i;
	//打印d这幅扑克牌的数量
	printf("%d cards:", d->n);
	//循环 52 次
	for (i = 0; i < d->n; i++)
        //对于每张扑克牌,打印其花色和数字
		show_card(d->cards + i);
    //输出换行
	printf("\n");
}
//对纸牌进行排序,给定一个排序的规则
int cmp_card(const void *a, const void *b)
{
    //x,y取得卡片a和b的随机值
	int x = ((card)a)->_s, y = ((card)b)->_s;
	//对随机值进行排序
	return x < y ? -1 : x > y;
}
//从d这幅扑克牌中发牌
card deal_card(deck d)
{
    //如果没有牌了,直接返回0
	if (!d->n) return 0;
	//否则返回当前的cards,并且d这副牌中数量减1
	return d->cards + --d->n;
}
//对d这幅扑克牌进行随机洗牌
void shuffle_deck(deck d)
{
	int i;
	//对于d这副牌中的每个卡片,给其成员变量_s赋一个随机值
	for (i = 0; i < d->n; i++)
		d->cards[i]._s = rand();
    //对d进行排序
	qsort(d->cards, d->n, sizeof(card_t), cmp_card);
}
int main()
{
    //循环变量i,j 
	int i, j;
	//创建一副扑克牌实例
	deck d = new_deck();
	printf("New deck, ");
	//打印当前的扑克牌
	show_deck(d);
	printf("\nShuffle and deal to three players:\n");
    //进行随机洗牌
	shuffle_deck(d);
	//三个玩家,每个玩家发5张牌
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 5; j++)
            //输出发到玩家手中的牌
			show_card(deal_card(d));
        //输出换行
		printf("\n");
	}
	//输出剩余的牌
	printf("Left in deck "); show_deck(d);
	return 0;
}