# Übungsaufgabe Nr. 5 – JPEG in .rodata einbetten

In dieser Übung vertiefen Sie Ihre Kenntnisse im Umgang mit **CMake**, **Build-Pipelines** und dem **Speicherlayout von Programmen**. Außerdem werden Sie ein kleines **Python-Tool** in den CMake-Build integrieren und die eingebetteten Daten in einem **C++-Programm** auswerten.

Ziel ist es, eine JPEG-Datei in das `.rodata`-Segment des Programms einzubetten, das Ergebnis mit `objdump`/`readelf` zu kontrollieren und die Daten im C++-Programm zu verwenden. Zusätzlich binden Sie **OpenCV** ein und lesen Parameter der JPEG-Datei aus.

**WICHTIG:** Diese Übungsaufgabe wird **einzeln** bearbeitet.

## Vorbereitung: Git-Branch anlegen

Stellen Sie sicher, dass Ihr lokales Repository mit `upstream` synchronisiert ist.

```sh
git fetch --all
git switch -c solution-005 upstream/exercise-005
git push --set-upstream origin solution-005
```

Prüfen Sie mit:

```sh
git branch -a
```

dass der Branch `solution-005` existiert.

Alle Änderungen erfolgen im Verzeichnis:

```
exercise-005/
```

---

## Ziel der Übung

Sie sollen:

1. ein **Python-Skript** verwenden, das ein JPEG-Bild in ein C-kompatibles Array konvertiert,
2. dieses Skript über **CMake** automatisch ausführen lassen,
3. ein **C++-Programm** schreiben, das die generierte Datei einkompiliert,
4. mit `objdump` und/oder `readelf` prüfen, dass die Bilddaten im **`.rodata`-Segment** liegen,
5. im C++-Programm mit Hilfe der **fmt-Bibliothek** die Größe der eingebetteten Daten ausgeben,
6. **OpenCV** einbinden und Bildparameter der JPEG-Datei auslesen.

---

## Aufgabenbeschreibung

### Aufgabe 1 – Projektstruktur & JPEG-Datei

Erweitern Sie das Verzeichnis `exercise-005/` um folgende Struktur:

```
exercise-005/
  CMakeLists.txt
  src/
    main.cpp
  jpg_to_header.py
  assets/
    image.jpg
```

---

### Aufgabe 2 – Integration des Python-Skripts in CMake

Erweitern Sie `CMakeLists.txt` so, dass:

- Python gefunden wird,
- ein Custom Command das Python-Skript aufruft,
- eine Header-Datei (z. B. `embedded_image.h`) generiert wird,
- das C++-Target von dieser Datei abhängt,
- der Include-Pfad korrekt gesetzt wird.

---

### Aufgabe 3 – C++-Programm & fmt

Implementieren Sie `main.cpp` so, dass:

- die generierte Header-Datei eingebunden wird,
- die Größe des eingebetteten Arrays per `fmt::print()` ausgegeben wird.

---

### Aufgabe 4 – Prüfung des Segments (.rodata)

Überprüfen Sie das Segment per:

```sh
readelf -S jpeg_rodata_demo
objdump -t jpeg_rodata_demo
```

Dokumentieren Sie in `ANSWER.md`:

- Symbolname,
- Segment,
- relevante Output-Auszüge,
- Tests mit unterschiedlichen Bildern (Bilder können via wget/curl geladen werden).

---

## Aufgabe 5 – OpenCV

Installieren:

```sh
sudo apt-get install libopencv-dev
```

In `CMakeLists.txt`:

```cmake
find_package(OpenCV REQUIRED core imgcodecs imgproc)

target_link_libraries(${PROJECT_NAME} PRIVATE
    fmt::fmt
    opencv_core
    opencv_imgcodecs
    opencv_imgproc
)
```

Erweitern Sie Ihr Programm:

- Bild aus eingebettetem Array mittels `cv::imdecode()` einlesen,
- Breite, Höhe und Kanäle mit fmt ausgeben.

---

## Ausblick – Erweiterungsaufgaben (optional)

### Aufgabe 6 – Bildverarbeitung mit OpenCV (Filter)

Implementieren Sie mindestens zwei einfache Filter:

- Gaussian Blur  
- Canny Kantenfilter  
- Umwandlung in Graustufen  

Geben Sie Parameter und Filterresultate per fmt aus.

### Aufgabe 7 – Speichern des bearbeiteten Bildes

Speichern Sie das bearbeitete Bild mittels:

```cpp

std::string output_filename = fmt::format("{}/{}",path, filename);
cv::imwrite(output_filename, img);
```

Anforderungen:

- Dateiname, Ablageort soll per CLI-Parameter (z. B. über CLI11) steuerbar sein
- Der Defaultwert für den Dateinamen und den Ablagepfad bitte über die `config.h.in` Datei steuern
- Ausgabe der Dateigröße nach dem Speichern,
- optional: Vergleich zwischen Originalgröße und Ausgabegröße.

---

## Abgabe

Ihre Abgabe soll enthalten:

- den Branch `solution-005`,
- das vollständige `exercise-005/` Verzeichnis,
- `ANSWER.md` mit den Untersuchungsergebnissen,
- optional die Bildanalyse- und Filteraufgaben.
