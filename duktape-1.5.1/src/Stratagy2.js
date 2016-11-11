function stratagy2(a, b)
{
	b= Math.random();
	b=b*20;
	a=a*b;
	a=a%2;
	a=Math.floor(a);
	return a;
}