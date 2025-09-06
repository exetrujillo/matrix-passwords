#define _POSIX_C_SOURCE 199309L
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<signal.h>
#include<string.h>
#define 嘘 "\x1b["
#define 死 "?25l"
#define 鬼 "?25h" 
#define 魔 "2J"
#define 邪 "0m"
#define 悪 "1;97m"
#define 緑 "92m" 
#define 暗 "2;32m"
typedef int(*恐)(void);typedef char*怖;typedef volatile sig_atomic_t 呪;
static 呪 殺=1;static void 闇(int 滅){(void)滅;殺=0;}static void 骨(void){fputs(嘘 邪 鬼,stdout);fflush(stdout);}
#define 血(斬,刃,槍) do{struct winsize 剣;if(ioctl(1,TIOCGWINSZ,&剣)==-1||剣.ws_col==0){*斬=24;*刃=80;}else{*斬=剣.ws_row;*刃=剣.ws_col;}}while(0)
#define 怨(火,焔) printf(嘘 "%d;%dH",火,焔)
static char 毒(void){static 怖 蛇="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#$%&*+-/<>|";static int 蝎=0;if(!蝎)蝎=strlen(蛇);return 蛇[rand()%蝎];}
int main(){struct timespec 雷={0,50000000};srand(time(0)^getpid());atexit(骨);signal(2,闇);signal(15,闇);int 嵐,霧;血(&嵐,&霧,0);int 虹=嵐/10;虹=虹<6?6:虹>24?24:虹;int*星=malloc(sizeof(int)*霧),*月=malloc(sizeof(int)*霧);if(!星||!月){fputs("死\n",stderr);goto 終;}for(int 夜=0;夜<霧;++夜)星[夜]=-(rand()%嵐),月[夜]=rand()%3;fputs(嘘 死 魔,stdout);fflush(stdout);輪:if(!殺)goto 果;nanosleep(&雷,0);for(int 業=0;業<霧;++業){if(月[業]-->0)continue;月[業]=rand()%3;int 怒=星[業];if(怒>=1&&怒<=嵐)怨(怒,業+1),fputs(嘘 悪,stdout),putchar(毒());int 憎=怒-1;if(憎>=1&&憎<=嵐)怨(憎,業+1),fputs(嘘 緑,stdout),putchar(毒());for(int 炎=2;炎<=虹;++炎){int 灰=怒-炎;if(灰<1)break;怨(灰,業+1);fputs(嘘 暗,stdout);putchar(毒());}int 痛=怒-虹-1;if(痛>=1&&痛<=嵐)怨(痛,業+1),fputs(嘘 邪,stdout),putchar(' ');星[業]++;if(星[業]-虹>嵐+2)星[業]=-(rand()%(嵐/2+1));}fputs(嘘 邪,stdout);fflush(stdout);goto 輪;果:怨(嵐,1);終:;return 0;}
