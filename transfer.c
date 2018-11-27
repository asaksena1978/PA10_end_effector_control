void transfer(double *sink, double *src)
{
	unsigned char i,j;

	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			*(sink + (i * 4) + j)  = *(src + (i * 4) + j);
		}
	}
}
