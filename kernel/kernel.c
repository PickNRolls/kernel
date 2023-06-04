int main() {
  char* video_memory = (char*) 0xb8000;
  char message[] = "Hello from kernel written in C!";
  int index = 0;
  char c;
  while ((c = message[index]) != 0) {
    video_memory[index] = c;
    index += 2;
  }
  return 0;
}
