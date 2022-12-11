```
/*
struct termios termios;

tcgetattr(filedesc, &termios);
termios.c_lflag &= ~ICANON; // Set non-canonical mode
termios.c_cc[VTIME] = 100; // Set timeout of 10.0 seconds
tcsetattr(filedesc, TCSANOW, &termios);
*/
```
