#define EPSILON 								0.00001
#define ESC										0xff1b
#define SPACE									0x20	
#define TAB										0xff09
#define DESTROY_NOTIFY							17	
#define	STRUCTURE_NOTIFY_MASK 					1L << 17
#define BMP_TOTAL_HEADER_SIZE					54
#define BMP_HEADER_SIZE							14
#define BMP_INFO_HEADER_SIZE					40
#define MAX_INTEGER_LEN							10
#define COLOR_DEPTH								32	
#define BYTE_SZ									8

/*
**  Do no set out of range values !
*/

#define BACKGROUND_COLOR						(t_color){255,255,255}
#define DEFAULT_AMBIENT_LIGHT_INTENSITY 		1
#define DEFAULT_AMBIENT_LIGHT_COLOR 			(t_color){255,255,255}
#define DEFAULT_AMBIENT_LIGHT_COLOR_DISTRIB 	(t_vec3){1,1,1}
