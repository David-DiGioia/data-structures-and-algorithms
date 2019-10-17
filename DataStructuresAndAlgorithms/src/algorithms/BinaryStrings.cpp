
/*
	How many binary strings of length n has no consecutive ones?

	1   2    3
	-----------------------------------
	0   00   000
	1   01   001
	    10   010
	    11x  011x
		     100
		     101
		     110x
		     111x
	
	f(n) = f(n-1) + f(n-2)

	f(n-1) because have of new strings contain a 0 as first bit, so all that
	was previously valid will remain valid

	f(n-2) because the other half contain a 1 as first bit, which invalidates all the
	bitstrings that f(n-1) has that f(n-2) doesn't have. So we're left with f(n-2)

	INPUT: n must be a natural number
*/
int nonConsecutiveOnes(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 2;
	if (n == 2) return 3;
	return nonConsecutiveOnes(n - 1) + nonConsecutiveOnes(n - 2);
}