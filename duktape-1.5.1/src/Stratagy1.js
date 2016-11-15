
function strategy(tempstring)
{
	for (var i = 0, len = tempstring.length; i < len; i++) 
	{
		var ch = tempstring.charAt(i);
		if (ch=='E')
		{
			return i;
		}
		i++;
	}
}
