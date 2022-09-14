void sort(int arr[], int n)
{
	int i, j, min, index, temp;
	for (i = 0; i < n; i++)
	{
		min = MAX_SIZE;
		for (j = i; j < n; j++)
		{
			if (min > arr[j])
			{
				min = arr[j];
				index = j;
			}
		}
		temp = arr[i];
		arr[i] = arr[index];
		arr[index] = temp;
	}
}
#pragma once
