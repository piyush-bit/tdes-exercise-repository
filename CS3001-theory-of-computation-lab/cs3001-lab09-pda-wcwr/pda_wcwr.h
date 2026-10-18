#ifndef PDA_WCWR_H
#define PDA_WCWR_H

/**
 * Checks if the input string s matches the language W c W^R.
 * 
 * @param s Null-terminated input string.
 * @return 1 if s is in L = { w c w^R | w in {a, b}* }, 0 otherwise.
 */
int is_valid_wcwr(const char *s);

#endif /* PDA_WCWR_H */
