# ALKS_3PI_COMMUNICATION

Repozitář obsahuje 4 soubory ve složce ALKS_3PI_COMMUNICATION:
  1) 3pi_include
  2) 3pi_main
  3) ALKS_include
  4) ALKS_main
  
## 3pi_include
Obsahuje soubory (knihovny), které vyžaduje samotné Pololu 3pi.
## 3pi_main
Obsahuje program 3pi_BatteryControl, který obsahuje program pro robota Pololu 3pi. (Tento soubor byl převzat z jiného projektu, který sem psal a název sem nezměnil).
## ALKS_include
Obsahuje *.h* soubor, který obsahuje prakticky překopírovaný *.h* pro Pololu 3pi, takže je možné používat funkce pro 3pi v kódu pro ALKS.
## ALKS_main
Obsahuje program pro řízení Pololu 3pi z ALKSu. Pokud bude třeba přidat funkcionalitu pro ovládání robota (zdroják), tak je třeba vložit to do main.cpp v této složce.
