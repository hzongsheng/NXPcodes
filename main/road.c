void Road();
int Edge_Find_1(int,char,int);
int Next_Point(int,int,char);
void imgdeal();


extern uint8 img[60][80];
extern uint8 imgbuff[CAMERA_SIZE];
//int imgnew[60][80];

float dit;

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



void imgdeal()
{
  
    float dis=0;
    for(int row=top_line;row<60;row++)
    {		
		if(L_edge[row]==-1&&R_edge[row]!=-1)
			Mid_Line[row]=R_edge[row]-(row+3)/2;
		else if(L_edge[row]!=-1&&R_edge[row]==-1)
			Mid_Line[row]=L_edge[row]+(row+3)/2;
		else if(L_edge[row]!=-1&&R_edge[row]!=-1)
        {
            Mid_Line[row]=(L_edge[row]+R_edge[row])/2;
            img[row][Mid_Line[row]]=0;
        }
    }
   
    
    for(int row=59;row>=49;row--)
    if( Mid_Line[row]<40)
    {
         dis=dis+Mid_Line[row]-40;
    }
  else{ dis=dis+Mid_Line[row]-40;}
   
   
    dit=dis/10;
    
    
    }

