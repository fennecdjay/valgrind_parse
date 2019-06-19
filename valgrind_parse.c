#include <stdio.h>
#include <stdlib.h>

struct GL {
  FILE *stream;
  char *line;
  size_t len;
  ssize_t nread;
};

static inline ssize_t get(struct GL *gl) {
  return gl->nread = getline(&gl->line, &gl->len, gl->stream);
}

static inline FILE* open_log(const char* filename) {
  FILE* f = fopen(filename, "r");
  if (f == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  return f;
}

size_t get_pidlen(struct GL *gl) {
  size_t pidlen = 0;
  if (get(gl) != -1) {
    while (gl->line[pidlen + 2] != '=')
      ++pidlen;
  }
  return pidlen;
}

int main(int argc, char *argv[]) {
  struct GL gl = {.stream = argc > 1 ? open_log(argv[1]) : stdin };
  const size_t pidlen = get_pidlen(&gl);
  unsigned int error = 0;
  if (pidlen) {
    unsigned int n = 6;
    while (n && get(&gl) != -1)
      n--;
    while (get(&gl) != -1) {
      if (gl.line[2 + pidlen + 3] != ' ') {
        if (gl.line[2 + pidlen + 3] == 'H')
          break;
        if (gl.line[2 + pidlen + 3] == '\n')
          continue;
        printf("[%u] %s", ++error, gl.line + pidlen + 5);
        if (get(&gl) == -1)
          break;
        printf("%s", gl.line + pidlen + 5);
      }
    }
  }
  free(gl.line);
  fclose(gl.stream);
  exit(error);
}
