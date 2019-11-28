# Qontainer 
[![Build Status](https://travis-ci.org/achimett/Qontainer.svg?branch=master)](https://travis-ci.org/achimett/Qontainer)

Progetto individuale del corso di Programmazione ad Oggetti, Laurea Triennale in Informatica, Università di Padova, tenuto dal prof. Francesco Ranzato. Si è scelto di modellare la creazione di un software contenitore per articoli in vendita in un negozio di elettronica (es. Mediaword, Unieuro).

## File Essenziali
| File | Descrizione |
| ------ | ------ |
| [specificaProgetto1819.pdf](specificaProgetto1819.pdf) | Requisiti da soddisfare |
| [relazione.pdf](relazione.pdf) | Relazione che accompagna il progetto |
| [feedback.txt](feedback.txt) | Valutazione ricevuta dal professore successivamente alla consegna dell'elaborato finale |

## Compilazione

Requisiti:
- Qt 5.5.1 (o superiore)

Nella cartella del progetto, eseguire le seguenti istruzioni da terminale:
```sh
$ qmake Qontainer.pro
$ make
```

## Istruzioni per l'uso
All’avvio si aprirà la finestra principale senza nessuna entry. Nella barra degli strumenti sono presenti i seguenti pulsanti:
- Salva: salva il Container corrente se esiste altrimenti richiama Salva
con Nome.
- Salva con Nome: apre una finestra in cui richiede dove salvare il
Container corrente e lo salva in formato YAML.
- Apri: apre un Container in formato YAML. Un file example1.yaml è
presente all’interno della cartella radice del progetto.
- Ricerca: apre un form di ricerca dal quale si possono fare ricerche fra gli articoli utilizzando i parametri
 mostrati; il pulsante Cerca fa partire la ricerca e restituisce il risultato sulla finestra principale. Il pulsante Rimuovi Elementi Trovati cancellerà dal container gli elementi risultanti dalla ricerca. La chiusura di questa finestra comporta l’annullamento della ricerca e il ritorno della finestra principale allo stato iniziale.
- Nuovo Articolo: verrà aperta una piccola form in cui verrà chiesto che tipo di articolo inserire e successivamente una Form di Inserimento. Una volta inseriti i dati e premuto il pulsante Inserisci la form rimarrà aperta divenendo una Form di Visualizzazione/Modifica.

Facendo doppio click su una riga della tabella verrà aperta una Form di Visualizzazione/Modifica che permetterà di vedere in dettaglio i campi dati specifici dell’articolo in quella riga di tabella. È possibile modificare i dati e applicare le modifiche con il pulsante Applica Mod oppure eliminare l’articolo dal Container con il pulsante Elimina.
