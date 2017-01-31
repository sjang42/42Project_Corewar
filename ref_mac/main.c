#include <stdio.h>
#include <strings.h>
int main(void)
{
	int i;
	int size;
	char str[100001];
	int num;
	int arr[26];
	int already[26];
	int consec;

	bzero(arr, sizeof(int) * 26);
	bzero(already, sizeof(int) * 26);
	scanf("%s", str);

	consec = 1;
	i = 1;
	while (str[i])
	{
		if (str[i] == str[i - 1])
			consec++;
		else if (arr[str[i - 1] - 'a'] < consec)
		{
			arr[str[i - 1] - 'a'] = consec;
			consec = 1;
		}
		i++;
	}
	if (arr[str[i - 1] - 'a'] < consec)
		arr[str[i - 1] - 'a'] = consec;

	i = 0;
	while (i < 26)
	{
		printf("arr[%d] : %d\n", i, arr[i]);
		i++;
	}
	return (0);
}