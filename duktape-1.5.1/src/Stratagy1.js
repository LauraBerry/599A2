
function strategy(tempstring)
{
	for (var i = 0, len = tempstring.length; i < len; i++) 
	{
		if (tempstring[i]=='E')
		{
			return i;
		}
		else
		{
			i++;
		}
	}
}
