# BookTrack

## Opis projektu
BookTrack to aplikacja konsolowa napisana w języku C++ do zarządzania kolekcją książek. Aplikacja pozwala na dodawanie, edytowanie, usuwanie oraz przeglądanie książek. Została stworzona jako projekt zaliczeniowy na zajęcia z programowania w C++.

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

## Struktura projektu

Projekt składa się z następujących plików:

- `main.cpp` - Główny plik programu, zawiera menu i logikę aplikacji
- `dataStructures.hpp` - Definicje struktur danych używanych w projekcie
- `functions.hpp` - Deklaracje funkcji
- `functions.cpp` - Implementacje funkcji
- `books.csv` i `books.txt` - Przykładowe pliki z danymi

## Struktura danych

Podstawową strukturą danych w projekcie jest `Book` zawierająca:
- ID (unikalne)
- Tytuł
- Autor
- Rok wydania

## Instalacja i uruchomienie

### Wymagania
- Kompilator C++ obsługujący standard C++11 lub nowszy
- System operacyjny: **macOS** (preferowany), Linux lub Windows

### Kompilacja
```bash
g++ -std=c++11 main.cpp functions.cpp -o BookTrack
```

### Uruchomienie
```bash
./BookTrack
```

## Format plików

Program obsługuje import i eksport danych w dwóch formatach:

### Format TXT
```
ID |Tytuł|Autor|Rok
```

### Format CSV
```
ID,Tytuł,Autor,Rok
```

## Autor
Projekt stworzony jako zadanie zaliczeniowe na zajęcia programowania w C++ 
[@S1D0R-10](https://www.github.com/S1D0R-10) ❤️

## Licencja
Zobacz plik [LICENSE](LICENSE) w repozytorium projektu.
