#include<stdio.h>
#include<stdlib.h>

extern "C" void SIMD_ADD_ALIGN(float* a, float* b, float* output);

int main()
{
	__declspec(align(16)) float vecA[] = { 1.1, 2.2, 3.3, 4.4 };
	__declspec(align(16)) float vecB[] = { 5.5, 6.6, 7.7, 8.8 };
	float *res = (float*)_aligned_malloc(sizeof(float) * 4, 16);
	float* res_bakup = res;
#if _M_X64 == 100
	SIMD_ADD_ALIGN(vecA, vecB, res);
#else
	__asm {
		//mov eax, vecA; //See what will be compiled and what eax will get :)
		lea eax, vecA
		movaps xmm0, [eax];
		//movaps xmm0, [vecA];
		movaps xmm1, [vecB];
		addps xmm0, xmm1;
		mov eax, res; //See what will be compiled and what eax will get :-)
		movaps [eax], xmm0;
		//movaps[res], xmm0;
		//mov ebx, 0x1234;
		//mov [res], ebx; //See what will be compiled and what changed :--)
	}
#endif
	printf("Let's show result!\n");
	for (int i = 0; i < 4; i++)
	{
		printf("%f ", res[i]);
	}

	system("pause");

}