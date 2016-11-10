function diagonal_possible(char [][] a)
{
	if(a[0][0]=='x' && a[2][2]=='x')
	{
		return true;
	}
	else if (a[0][2]=='x' && a[2][0]==='x')
	{
		return true;
	}
	else
	{
		return false;
	}
}
function boolean is_it_clear(char [][]a, int b, int c)
{
	if(a[b][c]==' ')
	{
		return true;
	}
	else
	{
		return false;
	}
}
function int[] Stratagy2(char[][] board)
{
	boolean diagonal=false;
	boolean clear=false;
	boolean all_corners_tried=false;
	int a;
	int b;
	while(!clear)
	{
		diagonal=diagonal_possible(board);
		if (diagonal==true)
		{
			a=1;
			b=1;
			clear=is_it_clear(board,a,b);
		}
		else if (all_corners_tried==false)
		{
			a=0;
			b=0;
			clear=is_it_clear(board,a,b);
			a=2;
			clear=is_it_clear(board,a,b);
			b=2;
			clear=is_it_clear(board,a,b);
			a=0;
			clear=is_it_clear(board,a,b);
			all_corners_tried=false;
		}
		else
		{
			if(b<3)
			{
				b++;
			}
			else
			{
				b=0;
				a++;
			}
		}
	}
}