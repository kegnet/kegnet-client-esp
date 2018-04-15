#ifndef FILES_H_
#define FILES_H_

void listFiles() {
  Serial.println();
  Serial.println("SPIFFS files found:");

  fs::Dir dir = SPIFFS.openDir("/"); // Root directory
  String  line = "=====================================";

  Serial.println(line);
  Serial.println("  File name               Size");
  Serial.println(line);

  while (dir.next()) {
    String fileName = dir.fileName();
    Serial.print(fileName);
    int spaces = 25 - fileName.length(); // Tabulate nicely
    if (spaces < 0) spaces = 1;
    while (spaces--)
      Serial.print(" ");
    fs::File f = dir.openFile("r");
    Serial.print(f.size());
    Serial.println(" bytes");
    f.close();
    yield();
  }

  Serial.println(line);
}

#endif
