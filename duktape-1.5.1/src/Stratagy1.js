function stratey(a, b)
{
	var a= Math.random();
	a=a*20;
	if(a>2)
	{
		a=a%2;
	}
	a=Math.floor(a);
	return a;
}