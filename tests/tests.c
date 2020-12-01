#include "../minirt.h"

Test(minirt, parsing)
{
	char *a = "1234.234";
	cr_assert(parse_double_or_die(&a) == 1234.234);
	char *b = "-12345";
	cr_assert(parse_double_or_die(&b) == -12345);
	char *c = "        -39084";
	cr_assert(parse_double_or_die(&c) ==  -39084);
	char *d = "        -39084     ";
	cr_assert(parse_double_or_die(&d) ==  -39084);
	char *e = "        -39084.93749559     ";
	cr_assert(parse_double_or_die(&e) ==  -39084.93749559);
	char *f = "39084.93749559 1 ,   ";
	cr_assert(parse_double_or_die(&f) ==  39084.93749559);
}
