function stratagy2(a,b)
{
	var indexes = new Array();
	if (a<2)
	{
		if(b>=2)
		{
			b=0;
		}
	}
	else
	{
		a=0;
		if(b>=2)
		{
			b=0;
		}
	}
	indexes[0]=a;
	indexes[1]=b;
	return indexes;
}