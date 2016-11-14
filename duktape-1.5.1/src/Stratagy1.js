function strategy(a)
{
	var arr= a.split();
	var i=0;
	for (int i=0; i<arr.length(); i++)
	{
		if (arr[i]=="E")
		{
			return i;
		}
	}
	return i;
}