
function strategy(tempString)
{
	for (var i = 0, len = tempString.length; i < len; i++) 
	{
		var ch = tempString.charAt(i);
		if (tempString.charAt(i)=='E')
		{
			return i;
		}
		i++;
	}
}
