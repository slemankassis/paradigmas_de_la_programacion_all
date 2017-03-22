package Translate;

public class TryChar {

  public TryChar() {};

  public boolean ValidChar(char chr) {

    boolean result = false;
    String listchar = "àèìòùáéíóúäëïöüÁÀÉÈÍÌÓÒÚÙÖÜ";

    if ((chr >= 'a' && chr <= 'z') ||
        (chr >= 'A' && chr <= 'Z') ||
        (chr >= '0' && chr <= '9')) {
      result = true;

    } else {
      for (int i = 0; !(result) && i < listchar.length(); i++) {
        result = (listchar.charAt(i) == chr);
      }
    }

    return result;
  }
    
  public char change_mayus_minus(char chr) {
    // a = 61 and z = 122.
    if (chr >= 'a' && chr <= 'z') {
      chr -= 32;
    } else {
      // A = 41 and z = 90. (c >= 'A' && c <= 'Z').
      chr += 32;
    }
    return chr;
  }

  public boolean is_mayus(char chr) {
    return (chr >= 'A' && chr <= 'Z');
  }
}