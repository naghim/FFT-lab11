# Labor 11

## Diagramok készítése Qt-ben

Diagramok elkészítéséhez a [Qt Charts](https://doc.qt.io/qt-5/qtcharts-index.html) könyvtárát/modulját fogjuk használni, amely könnyen használható diagram-összetevőket tartalmaz. Ennek érdekében a projektfájlban majd hozzá kell adjuk: ```QT += charts```. 

## Feladatok

1. Próbáljunk ki különböző diagramokat. Készítsünk legalább 5 értékből álló: 
  *  vonaldiagramot (_linechart_ - s ennek a görbés változatát _splinechart_, vagyis a pontokat egyenesek helyett görbék kötik össze),
  *  tortadiagramot (_piechart_), 
  *  oszlopdiagramot (_barchart_ - ennél is próbáljuk ki a horizontális és vertikális elrendezést) stb.

<img src="https://i.ibb.co/MgL4dHT/charts.png" align="center" />

2. Készítsünk "élő" vonaldiagramot, amelyet folyamatosan eltolunk (adunk hozzá új, véletlenszerűen kigenerált pontot, a régit pedig töröljük). Ennek megfelelően állítsuk a tengely címkéit is. Állítsuk át a vonal/háttér színét is tetszőleges színűre. 

3. Az előző feladatot módosítsuk annyiban, hogy a véletlenszerűen kigenerált pontok helyett az aktuális CPU kihasználtságot tüntessük fel. A kihasználtságot a következőképp tudjuk lekérni: 

```
#include <Windows.h>

static float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
   static unsigned long long _previousTotalTicks = 0;
   static unsigned long long _previousIdleTicks = 0;

   unsigned long long totalTicksSinceLastTime = totalTicks-_previousTotalTicks;
   unsigned long long idleTicksSinceLastTime  = idleTicks-_previousIdleTicks;

   float ret = 1.0f-((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime)/totalTicksSinceLastTime : 0);

   _previousTotalTicks = totalTicks;
   _previousIdleTicks  = idleTicks;
   return ret;
}

static unsigned long long FileTimeToInt64(const FILETIME & ft) {return (((unsigned long long)(ft.dwHighDateTime))<<32)|((unsigned long long)ft.dwLowDateTime);}

float GetCPULoad()
{
   FILETIME idleTime, kernelTime, userTime;
   return GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime)+FileTimeToInt64(userTime)) : -1.0f;
}
```

[Forrás](https://stackoverflow.com/questions/23143693/retrieving-cpu-load-percent-total-in-windows-with-c)
