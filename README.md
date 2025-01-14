# Steppatron
SPPuRV 2 Predmetni projekat (Marko Đorđević, Radomir Zlatković, Aleksa Heler)

![](docs/steppatron_diagram.png)
![](docs/circuit.png)
![](docs/steppatron_test_sheet.png)

## Ideja iza Steppatrona
Steper motori će biti povezani na RasPi uz pomoć A4988 drajvera. Kernel modul će upravljati njima kroz GPIO pinove, a kroz parametere se postavlja koliko ih ima i koje pinove koriste. Pisanjem u node se zadaje koju notu želimo da određeni steper "svira" ili se on zaustavlja. Korisnička aplikacija čita MIDI podatke koje šalje klavijatura povezana preko USB-a (verovatno se može uraditi uz pomoc ALSA C biblioteke), obrađuje ih i prosleđuje kernel modulu u zadatom obliku. Pre toga se može implementirati čitanje karaktera sa tastature i njihovo pretvaranje u note. Kasnije se ovo moze proširiti tako da je moguće svirati više tonova u istom trenutku uz pomoć više stepera, i napraviti program koji reprodukuje MIDI fajl umesto direktnog unosa.

## Zadatak
Potrebno je realizovati modul koji služi za kontrolu step motora u zavisnosti od zadate komande, tako da motori proizvode odgovarajući zvuk. 
Motore povezati na RPI uz pomoć A4988 kontrolera. Vezu između RPI i A4988 ostvariti kroz GPIO prolaze na RPI. 
Omogućiti da korisnička aplikacija učitava sadržaj u MIDI formatu (iz datoteke ili spoljnog uređaja) i zadaje zvuk koji je potrebno svirati kroz operaciju upisa u čvor napravljenog modula.

## TODO: Dodati uputstvo za run.sh

## TODO: FAQ
Error with EoL encoding (\r\n instead of \n):
> -bash: ./run.sh: /bin/bash^M: bad interpreter: No such file or directory

Solution:
```console
pi@raspberry:~/Steppatron $ sudo apt-get install dos2unix
pi@raspberry:~/Steppatron $ dos2unix run.sh
```
