/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150       25 ms           6 ms
    200       71 ms           12 ms
    300       218 ms          29 ms
    400       485 ms          86 ms
    800       3.7 s           292 ms
   1600       30 s            1 s
   3200       gissar 300 s    4.6 s
   6400       gissar 3000 s   20 s
  12800       gissar 30000 s  87 s


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(n^4). Eftersom det är "n choose 4" vilket har tidskomplexiteten O(n^4)

Sortering: O(n^2 log(n)). Eftersom vi sorterar en vector för varje punkt.
