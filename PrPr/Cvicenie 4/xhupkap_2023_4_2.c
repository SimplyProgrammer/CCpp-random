// Uloha 4.2

#include <stdio.h>

double tyzdenna_mzda(double, double);

int main()
{
	printf("Pocet opakovani: ");

	int count;
	scanf("%i", &count);

	double total = 0;
	while (count--)
	{
		printf("Zadaj mzdu a pocet hod: ");

		double mzda, hod, mzdaNaTyzden;
		scanf("%lf %lf", &mzda, &hod);

		total += (mzdaNaTyzden = tyzdenna_mzda(mzda, hod));
		printf("Hod. mzda: %g Euro/hod, hodin: %g, spolu: %g Euro\n", mzda, hod, mzdaNaTyzden);
	}

	printf("Celkova mzda: %g\n", total);
}

double tyzdenna_mzda(double h_mzda, double hod)
{
	float zaTyzden = h_mzda * hod;
	if (hod > 40)
		return zaTyzden + h_mzda * (hod - 40) * 1.5;
	return zaTyzden;
}