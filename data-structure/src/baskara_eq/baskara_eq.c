#include <stdio.h>
#include <math.h>

float calcDelta(float ax2, float bx, float c)
{
  return powf(bx, 2) - 4 * ax2 * c;
}

void main()
{
  // Variavéis da equação de baskara.
  float ax2, bx, c, delta;

  // Solução para delta maior ou igual a zero
  float solution[2];

  printf("Monte uma equação do segundo grau para ter sua resolução:\n\n");

  printf("Digite o valor de ax²: ");
  scanf("%f", &ax2);

  printf("Digite o valor de bx: ");
  scanf("%f", &bx);

  printf("Digite o valor de c: ");
  scanf("%f", &c);

  printf("\nEquação a ser resolvida: (%.1f)x² + (%.1f)x + (%.1f) = 0\n\n", ax2, bx, c);

  delta = calcDelta(ax2, bx, c);

  if (delta > 0)
  {
    solution[0] = (-bx + sqrtf(delta)) / (2 * ax2);
    solution[1] = (-bx - sqrtf(delta)) / (2 * ax2);
    printf("S={%.2f;%.2f}\n\n", solution[0], solution[1]);
  }
  else if (delta == 0)
  {
    solution[0] = -bx / (2 * ax2);
    printf("S={%.2f}\n\n", solution[0]);
  }
  else
  {
    printf("Sem solução dentro do conjunto dos números reais.\n\n");
  }
}
