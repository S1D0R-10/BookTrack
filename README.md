# BookTrack

## Opis projektu
BookTrack to aplikacja konsolowa napisana w języku C++ do zarządzania kolekcją książek. Aplikacja pozwala na dodawanie, edytowanie, usuwanie oraz przeglądanie książek. Została stworzona jako projekt zaliczeniowy na zajęcia z programowania w C++.

BookTrack oferuje intuicyjny interfejs użytkownika z menu tekstowym, które umożliwia łatwą nawigację po wszystkich funkcjonalnościach programu. Aplikacja przechowuje dane o książkach zarówno w pamięci operacyjnej podczas działania programu, jak i w plikach tekstowych lub CSV, co umożliwia zachowanie danych między sesjami.

## Funkcjonalności

- Wyświetlanie wszystkich książek w kolekcji
- Dodawanie nowych książek z informacjami takimi jak:
  - Tytuł
  - Autor
  - Rok wydania
- Edytowanie istniejących książek
- Usuwanie książek
- Wyszukiwanie książek po ID
- Wyszukiwanie książek po tytule
- Sortowanie książek alfabetycznie według tytułu
- Import i eksport danych w formatach TXT i CSV
- Automatyczne generowanie unikalnych identyfikatorów dla nowych książek
- Obsługa błędów z powiadomieniami dla użytkownika
- Wsparcie dla systemów macOS i Windows

## Struktura projektu

Projekt składa się z następujących plików:

- `main.cpp` - Główny plik programu, zawiera menu i logikę aplikacji
- `dataStructures.hpp` - Definicje struktur danych używanych w projekcie
- `functions.hpp` - Deklaracje funkcji
- `functions.cpp` - Implementacje funkcji
- `books.csv` i `books.txt` - Przykładowe pliki z danymi

Projekt jest zorganizowany w dwóch katalogach:
- `MacOS/` - Wersja programu dla systemu macOS
- `Windows/` - Wersja programu dla systemu Windows

Każdy katalog zawiera kompletną kopię kodu źródłowego z dostosowaniami dla danego systemu operacyjnego.

## Struktura danych

Podstawową strukturą danych w projekcie jest `Book` zawierająca:
- ID (unikalne) - liczbowy identyfikator książki
- Tytuł - pełny tytuł książki
- Autor - imię i nazwisko autora
- Rok wydania - rok publikacji książki

Książki są przechowywane w kontenerze `std::vector<Book>`, co umożliwia łatwą manipulację kolekcją i efektywne operacje wyszukiwania.

## Instalacja i uruchomienie

### Wymagania
- Kompilator C++ obsługujący standard C++11 lub nowszy
- System operacyjny: **macOS** lub **Windows**

### Kompilacja

#### macOS
```bash
cd MacOS
g++ -std=c++11 main.cpp functions.cpp -o BookTrack
```

#### Windows
```bash
cd Windows
g++ -std=c++11 main.cpp functions.cpp -o BookTrack.exe
```

### Uruchomienie

#### macOS
```bash
cd MacOS
./BookTrack [nazwa_pliku]
```

#### Windows
```bash
cd Windows
BookTrack.exe [nazwa_pliku]
```

Parametr `[nazwa_pliku]` jest opcjonalny. Jeśli nie zostanie podany, program użyje domyślnej nazwy pliku "books.txt".

## Format plików

Program obsługuje import i eksport danych w dwóch formatach:

### Format TXT
```
ID |Tytuł|Autor|Rok
```

Przykład:
```
1|Pan Tadeusz|Adam Mickiewicz|1834
2|Lalka|Bolesław Prus|1890
```

### Format CSV
```
ID,Tytuł,Autor,Rok
```

Przykład:
```
1,Pan Tadeusz,Adam Mickiewicz,1834
2,Lalka,Bolesław Prus,1890
```

Program automatycznie wykrywa format pliku na podstawie rozszerzenia (.txt lub .csv).

## Instrukcja użytkowania

1. **Uruchomienie programu**
   - Po uruchomieniu programu zostanie wyświetlone menu główne z dostępnymi opcjami.

2. **Dodawanie książki**
   - Wybierz opcję 2 z menu głównego.
   - Wprowadź tytuł, autora i rok wydania książki.
   - ID zostanie wygenerowane automatycznie.

3. **Wyświetlanie książek**
   - Wybierz opcję 1 z menu głównego, aby zobaczyć wszystkie książki.

4. **Edycja książki**
   - Wybierz opcję 3 z menu głównego.
   - Podaj ID książki, którą chcesz edytować.
   - Wprowadź nowe dane lub pozostaw puste pole, aby zachować obecną wartość.

5. **Usuwanie książki**
   - Wybierz opcję 4 z menu głównego.
   - Podaj ID książki, którą chcesz usunąć.

6. **Wyszukiwanie książek**
   - Wybierz opcję 5, aby wyszukać książkę po ID.
   - Wybierz opcję 6, aby wyszukać książki po tytule (lub jego fragmencie).

7. **Sortowanie książek**
   - Wybierz opcję 7, aby posortować książki alfabetycznie według tytułu.

8. **Zapisywanie danych**
   - Wybierz opcję 8, aby zapisać dane do pliku.
   - Podaj nazwę pliku lub naciśnij Enter, aby użyć domyślnej nazwy.

9. **Wczytywanie danych**
   - Wybierz opcję 9, aby wczytać dane z pliku.
   - Podaj nazwę pliku lub naciśnij Enter, aby użyć domyślnej nazwy.

10. **Wyjście z programu**
    - Wybierz opcję 0, aby zakończyć działanie programu.
    - Program zapyta, czy chcesz zapisać zmiany przed wyjściem.

## Autor
Projekt stworzony jako zadanie zaliczeniowe na zajęcia programowania w C++ 
[@S1D0R-10](https://www.github.com/S1D0R-10) ❤️

## Licencja
Zobacz plik [LICENSE](LICENSE) w repozytorium projektu.
