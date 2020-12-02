#include "../minirt.h"

Test(minirt, parsing)
{
	char *a = "1234.234561";
	parse_double_or_die(&a);
	char *b = "1234523845933297487324098327598342795.943279382475932993298324594379875057";
	parse_double_or_die(&b);
}
