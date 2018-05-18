#include <iostream>
#include <fstream>
#include <math.h>


using namespace std;//test
//add something else to learn branch


#define WHITE '1'
#define BLACK '0'
#define top_line 10

int imgnew[60][80]; // 保存处理过后的赛道信息，写入对应的*D.txt

/*void initimg();*/
void imgdeal();
void judgecircuit_cross();
int slope(unsigned char img[][80], int temp[100]);
void crossdeal();
void judgeFLAG();
void judgebarrier();
void crossdeal();
void barrierdeal_L();

int FLAG = 0;

unsigned char img[60][80];
int L_edge[60] = {-1}, R_edge[60] = {-1}, Mid_Line[60];

void Road();
int Edge_Find_1(int, char, int);
int Next_Point(int, int, char);
void Correct();
int main()
{
	for (int i = 0; i < 60; i++)
	{
		L_edge[i] = -1;
		R_edge[i] = -1;
	}
	ifstream infile("019C.txt");
	printf("%s\n", infile.is_open() ? "open success" : "open fail");
	for (int i = 0; i < 60; i++)
		for (int j = 0; j < 80; j++)
			infile >> img[i][j];
	infile.close();
	for (int i = 0; i < 60; i++)
	{
		cout << endl;
		for (int j = 0; j < 80; j++)
			cout << img[i][j] << "_";
	}

	Road();
	imgdeal();
	judgecircuit_cross();
	judgebarrier();
	judgeFLAG();

	for (int line = top_line; line < 60; line++)
	{
		for (int counter = 0; counter < 80; counter++)
		{
			if (counter == 40)
			{
				cout << "|";
			}
			else if (counter == L_edge[line])
			{
				cout << " L";
			}
			else if (counter == Mid_Line[line])
			{
				cout << "M";
			}
			else if (counter == R_edge[line])
			{
				cout << " R";
			}
			else
				cout << "  ";
			if (counter == 79)
				cout << endl;
		}
	}
	for (int line = top_line; line < 60; line++)
	{
		cout << L_edge[line] << "   " << R_edge[line] << endl;
	}

	printf("over\n");

	return 0;
}

//边沿搜索判断赛道
//环岛利用陀螺仪进行判断
//cur_is_coming为判断环岛的flag，in_the_cur为判断十字路口和出环岛的flag（可不要，因为用陀螺仪转300~350度）
void Road()
{
	/*
    功能：寻找图像的边界，储存在 L_edge[60],R_edge[60],Mid_Line[60]三个数组中；

    */
	int row = 60 - 1; //top_line是最高的有效行
	int temp_col;
	while (row > top_line)
	{
		temp_col = Edge_Find_1(row, 'L', 40 - 1);
		if (temp_col == -1)
		{ //如果没边界，储存边界值为-1，row减一行
			L_edge[row] = -1;
			row--;
			continue; //没边界，继续向上查找
		}
		else
		{
			L_edge[row] = temp_col;
			int temp_row = Next_Point(row, temp_col, 'L'); //渡过空白层，以此为起点开始查找边界
			if (temp_row != 0)
			{
				row = temp_row;
				continue;
			} //遇到断层，当作空白起始区，再次查找
			else
				break;
		}
	}
	//右边界同
	row = 60 - 1;
	while (row > top_line)
	{
		temp_col = Edge_Find_1(row, 'R', 40 - 1);
		if (temp_col == 80)
		{ //如果没边界，储存边界值为-1，row减一行
			R_edge[row] = -1;
			row--;
			continue; //没边界，继续向上查找
		}
		else
		{
			R_edge[row] = temp_col;
			int temp_row = Next_Point(row, temp_col, 'R'); //渡过空白层，以此为起点开始查找边界
			if (temp_row != 0)
			{
				row = temp_row;
				continue;
			} //遇到断层，当作空白起始区，再次查找
			else
				break;
		}
	}
	for (int i = top_line; i < 60; i++)
		if (L_edge[i] > R_edge[i])
			L_edge[i] = R_edge[i] = -1;
}

int Edge_Find_1(int row, char which_edge, int start_col)
{
	/*
   功能：为找到某一行的 “左” 或 “右”边界点
   参数：左边界的which_edge为 'L'，右边界为 'R' , start_loc为中线法找边界的起始列
   返回值：当为-1 或 80 时为没找到边界，否则，为所找到的边界
   */
	if (which_edge == 'R')
	{
		if (row < 60 - 1)
		{
			while (start_col < 80)
			{ ////////////////////
				if ((img[row][start_col] == BLACK && img[row][start_col - 1] == WHITE) && ((img[row + 1][start_col] == BLACK || img[row - 1][start_col] == BLACK)))
					return start_col;
				//第二个判断条件是为了消除噪音,即该点为黑点，但是上下同时为白色，可判断其为噪点
				else
					start_col += 1;
			}
		}
		else
		{
			while (start_col < 80)
			{
				if (img[row][start_col] == BLACK && img[row][start_col - 1] == WHITE)
					return start_col;
				else
					start_col += 1;
			}
		}
	}

	if (which_edge == 'L')
	{
		if (row < 60 - 1)
		{
			while (start_col >= 0)
			{ //////////////
				if (img[row][start_col] == BLACK && img[row][start_col + 1] == WHITE && ((img[row + 1][start_col] == BLACK || img[row - 1][start_col] == BLACK)))
					return start_col;
				//第二个判断条件是为了消除噪音,即该点为黑点，但是上下同时为白色，可判断其为噪点
				else
					start_col -= 1;
			}
		}
		else
		{
			while (start_col >= 0)
			{
				if (img[row][start_col] == BLACK && img[row][start_col + 1] == WHITE)
					return start_col;
				else
					start_col -= 1;
			}
		}
	}
	return start_col;
}
int Next_Point(int row, int col, char which_edge)
{
	/*
    功能：从某一个点找到上面一个边界点,循环找到边界
    参数：row,col分别为当前点的行列值，which_edge取值 'L','R',表示是左或右边界
    返回值：返回的值表示断层所在行，为0表示正常找完边界
    */
	row--;
	if (which_edge == 'L')
	{
		int i = 0;
		while (row > top_line && col < 80 && col >= 0)
		{
			for (i = 0; i < 4; i++)
			{
				if (img[row][col + i] == BLACK && img[row][col + i + 1] == WHITE)
				{
					col = col + i;
					break;
				} //左搜
				if (img[row][col - i] == BLACK && img[row][col - i + 1] == WHITE)
				{
					col = col - i;
					break;
				} //右搜
			}
			//循环结束，i=4，且为白点所以可能为断层,退出；
			if (i == 4)
			{
				if (img[row][col] == WHITE)
					return row; //返回断层所在行
				else
					while (img[row][col] == BLACK && col < 80)
						col++; //上面的点为黑色，可判断为由急弯造成的不连续
			}
			L_edge[row] = col;
			row--;
		}
	}
	if (which_edge == 'R')
	{
		int i = 0;
		while (row > top_line && col < 80 && col >= 0)
		{
			for (i = 0; i < 4; i++)
			{
				if (img[row][col + i] == BLACK && img[row][col + i - 1] == WHITE)
				{
					col = col + i;
					break;
				}
				if (img[row][col - i] == BLACK && img[row][col - i - 1] == WHITE)
				{
					col = col - i;
					break;
				}
			}
			if (i == 4)
			{
				if (img[row][col] == WHITE)
					return row;
				else
					while (img[row][col] == BLACK && col >= 0)
						col--; //上面的点为黑色，可判断为由急弯造成的不连续
			}
			R_edge[row] = col;
			row--;
		}
	}
	return 0;
}

void imgdeal()
{
	int i = 0, j = 0;
	for (i = 0; i < 60; i++)
		for (j = 0; j < 80; j++)
			imgnew[i][j] = 1;

	for (int row = 10; row <= 60; row++)
	{
		if (L_edge[row] != -1)
		{
			imgnew[row][L_edge[row]] = 0;
		}
		if (R_edge[row] != -1)
		{
			imgnew[row][R_edge[row]] = 0;
		}

		if (L_edge[row] == -1 && R_edge[row] != -1)
			Mid_Line[row] = R_edge[row] - (row + 3) / 2;
		else if (L_edge[row] != -1 && R_edge[row] == -1)
			Mid_Line[row] = L_edge[row] + (row + 3) / 2;
		else if (L_edge[row] != -1 && R_edge[row] != -1)
		{
			Mid_Line[row] = (L_edge[row] + R_edge[row]) / 2;
			imgnew[row][Mid_Line[row]] = 0;
		}
	}
	for (i = 0; i < 60; i++)
	{
		printf("\n");
		for (j = 0; j < 80; j++)
			printf("%d ", imgnew[i][j]);
	}
}
//******************************************judge*****************************************
void judgecircuit_cross()
{
	int j, i;												  //i is used for array"left right mid" ; j is used for the judgement of height
	int templ, tempr;										  //temp is used for left[i-1] || right[i-1] && one side is white
	int judgecircuitl = 0, judgecircuitr = 0, judgecross = 0; //judge is used for FLAG
	int kl, kr;												  //kl=slopeleft,kr=sloperight;
	int jump = 0;
	int num = 0;
	for (i = 59; i > 10; i--)
	{
		if (L_edge[i] != -1 && R_edge[i] != -1)
			continue;
		else if (L_edge[i] == -1 && R_edge[i] == -1)
		{
			judgecross++;
			if (judgecross >= 8)
				FLAG = 1;
		}

		else if (L_edge[i] != -1 && R_edge[i] == -1) //右环岛
		{
			int j = i;
			for (; L_edge[j] != -1 && R_edge[j] == -1 && j >= 10; j--, judgecircuitl++)
				;
			if (judgecircuitr >= 10)
				jump = 1;
			while (L_edge[j] != -1 && R_edge[j] != -1 && j >= 10)
				j--;
			i = j;
			if (jump == 1)
				for (judgecircuitl = 0; ((L_edge[i] == -1 && R_edge[i] == -1) || (L_edge[i] != -1 && R_edge[i] == -1)) && i >= 10; i--, judgecircuitl++)
					;
			if (jump == 1 && judgecircuitr >= 1)
				FLAG = 2;
		}
		else if (L_edge[i] == -1 && R_edge[i] != -1) //左环岛
		{
			int j = i;
			for (; L_edge[j] == -1 && R_edge[j] != -1 && j >= 10; j--, judgecircuitl++)
				;
			if (judgecircuitl >= 10)
				jump = 1;
			while (L_edge[j] != -1 && R_edge[j] != -1 && j >= 10)
				j--;
			i = j;
			if (jump == 1)
				for (judgecircuitl = 0; ((L_edge[i] == -1 && R_edge[i] == -1) || (L_edge[i] == -1 && R_edge[i] != -1)) && i >= 10; i--, judgecircuitl++)
					;
			if (jump == 1 && judgecircuitl >= 1)
				FLAG = 3;
		}
	}
}
void judgebarrier()
{
	int row, jump = 0;
	int leftside[100], rightside[100];
	int startline = 0, barrierl = 0, barrierr = 0;
	for (row = 59; row > 24; row--)
		leftside[row] = rightside[row] = Mid_Line[row];

	for (row = 59; row > 24; row--) //从中间往两边寻迹
	{
		while (leftside[row] > 0 && img[row][leftside[row]] == '1')
			leftside[row]--;
		while (rightside[row] > 0 && img[row][rightside[row]] == '1')
			rightside[row]++;
	}

	for (row = 59; row > 24; row--)
	{
		if (abs(leftside[row] - L_edge[row]) > 5 && abs(R_edge[row] - rightside[row]) > 5)
			startline++;
		else if (abs(leftside[row] - L_edge[row]) < 5 && abs(R_edge[row] - rightside[row]) > 5)
			barrierr++;
		else if (abs(leftside[row] - L_edge[row]) > 5 && abs(R_edge[row] - rightside[row]) < 5)
			barrierl++;
		else if (abs(Mid_Line[row] > 39 && L_edge[row] - Mid_Line[row]) <= 20 || abs(R_edge[row] - Mid_Line[row]) <= 20)
			barrierl++;
		else if (abs(Mid_Line[row] < 39 && L_edge[row] - Mid_Line[row]) <= 20 || abs(R_edge[row] - Mid_Line[row]) <= 20)
			barrierr++;
	}

	/*	printf("bal=%d bar=%d sta=%d\n",barrierl,barrierr,startline)*/;
	for (row = 59; row > 24; row--)
		if (R_edge[row] == -1 || L_edge[row] == -1)
			jump = 1;
	if (jump == 0 && startline >= 5)
		FLAG = 4;
	if (jump == 0 && barrierl >= 5)
		FLAG = 5;
	if (jump == 0 && barrierr >= 5)
		FLAG = 6;
}
//********************************************deal***************************************************
void crossdeal()
{
	int row = 59, tempxl, tempxr, tempy1, tempy2;
	int xl1 = 0, xl2 = 0, yl1 = 0, yl2 = 0;
	int xr1 = 0, xr2 = 0, yr1 = 0, yr2 = 0;
	int kl, kr;
	int jump = 0, p = 1;
	while (L_edge[row] != -1 && R_edge[row] != -1 && row >= 10)
		row--; //find white area
	tempxl = xl1 = L_edge[row + 1];
	tempxr = xr1 = R_edge[row + 1];
	yl1 = yr1 = row + 1;
	tempy1 = row;
	if (row == 59)
	{
		tempxl = xl1 = 0;
		tempxr = xr1 = 79;
		yl1 = yr1 = row;
		tempy1 = row;
		jump = 1;
	}

	while ((L_edge[row] == -1 || R_edge[row] == -1) && row >= 10)
		row--;
	xl2 = L_edge[row];
	xr2 = R_edge[row];
	tempy2 = yl2 = yr2 = row;

	kl = (yl2 - yl1) / (xl2 - xl1);
	kr = (yr2 - yr1) / (xr2 - xr1);
	/*	printf("\nkl=%d,kr=%d\n",kl,kr);*/

	/*	printf("xl1=%d xr1=%d yl1=%d yr1=%d\nxl2=%d xr2=%d yl1=%d yr2=%d\nR_edge[tempy1]=%d",xl1,xr1,yl1,yr1,xl2,xr2,yl2,yr2,R_edge[tempy1]);*/
	for (; tempy1 >= tempy2; tempy1--)
	{
		if (jump == 0)
		{
			L_edge[tempy1] = L_edge[tempy1 + 1] - 1 / kl;
			R_edge[tempy1] = R_edge[tempy1 + 1] - 1 / kr;
			imgnew[tempy1][L_edge[tempy1]] = 2;
			imgnew[tempy1][R_edge[tempy1]] = 2;
		}
		if (jump == 1)
		{
			L_edge[tempy1] = -p / kl;
			R_edge[tempy1] = 79 - p / kr;
			imgnew[tempy1][L_edge[tempy1]] = 2;
			imgnew[tempy1][R_edge[tempy1]] = 2;
			p++;
		}
	}
	int j;
	/*	for(int i=0;i<60;i++)
    {
    	printf("\n");
    	for(j=0;j<80;j++)
    	printf("%d ",imgnew[i][j]);
	}*/

	FLAG = 0;
}

void barrierdeal_L()
{
	int row = 59;
	int leftside[100], rightside[100];
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	int x3 = 0, x4 = 0, y3 = 0, y4 = 0;
	int judge = 0, jump = 0;
	float k1 = 0, k2 = 0;
	int i = 0, j = 0;
	for (row = 59; row > 24; row--)
		leftside[row] = rightside[row] = Mid_Line[row];

	for (row = 59; row > 10; row--) //从中间往两边寻迹
	{
		while (leftside[row] > 0 && img[row][leftside[row]] == '1')
			leftside[row]--;
		while (rightside[row] < 79 && img[row][rightside[row]] == '1')
			rightside[row]++;
	}

	for (row = 59; row >= 24 && abs(leftside[row] - L_edge[row]) <= 5 && abs(R_edge[row] - rightside[row]) <= 5; row--)
		;
	x2 = leftside[row];
	y2 = row;
	x1 = leftside[59];
	y1 = 59;
	/*	printf("x1=%d x2=%d y1=%d y2=%d\n",x1,x2,y1,y2);*/
	k1 = (x2 - x1) / (y2 - y1);
	/*	printf("\nk1=%d\n",k1);*/
	for (row = 58; row >= 24 && abs(leftside[row] - L_edge[row]) <= 5 && abs(R_edge[row] - rightside[row]) <= 5; row--)
	{
		L_edge[row] = L_edge[row + 1] - k1;
		imgnew[row][L_edge[row]] = 2;
	}
	/*	for(int i=0;i<60;i++)
    {
    	printf("\n");
    	for(j=0;j<80;j++)
    	printf("%d ",imgnew[i][j]);
	}*/
	for (row = 59; row > 50; row--)
	{
		if (row >= 50 && (abs(L_edge[row] - Mid_Line[row]) <= 20 || abs(R_edge[row] - Mid_Line[row]) <= 20))
			judge++;
	}
	if (judge >= 5) //判断障碍黑边将过
	{

		for (row = 58; row >= 30 && abs(leftside[row] - L_edge[row]) >= 5 && abs(R_edge[row] - rightside[row]) <= 5; row--)
			;
		x3 = leftside[row + 1];
		y3 = row + 1;
		x4 = leftside[row - 10];
		y4 = row - 10;

		k2 = (x3 - x4) / (y3 - y4);
		printf("\nk2=%d\n", k2);
		printf("x3=%d x4=%d y3=%d y4=%d\n", x3, x4, y3, y4);
		for (; row >= 10 && abs(leftside[row] - L_edge[row]) >= 2 && abs(R_edge[row] - rightside[row]) <= 5; row--) //>=2是为了保证补线不超过L_edge
		{
			L_edge[row] = L_edge[row + 1] - k2;
			imgnew[row][L_edge[row]] = 2;
		}
	}
	for (int i = 0; i < 60; i++)
	{
		printf("\n");
		for (j = 0; j < 80; j++)
			printf("%d ", imgnew[i][j]);
	}
}

void judgeFLAG()
{
	//FLAG=1,2,3,4,5,6依次为 十字 左环道 右环道 起跑线 左障碍 右障碍
	printf("flag=%d\n", FLAG);
	/*	switch(FLAG)
	{
		case 1: crossdeal();
		case 2: circuitdeal_L();
		case 3: circuitdeal_R();
		case 4: startlinedeal();
		case 5: barrierdeal_L();
		case 6: barrierdeal_R();
	}*/
	if (FLAG == 1)
		crossdeal();
	/*	else if(FLAG==2) circuitdeal_L();
	else if(FLAG==3) circuitdeal_R();
	else if(FLAG==4) startlinedeal();*/
	else if (FLAG == 5)
		barrierdeal_L();
	/*	else if(FLAG==6) barrierdeal_R();*/
}
