# Párhuzasom Algoritmusok

## Feladat kiírása:

### OpenMP

Where is waldo

- Adott egy n hosszú 3 dimenziós mátrix amit feltöltünk elemekkel (ebben az esetben 0-kal), ahol elrejtjük (aki itt egy 1-es) Waldót.
- A mátrix-on végig megyünk egy lineáris kereséssel majd egy párhuzamosított kereséssel mérve a futási időt.
- A program futása előtt meg tudjuk adni hogy Waldo hányszor bújjon el úrja.
- Amennyiben megtalálták a keresés nem kezdődik újra az 0,0,0 pozícióból.


 ### Posix
 
 - Van n darab vödrünk. Az egyik vödör alatt elbújt egy kiskacsa.
 - Minden egyes körben egy vödröt emelhetünk fel, amennyiben a kiskacsa nem ott van akkor valamelyik szomszédos vödörbe átmegy.
 - A feladat a kiskacsa megtalálása.
 - A párhuzamosítás több különböző algroitmus egy időben való futattásával történik
 
 ### Tetszőleges
 
 - OpenMP segítségével párhuzamosítunk
 - Veszünk egy szöveges file-t
 - Parancssorból argumentumként bekérünk egy betűt
 - Végig megyünk a file-on keresve ezt a betűt (párhuzamosítva és a nélkül is)
 - Végig mérjük az időt és a végén ki írjuk ezt és a betű előforulásának számát
