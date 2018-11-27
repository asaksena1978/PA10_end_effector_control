void inv_mat(double *arr_inv, double *arr)
{
	unsigned char i,j,k;

	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 3; j++)
		{
			*(arr_inv + (j * 4) + i) = *(arr + (i * 4) + j);
		}
	}


	for(i = 0; i < 3; i++)
	{
		*(arr_inv + (i * 4) + 3) = 0;		
		for(j = 0; j < 3; j++)
		{
			*(arr_inv + (i * 4) + 3) = (*(arr_inv + (i * 4) + 3)) + ((*(arr_inv + (i * 4) + j)) * (*(arr + (j * 4) + 3))); 
		}
	}	

	*(arr_inv + (3 * 4) + 0) = 0;
	*(arr_inv + (3 * 4) + 1) = 0;
	*(arr_inv + (3 * 4) + 2) = 0;
	*(arr_inv + (3 * 4) + 3) = 1;
}
