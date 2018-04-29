/*is_[...] 3 states of a character */
#define IS_SYMBOL 0
#define IS_ALPHABET  1
#define IS_NUMBER 2

/*function prototype declarations*/
void refresh();
long isSpace(char);
void charsFrequency();
void analyzeChars(const char*, long*, long*);
void categorizeChar(char, long*);
long proposeCeasar(long, const char * );
long shiftCipher( long, const char * );
