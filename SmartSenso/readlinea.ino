// Stato linea
int readlinea(int linea) {
  while (linea == 0) {
    int lineanew = digitalRead(A0);
    delay(100); // tempo tra 2 linee tratteggiate
    linea = digitalRead(A0);
    if (lineanew == linea)
      linea = 1; // linea trateggiata 
    else
      linea = 0; // linea continua
  }
}
