#ifndef UTILS_H
#define UTILS_H

typedef enum{
	FALSE,
	TRUE
} bool_t;

#define IS_BIT_SET(n, pos)	((n & (1 << pos)) != 0)
#define TOGGLE_BIT(n, pos)	(n = n ^ (1 << pos))
#define COMPLEMENT(n) 		(n = n ^ 0xFFFFFFFF)
#define UNSET_BIT(n, pos)	(n = n & ((1 << pos) ^ 0xFFFFFFF))
#define SET_BIT(n, pos) 	(n = n | 1 << pos)

#endif

