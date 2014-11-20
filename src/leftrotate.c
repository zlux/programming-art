#include "stdio.h"
#include "stdlib.h"

#define forceMethod        0              /* pass */
#define pointerShift       0              /* pass */
#define pointerShift2      0              /* pass */

#define handinvert         1
void swap(char* a, char* b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

#if  handinvert

void * invert(char* pStart, char* pEnd)
{
	char chTmp = 0;
	while((pStart != 0) && (pEnd != 0) && (pStart < pEnd))
	{
		chTmp = *pStart;
		*pStart = *pEnd;
		*pEnd = chTmp;
		pStart++;
		pEnd--;
	}
}
#endif
int main(void)
{
	char target[100] = {0};
	int  iLength = 0;
	/*
	 * notice that gets is quite different from fgets, not only gets get from stdin, but also
	 * gets never assign a largest length, which can lead to buffer overflow. ALSO Important!!!
	 * gets will not include the \n in the returned string, fgets will include.
	 * and strlen will not include the null terminator at the end of a string.
	 *
	 * strlen()
	 * "
	 * The length of a C string is determined by the terminating null-character: A C string is as long as the number
	 * of characters between the beginning of the string and the terminating null character (without including the
	 * terminating null character itself).
	 * "
	 */
#if 0
	gets(target);
#endif
	/*
	 * fgets is much safer than gets, but when it comes to get integer from stdin, scanf is a
	 * better idea
	 */
#if 1
	fgets(target, 100, stdin);

#endif

	iLength = strlen(target);
	iLength--;
#if 1
	/* CAUTION:: the iLength already include \n */
	printf("length of the string is %d\n%s\n", iLength, target);
#endif

#if 0
	while(scanf("%s", target, 100))
	{
		if(strncmp(target, "exit", 4) == 0)
			break;
		iLength = strlen(target);
		printf("%s\n%d\n", target, iLength);

	}
#endif

	int iOffset = 0;
	/* please input the offset of the rotation counting from starting position*/
	printf("please input the offset\n");

	while(scanf("%d", &iOffset))
	{
		if(iOffset >= iLength)
			printf("offset exceed the length of input string, please input a number smaller than %d\n", iLength);
		else
			break;
	}

	printf("the offset is %d\n", iOffset);

#if forceMethod
	int i = 0;
	int j = 0;
	char chTmp = 0;
	for(i = 0; i<iOffset; i++)
	{
		chTmp = target[0];
		for(j = 1; j< iLength; j++)
			target[j-1] = target[j];
		target[iLength-1] = chTmp;
	}
#endif

#if pointerShift
	int p1 = 0;
	int p2 = iOffset;
	int i = 0;
	int j = 0;

	i = iLength-iLength%iOffset - iOffset;

	while(i--)
	{
		swap(target+p1, target+p2);
		p1++;
		p2++;
	}

	//tail thing to clean up
	i = iLength -p2;
	while(i--)
	{
		j = p2;
		while(j>p1)
		{
			swap(target+j, target +j-1);
			j--;
		}
		p2++;
		p1++;
	}
#endif

#if pointerShift2
	int p1 = 0;
	int p2 = iOffset;
	int r  = 0;
	char chTmp = 0;
	int i  = 0;

	while(p2 < iLength)
	{
		swap(target+ p1, target + p2);
		p1++;
		p2++;
	}
	/* Important!!!*/
	p2--;

	/* now the tail contains the junk needs to be sorted out by recursively shift iOffset - iLength%iOffset times
	 * keep p1, p2 is already the iLength, out of the array already
	 */
	r = iOffset - iLength%iOffset;
	while(r--)
	{
		i = p1;
		chTmp = target[i];
		while(i<p2)
		{
			target[i] = target[i+1];
			i++;
		}
		target[p2] = chTmp;
	}

#endif

#if handinvert
	invert(target, target+iOffset-1);
	invert(target+iOffset, target+iLength -1);
	invert(target, target+iLength-1);
#endif

	printf("after rotation the string is \n%s", target);
}

