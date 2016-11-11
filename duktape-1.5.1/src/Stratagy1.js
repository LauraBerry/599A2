function freed_space(board, b, c)
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

function Stratagy1(board)
{
	turn=false;
	a=0;
	b=0;
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
	result = new int[2];
	result[0]=a;
	result[1]=b;
	return result;
}
