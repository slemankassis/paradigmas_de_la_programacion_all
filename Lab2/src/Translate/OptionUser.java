package Translate;

import java.io.IOException;
import java.util.Scanner;
import java.util.concurrent.atomic.AtomicReference;

public class OptionUser {

  private void SwapString(String s1, String s2) {
    AtomicReference<String> string1 = new AtomicReference<String>(s1);
    AtomicReference<String> string2 = new AtomicReference<String>(s2);
    string1.set(string2.getAndSet(string1.get()));
  }

  public String word_user(IDictionary dict,
                      IDictionary dict_temp,
                      ListIgnore dict_ignored,
                      ListIgnore ig_temp, String buff) throws IOException {

    String buff_translated = "";
    char option;
    boolean state = true;

    Scanner string = new Scanner(System.in);

    System.out.print("No hay traducción para la palabra: " + buff + "\n");
    System.out.print("Ignorar Todas (i) Ignorar todas siempre (h)\n");
    System.out.print("Traducir como (t)Traducir siempre como (s)\n:");

    while (state) {
      option = string.next().charAt(0);

      switch (option) {
        case 'i':  // "Ignorar".
          // It is decided to pass the word untranslated.
          ig_temp.dict_add(buff, null);
          buff_translated = buff;
          state = false;
          break;

        case 'h':  // "Ignorar todas".
          // It is added to list of ignored words.
          dict_ignored.dict_add(buff, null);
          buff_translated = buff;
          state = false;
          break;

        case 't':  // Traducir como".
          // It is added to temporary list, only for current file.
          Scanner reader = new Scanner(System.in);
          buff_translated = reader.next();

          if (dict.is_reverse()) {
            SwapString(buff_translated, buff);
          }
          dict_temp.dict_add(buff, buff_translated);
          state = false;
          break;

        case 's':  // "Traducir siempre como".
          // It is added to the open dict.
          Scanner reader2 = new Scanner(System.in);
          buff_translated = reader2.next();

          if (dict.is_reverse()) {
            SwapString(buff_translated, buff);
          }

          dict.dict_add(buff, buff_translated);
          state = false;
          break;

        default:
          System.out.println("\n" + option
                  + "\" is invalid. Please choose "
                  + "a valid option.\n\n");
      }
    }
    return buff_translated;
  }
}