function boolean freed_space(char a[][], int b, int c)
{
	if(a[b][c]=='0')
	{
		return true;
	}
	else
	{
		return false;
	}
}

function int[] Stratagy1(char board[][])
{
	boolean turn=false;
	int a=0;
	int b=0;
	while (!turn)
	{
		turn=freed_space(board,a,b);
		if(!turn)
		{
			if (a<3)
			{
				a++;
			}
			else
			{
				a=0;
				b++;
			}
		}
	}
	int [] result = new int[2];
	result[0]=a;
	result[1]=b;
	return result;
}