function strategy(tostring)
{
	var i;
	var found;
	i=0;
	found = false;
	for (ch in String tostring)
	{
		if (ch=='E')
		{
			if (found ==true)
			{
				return i;
			}
			else
			{
				found = true;
				i++;
			}
		}
		else
		{
			i++;
		}
	}
	for (cha in String tostring)
	{
		if (ch=='E')
		{
			return i;
		}
		else
		{
			i++;
		}
	}
	return i;
}
	
}