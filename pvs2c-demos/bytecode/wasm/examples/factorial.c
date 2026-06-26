__attribute__((export_name("factorial")))
int factorial(int n) {
  int acc = 1;
  while (n != 0) {
    acc *= n;
    n -= 1;
  }
  return acc;
}
