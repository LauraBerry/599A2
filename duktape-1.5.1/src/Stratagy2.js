function strategy(a, b)
{
	a = a*20;
	b = b*20;
	a=a*b;
	a=a%2;
	a=Math.floor(a);
	return a;
}