function strategy(tempstring)
{
	var found;
	found = false;
	for (var i = 0, len = tempstring.length; i < len; i++) 
	{
		var ch = tempstring.charAt(i);
		if (ch=='E')
		{
			if (found ==true)
			{
				return i;
			}
			else
			{
				found = true;
			}
		}
	}
	for (var j = 0, len = tempstring.length; j < len; j++) 
	{
		ch = tempstring.charAt(i);
		if (ch=='E')
		{
			return j;
		}
	}
	return j;
}

