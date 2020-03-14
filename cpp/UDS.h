#include <iostream>
#include <cstring>
using namespace std;
#define UDS_SPACE_TOK 26
#define UDS_MIN_TOK 27
#define MAX_UDS_SZ 29

/*
 * "To be a great motorbike racer, the most important thing is passion for the bike." ~ Valentino Rossi
 */
 
class UDS{
    /*
     * Universal Dictionary Structure:
     * memory efficient way of storing and searching words.
     * Something like a set for strings.
     */
   private:
        struct Cell{
                struct Cell *cell[MAX_UDS_SZ];
        };
        Cell *cell;

        static int toIndex(char c){
                if ((c<='Z') && (c>='A') || (c<='z') && (c>='a'))
                        return toupper(c) -'A';
                if (c == ' ') return UDS_SPACE_TOK;
                if (c == '-') return UDS_MIN_TOK;
                return -1;
        }

        static char fromIndex(int i){
                if (i >= 0 && i <=('Z'-'A'))
                       return toupper((char) i+'A');
                if (i == UDS_SPACE_TOK) return ' ';
                if (i == UDS_MIN_TOK) return '-';
                return 0;
        }

    public:
        UDS(){
                cell = new Cell;
                for (int i=0; i < MAX_UDS_SZ; cell->cell[i++]=NULL);
        }

        void insert(char* word){
                int pos, wlen = strlen(word);
                Cell* dict = cell;
                for(int i=0; i < wlen; i++){
                        pos = toIndex(word[i]);
                        if (dict->cell[pos] != NULL) {
                                dict=dict->cell[pos];
                        }
                        else {
                                dict->cell[pos] = new Cell;
                                for(int k = 0; k < MAX_UDS_SZ; dict->cell[pos]->cell[k++]=NULL);
                                dict = dict->cell[pos];
                        }
                }
                dict->cell[MAX_UDS_SZ-1] = dict;
        }

        bool search(char* word){
                int test = 1, i = 0;
                int wlen = strlen(word);
                Cell *dict = cell;
                while (test && (i < wlen)){
                        if(!dict->cell[toIndex(word[i])])
                               test = 0;
                        else
                               dict=dict->cell[toIndex(word[i++])];
                }
                if ((i==strlen(word)) && (dict->cell[MAX_UDS_SZ-1] == dict) && test)
                        return true;
                return false;
        }

};

